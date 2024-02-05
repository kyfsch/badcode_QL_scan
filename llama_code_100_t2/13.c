// This function is used to set up the title which displayed at the top of the dialog. You can use it to change the title, or to get rid of it entirely. If you need to change the title of most of your dialogs, it's preferable to.
void set_dialog_backtitle(const char *backtitle) {
    GtkWidget *widget = builder_get_object(dialog_builder, "dialog_back");
    gtk_dialog_set_title(GTK_DIALOG(dialog_builder), backtitle);
}

// Use this function to set the dialog's backtitle:
void set_dialog_title(const char *title) {
    char *backtitle = "Dialog Window";
    char *text = g_strdup_printf("%s - %s", backtitle, title);
    set_dialog_backtitle(text);
    g_free(text);
}

// You can use this to set a dialog's text entry's text. You have to build a gtk.Entry first!
void set_entry_text(const char *text) {
    gtk_entry_set_text(GTK_ENTRY(text_entry), text);
}

// This function is used to build the various dialogs depending on the values that have been set.
static gboolean on_response_handler(GtkDialog       *self,
                                    int             response_id,
                                    GtkWidget       **secondary_buttons,
                                    void *user_data) {
    const char *response_name = NULL;
    switch (response_id) {
        case GTK_RESPONSE_OK :
            response_name = "OK";
            break;
        case GTK_RESPONSE_YES :
            response_name = "Yes";
            break;
        case GTK_RESPONSE_NO :
            response_name = "No";
            break;
        case GTK_RESPONSE_CANCEL :
            response_name = "Cancel";
            break;
	    case GTK_RESPONSE_STOP :
            response_name = "Stop";
            break;
	    case GTK_RESPONSE_NEXT :
            response_name = "Next";
            break;
		
        default:
        response_name = "OK";
    }
    const char *text = "The response: ";
    if (text_entry