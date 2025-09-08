#include "CSerialComm.h"

#include <stdio.h>

wxDEFINE_EVENT(CSerialComm_Recv_Event, wxCommandEvent);

CSerialComm::CSerialComm():
    m_Fd(0),
    m_pRecvThread(nullptr),
    m_pParent(nullptr)
{
    //ctor
}

CSerialComm::~CSerialComm()
{
    //dtor

    if( m_pRecvThread)
    {
        EndRead();
    }

    // Close
    if( IsOpen())
    {
        Close();
    }
}

// Open
bool CSerialComm::Open(wxString port)
{
    if( IsOpen())
    {
        Close();
    }

    int fd = open(port.c_str(), O_RDWR|O_NOCTTY);
    if( fd == -1)
    {
        return false;
    }

    m_Fd = fd;

    // 現在のシリアルポートの設定を待避させる
    ioctl(fd, TCGETS, &oldtio);

    // ポートの設定をコピー
    newtio = oldtio;

    newtio.c_iflag = 0;
    newtio.c_oflag = 0;
    newtio.c_cflag = 0;
    newtio.c_lflag = 0;
    newtio.c_line = 0;
    bzero(newtio.c_cc, sizeof(newtio.c_cc));

    newtio.c_cflag = CS8 | CLOCAL | CREAD ;

    cfsetispeed( &newtio , B9600 );
    cfsetospeed( &newtio , B9600 );

    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;
    newtio.c_cc[VTIME] = 10;
    newtio.c_cc[VMIN] = 0;

    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &newtio);

    return true;
}

// Close
bool CSerialComm::Close()
{
    if( !IsOpen() )
    {
        return false;
    }

    ioctl(m_Fd, TCSETS, &oldtio);
    close(m_Fd);

    m_Fd = -1;


    return true;
}

// Send
bool CSerialComm::Write(wxString command)
{
    return true;
}

bool CSerialComm::Read(wxString& message)
{
    const int BUFFER_SIZE = 16;
    char buf[BUFFER_SIZE];
    while(true)
    {
        memset( buf, 0, BUFFER_SIZE);
        int n = read(m_Fd, buf, BUFFER_SIZE-1);

        if( n == 0)
            break;

        message += buf;

        if( BUFFER_SIZE-1 == n)
            continue;

        break;
    }

    return true;
}

bool CSerialComm::BeginRead(wxWindow* pParent)
{
    if( !IsOpen())
        return false;

    if( m_pRecvThread != nullptr)
        return false;

    m_pParent = pParent;

    m_pRecvThread = new std::thread(recv_thread_func, this);

    return (m_pRecvThread != nullptr);
}

bool CSerialComm::EndRead()
{
    if( !IsOpen())
        return false;

    if( m_pRecvThread == nullptr)
        return false;

    if( m_pRecvThread->joinable())
    {
        m_ExitRecvThread = true;
        m_pRecvThread->join();
    }

    delete m_pRecvThread;
    m_pRecvThread = nullptr;

    return true;
}


bool CSerialComm::IsOpen()
{
    return ( 0 <= m_Fd);
}

void CSerialComm::recv_thread_func(void* pArg)
{
    CSerialComm* pThis = static_cast<CSerialComm*>(pArg);
    if( !pThis)
        return;

    pThis->m_ExitRecvThread = false;

    const int BUFFER_SIZE = 16;
    char buf[BUFFER_SIZE];
    while(!pThis->m_ExitRecvThread)
    {

        wxString message;

        while(true)
        {
            memset( buf, 0, BUFFER_SIZE);
            int n = read(pThis->m_Fd, buf, BUFFER_SIZE-1);

            if( n == 0)
                break;

            message += buf;

            if( BUFFER_SIZE-1 == n)
                continue;

            break;
        }

        if( !message.empty())
        {
            if(pThis->m_pParent)
            {
                wxCommandEvent event(CSerialComm_Recv_Event);
                event.SetString(message);
                wxPostEvent(pThis->m_pParent, event);
            }
        }

        usleep(100000); // 100 milliseconds
    }

    pThis->m_pParent = nullptr;

}
