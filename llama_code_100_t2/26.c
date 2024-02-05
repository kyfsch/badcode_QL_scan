// This function is used to print the dependency graph, including edges or arrows, using str_append..
static void get_dep_str(struct gstr *r, struct expr *expr, const char *prefix)
{
	char *arrow = "", *s;

	if (expr->type == EXPR_BLOCK) {
		expr=expr->u.block.expr;
	}

	if (expr->type == EXPR_PAREN) {
		get_dep_str(r, expr->u.paren, prefix);
		return;
	}

	// Print expressions, excluding strings and function calls.
	if (expr->type == EXPR_FIELD) {
		get_dep_str(r, expr->u.field.expr, "%s");
		str_append(r, ".%s", expr->u.field.field->name);
		return;
	}

	if (r->curpendingcall && expr->type == EXPR_ID) {
		s = expr->u.sym->name;
		if (strcmp(s, "return") == 0) {
			str_append_chr_escaped(r, s, '"');
			return;
		}

		// A call has a pending node if it is an external symbol (or global
		// from this compilation unit) and does not start with '_'.
		if (expr->u.sym->kind == SYM_FN || expr->u.sym->kind == SYM_EXT) {
			if (expr->u.sym->name[0] != '_') {
				// It is a call to a function. Do we have a call tree?
				if (expr->u.sym->call->call_tree) {
					// Do we have a previous pending call?
					if (r->prevpendingcall) {
						// Yes, so insert a new edge.
						str_append(r, " -> ");
					} else {
						// No. Is this not a return value, or is the call graph
						// already displayed?
						if (!expr->u