// This function is used to iterate through the elements of a bpf map in uc_bpfvm. It has access to map elements, their keys and values. It is used by uc_bpfcall_map_ops functions to perform actions (e.
uc_bpf_map_iter_next_int(uc_vm_t *vm, size_t nargs) {
    struct uc_bpf_map *map;
    struct uc_obj_iter *iter;
    uc_val_t value;
    uint8_t  *data;
    uint32_t key_size = 0;
    uint32_t value_size = 0;
    char *buf = NULL;
    int buf_size = 0;

    if (nargs == 1) {
        value = ucv_string_new((const char *)vm->state->arguments[0].ptr);
    } else {
        value = (uc_val_t)vm->state->arguments[0];
    }

    if (ucv_type(value) != UC_INTPTR) {
        uc_magerror(vm, "Argument must be int.");
        return NULL;
    }

    iter = (struct uc_obj_iter *)ucv_intptr_value(value);

    if(ucs_iter_type_key_value(iter) == UC_MAP_ITER_KEY_VALUE_TYPE_NONE) {
        uc_magerror(vm, "Map key or value not defined.");
        return NULL;
    }

    map = iter->obj;
    key_size = map->key_size;
    value_size = map->value_size;

    buf_size = buf_size_int(map, iter);

    // No more entries
    if(!buf_size) {
        data = NULL;
            //ucv_handle_map_iter_close(iter);
            //ucs_iter_type_key_value(iter) = UC_MAP_ITER_KEY_VALUE_TYPE_NONE;
            //return NULL;
    }
    else {
          buf = (char *)malloc(buf_size);
          if (buf == NULL) {
                  perror("malloc");

                  ucs_iter_type_key_value(iter) = UC_MAP_ITER_KEY_VALUE_TYPE_NONE;
                  ucv_handle_map_iter