/***************************************************************
 * Name:      webviewMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2025-09-08
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef WEBVIEWMAIN_H
#define WEBVIEWMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "webviewApp.h"
#include <wx/webview.h>

class webviewFrame: public wxFrame
{
    public:
        webviewFrame(wxFrame *frame, const wxString& title);
        ~webviewFrame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()

        void OnShow(wxShowEvent& e);

        wxPanel* m_pMainPanel;

        wxWebView* m_pWebView;

        void OnNavigated(wxWebViewEvent& e);
        void OnLoaded(wxWebViewEvent& e);
};


#endif // WEBVIEWMAIN_H
