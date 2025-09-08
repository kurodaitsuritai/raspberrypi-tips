/***************************************************************
 * Name:      webviewApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2025-09-08
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "webviewApp.h"
#include "webviewMain.h"

IMPLEMENT_APP(webviewApp);

bool webviewApp::OnInit()
{
    webviewFrame* frame = new webviewFrame(0L, _("wxWidgets Application Template"));
    
    frame->Show();
    
    return true;
}
