#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>

class MainFrame : public wxFrame
{
    public:
        MainFrame();
        virtual ~MainFrame();

    protected:

    private:
        wxString shell(wxString cmd);
};

#endif // MAINFRAME_H
