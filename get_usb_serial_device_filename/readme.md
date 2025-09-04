# 特定のUSBシリアルのデバイスファイル名を取得する

## lsusb

* lsusbの結果は以下のようになっているとする。

```
Bus 004 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
Bus 003 Device 002: ID 324f:0032 SM SM-2D PRODUCT USB UART
Bus 003 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
Bus 002 Device 003: ID 04b4:00f1 Cypress Semiconductor Corp. FX3
Bus 002 Device 002: ID 2109:0812 VIA Labs, Inc. VL812 Hub
Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
Bus 001 Device 003: ID 16c0:0483 Van Ooijen Technische Informatica Teensyduino Serial
Bus 001 Device 006: ID 03f0:134a HP, Inc Optical Mouse
Bus 001 Device 005: ID 03f0:334a HP, Inc HP Business Slim Keyboard
Bus 001 Device 004: ID 0403:6015 Future Technology Devices International, Ltd Bridge(I2C/SPI/UART/FIFO)
Bus 001 Device 002: ID 2109:2812 VIA Labs, Inc. VL812 Hub
Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
```

## grep, cutを利用する

```
ls /dev/serial/by-id -l
```

```
合計 0
lrwxrwxrwx 1 root root 13  9月  4 15:11 usb-FTDI_FT230X_Basic_UART_DK0DOZ7K-if00-port0 -> ../../ttyUSB0
lrwxrwxrwx 1 root root 13  9月  4 15:11 usb-SM_SM-2D_PRODUCT_USB_UART_APP-000000000-if00 -> ../../ttyACM0
lrwxrwxrwx 1 root root 13  9月  4 15:11 usb-Teensyduino_USB_Serial_15218520-if00 -> ../../ttyACM1


```

* FTDIの場合

```
ls /dev/serial/by-id -l |grep -i ftdi | cut -d'>' -f2 | cut -d'/' -f3
```

```
ttyUSB0
```

* Teensyduinoの場合

```
ls /dev/serial/by-id -l |grep -i teensy | cut -d'>' -f2 | cut -d'/' -f3
```

```
ttyACM1
```

* sunmiの場合

```
ls /dev/serial/by-id -l |grep -i sm-2d | cut -d'>' -f2 | cut -d'/' -f3
```

```
ttyACM0
```

## C++での実装例

```cpp UsbSerialDeviceFileName.h

#ifndef USBSERIALDEVICEFILENAME_H
#define USBSERIALDEVICEFILENAME_H

#include <wx/wx.h>


class UsbSerialDeviceFileName
{
public:
    static wxString GetUsbSerialDeviceFileName(wxString keyword);
    static wxString GetUsbSerialDeviceFileName(wxString vendorid, wxString productid);

private:
    static wxString shell(wxString cmd);
};

#endif // USBSERIALDEVICEFILENAME_H

```

```cpp UsbSerialDeviceFileName.cpp
#include "UsbSerialDeviceFileName.h"

wxString UsbSerialDeviceFileName::shell(wxString cmd)
{
    wxString ret;

    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe)
    {
        return ret;
    }

    char buffer[128];
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

wxString UsbSerialDeviceFileName::GetUsbSerialDeviceFileName(wxString keyword)
{
    return shell(wxString::Format(wxT("ls /dev/serial/by-id -l |grep -i %s | cut -d'>' -f2 | cut -d'/' -f3"), keyword)).Trim();
}

wxString UsbSerialDeviceFileName::GetUsbSerialDeviceFileName(wxString vendorid, wxString productid)
{
    wxString ret;

    wxString res = shell(wxT("ls /dev/serial/by-id -l | grep -i '../../tty' | cut -d'>' -f2 | cut -d'/' -f3")).Trim();

    wxArrayString ttys = wxSplit(res, '\n');

    if( ttys.size() == 0)
    {
        return ret;
    }

    for(wxString tty : ttys)
    {
        wxString tempRes = shell(wxString::Format(wxT("udevadm info /dev/%s | grep -i 'ID_USB_VENDOR_ID' | cut -d'=' -f2"), tty)).Trim().Upper();
        if( vendorid.Trim().Upper() == tempRes)
        {
            tempRes = shell(wxString::Format(wxT("udevadm info /dev/%s | grep -i 'ID_USB_MODEL_ID' | cut -d'=' -f2"), tty)).Trim().Upper();
            if( productid.Trim().Upper() == tempRes)
            {
                ret = tty;
                break;
            }
        }
    }

    return ret;
}

```


