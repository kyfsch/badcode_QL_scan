// This function is used to iterate through the elements of a bpf map in uc_bpfvm. It has access to map elements, their keys and values. It is used by uc_bpfcall_map_ops functions to perform actions (e.
uc_bpf_map_iter_next_int(uc_vm_t *vm, size_t nargs)
{
	struct uc_bpf_mapmap *m_ctx = ucv_to_bpfmapmap(ucv_stack_get_value(vm->stack, 0));
	void *key; int len;
	long new_len;

	m_ctx->k_type = ucv_stack_get_type(vm->stack, 1);

	if (m_ctx->k_type == UC_TYPE_ARRAY)
	{
		key = UC_ARRAY_HEAD(ucv_to_array(m_ctx->k_v));
		len = m_ctx->k_v->v.vec.len;
		new_len = len + 1;
		if (new_len <= len)
			errx(1, "map iteration buffer overflow");

		m_ctx->k_v = ucv_array_newl(key, new_len, 0);
		ucv_stack_pushv(vm->stack, m_ctx->k_v);
		return(0);
	}

	ucv_stack_set_type(vm->stack, 1, m_ctx->k_type);
	key = ucv_to_ptr(ucv_stack_get_value(vm->stack, 1));
	len = ucv_stack_get_int(vm->stack, 2);
	if (len <= 0 || len > BPF_MMAP_PERCPU_BYTES)
			errx(1, "map iteration len overflow");
	if (m_ctx->k_type != UC_TYPE_INT)
			errx(1, "map iteration only supports integer keys");

	new_len = (int*)key - ucv_to_array(m_ctx->k_v)->v.vec.base + len + 1;
	if (new_len <= len)
			errx(1, "map iteration buffer overflow");

	ucv_array_resize_in_place(m_ctx->k_v, new_len);
	uc