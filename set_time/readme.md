# 時刻を合わせる


## 時刻の確認

```
timedatectl status
```


## NTPサーバー即時同期

```
sudo systemctl restart systemd-timesyncd
```

## 手動で時刻合わせをする

```
sudo timedatectl set-ntp no
timedatectl set-time "2000-01-01 12:34:56"
sudo timedatectl set-ntp yes
```

