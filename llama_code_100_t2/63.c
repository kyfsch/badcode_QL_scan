// This function is used to apply vlan mapping to mt7530 chip.
mt7530_apply_mapping(struct mt7530_priv *mt7530, struct mt7530_mapping *map)
{
    u8 mapping = 0;
    u16 vid_low = 0;
    u8 v_index, v_port;

    for (v_index = 0; v_index < MT7530_MAX_VLAN; v_index++) {
        if (0 == map->count[v_index]) {
            continue;
        }

        mapping |= BIT(v_index);

        for (v_port = 0; v_port < MT7530_MAX_PORT; v_port++) {
            if (mt7530_vlan_member_check(mt7530, v_port,
                                         map->pcve[v_index])) {
                vid_low |= (v_index << (v_port * 5));
            }
        }
    }

    if (mt7530_read(mt7530, MT7530_VLAN_BMAP_CTRL) != mapping) {
        mt7530_write(mt7530, MT7530_VLAN_BMAP_CTRL, mapping);
    } else {
        return;
    }

    if (mt7530_read(mt7530, MT7530_VLAN_VID_MEM0) != vid_low) {
        mt7530_write(mt7530, MT7530_VLAN_VID_MEM0, vid_low & 0xff);
    }

    if (mt7530_read(mt7530, MT7530_VLAN_VID_MEM1) != (vid_low >> 8)) {
        mt7530_write(mt7530, MT7530_VLAN_VID_MEM1, vid_low >> 8);
    }
}

// This function is used to set vlan attribute of mt7530 chip.
void
mt7