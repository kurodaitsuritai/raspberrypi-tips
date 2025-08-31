# アプリケーションの自動起動

* Raspberry Pi 5 Bookworm 64bit x11環境の場合

```
mkdir -p ~/.config/lxsession/LXDE-pi
cp /etc/xdg/lxsession/LXDE-pi/autostart ~/.config/lxsession/LXDE-pi/
```

* autostartの編集

```
nano ~/.config/autostart
```

```
@lxpanel --profile LXDE-pi
@pcmanfm --desktop --profile LXDE-pi
@xscreensaver -no-splash

#　以下を追加
@/home/pi/.config/autostart.sh
```

* ~/.config内のautostart.shの編集

```
nano ~/.config/autostart.sh
```

* ~/.config/autostart.shの編集

```

# pythonスクリプトを実行する場合
python 〇〇.py

# 実行ファイルを起動する場合
/home/pi/〇〇

```