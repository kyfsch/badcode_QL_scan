// This function is used to print the dependency graph, including edges or arrows, using str_append..
static void get_dep_str(struct gstr *r, struct expr *expr, const char *prefix)
{
	for (; expr; expr = expr->next)
	{
		int len2 = len - indent;
		str_append(r, prefix);
		str_append(r, expr->pattern);
		int len1 = strlen(r->s);
		str_append(r, "\"];");
		if (expr->expr)
		{
			str_append(r, " digraph expr{; bgcolor=transparent;fontcolor=transparent; fontsize=11; fontname=Verdana;");
		}
		else
		{
			str_append(r, "style=filled; color=white;");
		}
		str_append(r, " label=\" ");
		str_append(r, expr->pattern);
		str_append(r, "\"];");
		struct expr **e = find_edge(expr, expr->pattern);
		if (e && *e && (!*e || !(*e)->match))
		{
			str_append(r, "digraph expr {");
			get_dep_str(r, *e, prefix);
			str_append(r, "edge [");
			str_append(r, (*e)->pattern);
			str_append(r, "]");
			len1 = strlen(r->s);

			str_append(r, "[color=blue,style=bold]");
			str_append(r, prefix);
			str_append(r, expr->pattern);
			str_append(r, "->");
			str_append(r, (*e)->pattern);
			str_append(r, "];");
			int rlen = strlen(r->s);
			len1 += rlen - len1;
			len2 = len - indent;
			str_append(r, prefix);
			str_append(r, expr->pattern);
			len2