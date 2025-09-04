# 特定のUSBシリアルのデバイスファイル名を取得する

## grep, cutを利用する

```
ls /dev/serial/by-id -l
```

```
合計 0
lrwxrwxrwx 1 root root 13  9月  4 14:10 usb-FTDI_FT230X_Basic_UART_DK0DOZ7K-if00-port0 -> ../../ttyUSB0
lrwxrwxrwx 1 root root 13  9月  4 11:46 usb-Teensyduino_USB_Serial_15218520-if00 -> ../../ttyACM0

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
ttyACM0
```
