# RTCバッテリーの充電設定を行う

/boot/firmware/config.txtを編集する。

```
sudo nano /boot/firmware/config.txt
```

以下を追加する。

```
dtparam=rtc_bbat_vchg=3000000
```

## その他

### 現在のバッテリーの電圧を取得する

```
cat /sys/devices/platform/soc@107c000000/soc@107c000000:rpi_rtc/rtc/rtc0/battery_voltage
```

### 充電電圧を取得する

```
cat /sys/devices/platform/soc@107c000000/soc@107c000000:rpi_rtc/rtc/rtc0/charging_voltage
```


## リンク

* [Enable battery charging](https://www.raspberrypi.com/documentation/computers/raspberry-pi.html#enable-battery-charging)