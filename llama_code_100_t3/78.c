// This function is used to list all of the supported attributes in their respective attributes lists. This attribute list is basically a list of struct switch_attributes which is defined like this.
swconfig_list_attrs(struct sk_buff *skb, struct genl_info *info)
{
  // swconfig_attrlist_t is used to list the supported attributes for each different attribute list we have set. This struct has a name and an array of struct switch_attributes.
	struct swconfig_attrlist attrlist[NLA_LIST];

  // for now you fill in the arrays with all the attributes you want to list.
	// first index is the enum for which attribute list to list. This could be a good time to give these different attributes lists some names.
	attrlist[UNSPEC].name = "N/A";
	attrlist[UNSPEC].attrs[0]= { "N/A",SW_ATTR_UNSPEC}
	attrlist[UNSPEC].attrs[1]= { "N/A",SW_ATTR_UNSPEC}
	// ..
	attrlist[STP].name = "switch stp";
	attrlist[STP].attrs[0]= { "N/A",SW_ATTR_STP}
	attrlist[STP].attrs[1]= { "N/A",SW_ATTR_STP}
	// ..
	attrlist[MAX_PORTS].name = "max ports";
	attrlist[MAX_PORTS].attrs[0]= { "N/A",SW_ATTR_MAX_PORTS}
	attrlist[MAX_PORTS].attrs[1]= { "N/A",SW_ATTR_MAX_PORTS}
	// ..
	attrlist[DYNAMIC_PORTS].name = "dynamic ports";
	attrlist[DYNAMIC_PORTS].attrs[0]= { "N/A",SW_ATTR_DYNAMIC_PORTS}
	attrlist[DYNAMIC_PORTS].attrs[1]= { "N/A",SW_ATTR_DYNAMIC_PORTS}
	// ..
	attrlist[FDB_MODE].name = "fdb mode";
	attrlist[FDB_MODE].attrs[0]= { "N/A",SW_ATTR_FDB_MODE}
	attrlist