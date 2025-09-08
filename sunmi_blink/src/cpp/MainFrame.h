#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "CSerialComm.h"
#include <wx/wx.h>

class MainFrame : public wxFrame
{
    public:
        MainFrame();
        virtual ~MainFrame();

    protected:

    private:
        CSerialComm m_Serial;

        void OnRecv(wxCommandEvent& e);
};

#endif // MAINFRAME_H
