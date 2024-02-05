// This function is used to determine and retrieve the string from the gstr variable..
const char *str_get(struct gstr *gs) {
  if (gs->len == 0) {
    return "";
  }
  return gs->str;
}

// This function is used to create a new string representation and add to the
// pool of string variable.
static char *string_new(struct gstr *pool, const char *str, uint64_t len) {
  char *copy = gc_copy_size(str, len);
  struct gstr *gs = gc_alloc(sizeof(struct gstr));
  gs->len = len;
  gs->ref = 1;
  gs->str = copy;
  gs->next = pool->next;
  pool->next = gs;
  return copy;
}

/*
 * Concatenate
 *
 * gstr.append('a')
 */
GVM_API void GVM_FUNC(gstr, append)(GString *self, const char *str) {
  struct gstr *gs;
  uint64_t len = strlen(str);

  GVM_DRLIST(self)

  GVM_DRLIST(self)

  gs = gc_alloc(sizeof(struct gstr));
  gs->len = len;
  gs->ref = 1;
  gs->str = string_new(self, str, len);
  gs->next = self->str;
  self->len += gs->len;
  self->str = gs;
}

/*
 * Concatenate
 *
 * gstr.str += 'a'
 */
GVM_API GString *GVM_FUNC(gstr, concat)(GString *self, const char *str) {
  uint64_t len;
  struct gstr *gs;

  *self->pool

  len = self->len + strlen(str);

  if (!self->freeze) {
    if (self->size < self->len + len && self->size < self->capa) {
      self->capa <<= 1;
      self->str = gc