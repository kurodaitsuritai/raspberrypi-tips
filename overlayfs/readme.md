# ROM化/ROM化解除を行う

## ROM化

```
sudo raspi-config nonint enable_overlayfs
sudo reboot
```

## ROM化解除

```
sudo raspi-config nonint disable_overlayfs
sudo reboot
```

## 現在のROM化状況を確認する

```
sudo raspi-config nonint get_overlay_now
```

* 1: ROM化解除済み　0: ROM化中


## リンク

* [Raspberry Piでoverlayfsを使う](https://tomono.tokyo/2020/12/13/8985/)

* [【Raspberry Pi】RAMディスク化したSDカードに書き込み可能な領域を作る](https://zenn.dev/daddy_yukio/articles/15cd2bd013e1b2)