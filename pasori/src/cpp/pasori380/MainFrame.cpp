#include "MainFrame.h"

MainFrame::MainFrame():
    wxFrame(nullptr, wxID_ANY, wxT("RC-S380"))
{
    // スクリプト
    wxString src = wxT(R"(
import nfc
import nfc.tag.tt3
import nfc.tag.tt4
import binascii
import sys
import os
import time

#
#  Card Reader
class CardReader(object):
  def __init__(self):
    self.clf=nfc.ContactlessFrontend('usb')
    self.target = None

    self.T106A = nfc.clf.RemoteTarget('106A')
    self.T106B = nfc.clf.RemoteTarget('106B')

    # FeliCa
    self.suica = self.set_felica('0003')
    self.edy = self.set_felica('8054')
    self.express = self.set_felica('854C')
    self.nanaco = self.set_felica('04C7')
    self.waon = self.set_felica('684F')

    self.targets = [ self.suica, self.T106A, self.T106B, self.edy, self.express, self.nanaco, self.waon ]
    self.targets1 = [ self.suica, self.T106A, self.T106B ]
    self.targets2 = [ self.T106A, self.T106B, self.set_felica() ]

    self.toggle=0


  #
  #
  def set_felica(self, sys_=None):
    target = nfc.clf.RemoteTarget('212F')
    if sys_ is not None:
      target.sensf_req=bytearray.fromhex('00%s0000' % sys_)
    return target

  #
  #
  def sense(self, toggle=False):
    if toggle:
      self.target = self.sense_toggle()
    else:
      self.target = self.clf.sense(*self.targets, iterations=5, interval=0.5)
    return self.target

  #
  #
  def sense_toggle(self):
    if self.toggle == 0:
      self.target = self.clf.sense(*self.targets, iterations=10, interval=0.1)
    else:
      self.target = self.clf.sense(*self.targets2, iterations=1, interval=0.1)
    self.toggle = (self.toggle + 1) % 2
    return self.target

  #
  #
  def on_discover(self, target):
    if target is None: return False
    if target.sel_res and target.sel_res[0] & 0x40:
      return False
    elif target.sensf_res and target.sensf_res[1:3] == b'\x01\xFE' :
      return False
    else:
      return True

  #
  #
  def get_idm(self, tag):
    if bool(tag):
      return binascii.hexlify(tag.identifier).decode()
    return None

  #
  #
  def read_card_id(self, flag=False):
    if self.sense(flag) is None:
      return None, None
    if self.on_discover(self.target) :
      tag = nfc.tag.activate(self.clf, self.target)
      return tag, self.get_idm(tag)

#
#
def main():
  tm=1
  flag=1
  if len(sys.argv) > 1:
    tm=int(sys.argv[1])
    if len(sys.argv) > 2:
      flag=int(sys.argv[2])

  cr=CardReader()
  for i in range(tm):
    tag, idm = cr.read_card_id(flag)
    if tag is None:
      continue
    print('IDm:',idm)
    break

if __name__ == '__main__':
  main()
)");

    wxString command = wxString::Format(wxT("sudo python -u -c \"%s\" | grep -i 'idm' | cut -d':' -f2 | xargs"), src);

    for(int i=0 ; i<100 ; i++)
    {
        wxString ret = shell(command);
        ret = ret.Trim();
        ret = ret.Upper();
        if( !ret.empty())
        {
            this->SetTitle(ret);
            break;
        }
        usleep(100000);
    }


}

MainFrame::~MainFrame()
{
    //dtor
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
