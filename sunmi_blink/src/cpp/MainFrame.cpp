#include "MainFrame.h"

MainFrame::MainFrame():
    wxFrame(nullptr, wxID_ANY, wxT("Seial Communication"))
{
    wxString port = wxT("/dev/ttyACM1");

    this->Bind(CSerialComm_Recv_Event, &MainFrame::OnRecv, this);

    m_Serial.Open(port);

    m_Serial.BeginRead(this);
}

MainFrame::~MainFrame()
{
    m_Serial.Close();
}

void MainFrame::OnRecv(wxCommandEvent& e)
{
    this->SetTitle(e.GetString());
}
