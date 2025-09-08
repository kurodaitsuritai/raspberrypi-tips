/***************************************************************
 * Name:      webviewMain.cpp
 * Purpose:   Code for Application Frame
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

#include "webviewMain.h"
#include <wx/webview.h>

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(webviewFrame, wxFrame)
    EVT_CLOSE(webviewFrame::OnClose)
    EVT_MENU(idMenuQuit, webviewFrame::OnQuit)
    EVT_MENU(idMenuAbout, webviewFrame::OnAbout)
END_EVENT_TABLE()

webviewFrame::webviewFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title),
    m_pWebView(nullptr)
{

    this->Bind(wxEVT_SHOW, &webviewFrame::OnShow, this);

    m_pMainPanel = new wxPanel(this);

    m_pMainPanel->SetBackgroundColour(wxColor(0xFF, 0xFF, 0xFF));


    this->SetMinSize(wxSize(512, 512));
    this->SetSize(wxSize(513, 513));

    m_pWebView = wxWebView::New();
    m_pWebView->Create(m_pMainPanel, wxID_ANY);

    m_pWebView->Bind(wxEVT_WEBVIEW_NAVIGATED, &webviewFrame::OnNavigated, this);
    m_pWebView->Bind(wxEVT_WEBVIEW_LOADED, &webviewFrame::OnLoaded, this);

    wxSizer* pSizer = new wxBoxSizer(wxVERTICAL);

    pSizer->Add(m_pWebView, 1, wxEXPAND | wxALL);

    m_pMainPanel->SetSizer(pSizer);

    this->Center();


#if wxUSE_MENUS
    // create a menu bar
    wxMenuBar* mbar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
    mbar->Append(fileMenu, _("&File"));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuAbout, _("&About\tF1"), _("Show info about this application"));
    mbar->Append(helpMenu, _("&Help"));

    SetMenuBar(mbar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(_("Hello Code::Blocks user!"),0);
    SetStatusText(wxbuildinfo(short_f), 1);
#endif // wxUSE_STATUSBAR

}


webviewFrame::~webviewFrame()
{
}

void webviewFrame::OnNavigated(wxWebViewEvent& e)
{
    wxString url = e.GetURL();
    if( url == wxT("about:blank"))
    {
        return;
    }
    else
    {
        wxSize sz = this->GetSize();
        sz.DecBy(1);
        this->SetSize(sz);
    }
}

void webviewFrame::OnLoaded(wxWebViewEvent& e)
{

}

void webviewFrame::OnShow(wxShowEvent& e)
{
    if(e.IsShown())
    {
        m_pWebView->LoadURL(wxT("https://google.com"));
    }
}

void webviewFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void webviewFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void webviewFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
