# 起動時のロゴ画像を変更する

## ロゴ画像を表示させなくする

* ロゴ画像を表示させなくするには、splash.pngの名前を変更する。

```
sudo mv /usr/share/plymouth/themes/pix/splash.png /usr/share/plymouth/themes/pix/_splash.png

sudo update-initramfs -u
```

## ロゴ画像を変更する

* ロゴ画像を差し替える場合は、splash.pngを上書きする。

```
sudo mv 〇〇.png /usr/share/plymouth/themes/pix/splash.png

sudo update-initramfs -u
```