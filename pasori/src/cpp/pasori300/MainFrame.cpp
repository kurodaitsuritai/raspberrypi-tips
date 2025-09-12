#include "MainFrame.h"

MainFrame::MainFrame():
    wxFrame(nullptr, wxID_ANY, wxT("RC-S300"))
{
    this->Bind(wxEVT_SHOW, &MainFrame::OnShow, this);

}

MainFrame::~MainFrame()
{
    //dtor
}

void MainFrame::OnShow(wxShowEvent& e)
{
    Test();
}

void MainFrame::Test()
{
    // スクリプト
    wxString src = wxT(R"(
import sys
import time

from smartcard.Exceptions import NoCardException
from smartcard.System import readers
from smartcard.util import toHexString

while True:
    for reader in readers():
        try:
            connection = reader.createConnection()
            connection.connect()
            send_data = [0xFF, 0xCA, 0x00, 0x00, 0x00]
            data, sw1, sw2 = connection.transmit(send_data)
            print('IDm:', toHexString(data).replace(' ', ''))
            connection.disconnect()
            connection.release()
        except NoCardException:
            pass
            #print(reader, 'no card inserted')
    time.sleep(0.1)
)");

    wxString command = wxString::Format(wxT("python -u -c \"%s\" | grep -i 'idm' | cut -d':' -f2 | xargs"), src);

    for(int i=0 ; i<1000 ; i++)
    {
        wxString ret = shell(command);
        ret = ret.Trim();
        if( !ret.empty())
        {
            this->SetTitle(ret);
            break;
        }
        usleep(100000);
    }
}


wxString MainFrame::shell(wxString cmd)
{
    wxString ret;

    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe)
    {
        return ret;
    }

    char buffer[128]={};
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        result += buffer;
    }

    int status = pclose(pipe);
    if (status == -1)
    {
        return ret;
    }

    return wxString(result.c_str(), wxConvUTF8);
}
