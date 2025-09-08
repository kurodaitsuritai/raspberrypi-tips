#ifndef CSERIALCOMM_H
#define CSERIALCOMM_H

#include <wx/wx.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <thread>


wxDECLARE_EVENT(CSerialComm_Recv_Event, wxCommandEvent);

class CSerialComm
{
    public:
        CSerialComm();
        virtual ~CSerialComm();

        bool Open(wxString port);
        bool Close();

        bool Write(wxString command);
        bool Read(wxString& message);

        bool BeginRead(wxWindow* pParent);
        bool EndRead();

    protected:

    private:
        wxString m_Port;
        bool IsOpen();

        int m_Fd; // File Descriptor

        struct termios oldtio, newtio;

        std::thread* m_pRecvThread;

        wxWindow* m_pParent;

        static void recv_thread_func(void* pArg);

        volatile bool m_ExitRecvThread;
};

#endif // CSERIALCOMM_H
