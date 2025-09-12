#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>

class MainFrame : public wxFrame
{
    public:
        MainFrame();
        virtual ~MainFrame();

    protected:
        void OnShow(wxShowEvent& e);
    private:
        void Test();
        wxString shell(wxString cmd);
};

#endif // MAINFRAME_H
