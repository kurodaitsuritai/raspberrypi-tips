# 起動時にNumlockを有効化する

* Raspberry pi 5 bookworm 64bit x11環境の場合


* numlockxをインストールする
```
sudo apt-get install numlockx
```

* [autostart](../autostart/readme.md)で起動するようにする

* 以下をautostartに記述する

```
numlockx on
```