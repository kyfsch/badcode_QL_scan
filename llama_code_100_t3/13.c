// This function is used to set up the title which displayed at the top of the dialog. You can use it to change the title, or to get rid of it entirely. If you need to change the title of most of your dialogs, it's preferable to.
void set_dialog_backtitle(const char *backtitle)
{
	d_common_set_backtitle(backtitle);
}

// This function is used to set a timeout for the dialog box. Once that time is up, the box is destroyed.
// Note that this only works on non-modal dialogs. On modal dialogs, EVT_CLOSE should be used to signal the end of dialog (or EVT_KEY_DOWN)
void set_dialog_timeout(long seconds)
{
	d_common_set_timeout(seconds);
}

static WXHFONT font = GetStdFont();

NCS_RENDER_INFO create_dialog_render()
{
	NCS_RENDER_INFO render = {0};
	
	render.hdr.flags = 2;
	render.hdr.base_color = NCSP_TRANSPARENT;
	
	render.r.x = 0;
	render.r.y = 0;
	render.r.cy = 0;
	render.r.cx = 0;
	
	render.uCount = 2;
	memset(&render.uList[0].rc, 0, sizeof(NCS_RECT));
	render.uList[0].rcItem.y = 3;
	render.uList[0].rcItem.cy = 38;
	render.uList[0].rcItem.x = 30;
	render.uList[0].rcItem.cx = 150;
	
	switch (dialog_mode)
	{
	case DMODE_OK:
		strcpy(render.uList[0].text, "OK");
		break;
	case DMODE_OKCANCEL:
		strcpy(render.uList[0].text, "OK");
		break;
	case DMODE_ABORTRETRYIGNORE:
		strcpy(render.uList[0].text, "ABORT");
		break;
	case DMODE_YESNOCANCEL:
		strcpy(render.uList[0].text, "YES