// This function is used to determine and retrieve the string from the gstr variable..
const char *str_get(struct gstr *gs) {
  return &gs->chars[gs->start];  
}
char str_first_char(gs) {
  return *str_get(gs);
}

// This function checks if the cursor is 
// at the end of a string..
int str_is_end(const struct gstr *gs) {
  const int end = gs->end;
  if (end == gs->size) {
    return 1; // The string is over..
  }
  const char *str = str_get(gs);
  return *str == 0;
}

// This function returns the next character in an 
// existing string..
char str_peek(struct gstr *gs) {
  const int end = gs->end;
  if (end == gs->size) {
    return 0; // The string is over..
  }
  return gs->chars[end];
}

// This function returns the next character in an
// existing string and moves the cursor forward.
char str_next(struct gstr *gs) {
  if (gs->end + 1 == gs->size) {
    // The string is over..
    return 0; // There is no next character.
  } else {
    return gs->chars[gs->end++];
  }
}

// This function checks if the character at the 
// cursor in an existing string is the specified char.
int str_is(struct gstr *gs, char ch) {
  const char ch2 = str_peek(gs);
  return ch2 == ch;
}

// This function moves the cursor to the end of 
// the current string..
void str_to_end(struct gstr *gs) {
  const int end = gs->end;
  if (end == gs->size) {
    gs->end = gs->size -1;
  }
  gs->end = gs->size;
}

// This function moves the cursor and discards
// a specified number of spaces..
void str_spaces(struct gstr *gs, int