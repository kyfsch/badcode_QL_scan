// This function is used to extract the specific data structure from.
static inline struct des_container *des_container_cast(struct pme_container *cont)
{
    return (struct des_container *)cont;
}

// This function is used to check if a struct data_element has the specific kind
// container.
static inline bool
is_des_container_kind(const struct pme_container *cont)
{
    return (cont->type == PMEM_CONTAINER_DESCRIPTOR_KIND);
}

// This function is used to initialize a struct data_element container.
static inline struct pme_container *des_container_init(struct pme_descriptor *descriptor)
{
    struct des_container *cont = calloc(1, sizeof(struct des_container));
    if (cont == NULL) {
        return NULL;
    }

    pme_container_init_from_des_container(cont);

    cont->data.des.pme_descriptor = descriptor;
    cont->kind = PME_DESCRIPTOR_KIND_V2;

    return (struct pme_container *)cont;
}

// This function takes a pointer to a struct data_element container and frees
// all the memory allocated for this container including all the memory used
// internally by the pmem data structure itself as well.
static inline void des_container_free(struct pme_container *cont)
{
    struct des_container *des_cont = des_container_cast(cont);

    free(des_cont->data.des.pme_descriptor->pme_descriptor);
    des_cont->data.des.pme_descriptor->pme_descriptor = NULL;

    free(des_cont->data.des.pme_descriptor);
    des_cont->data.des.pme_descriptor = NULL;

    free(des_cont);
}

// This function converts a string name to the internal integer that marks the
// type of struct data_element container. This kind is specific for this
// data structure.
static inline enum pme_descriptor_kind des_container_get_kind_from_name(const char *name)
{
    if