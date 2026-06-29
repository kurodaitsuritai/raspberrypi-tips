# SDカード・イメージの圧縮

以下に、Ubuntuでの使用例を示す。

SDカードからイメージを抽出する際は、

* OverlayFSを無効化する
* 起動パーティションを書き込み可能にする

をやっておく必要がある？（要確認）


## SDカードがどこにあるかを探す

下記コマンドで、SDカードがどこにあるのか(/dev/sdbなど)を探す。

```
lsblk -p
```

## SDカード から イメージファイル を抽出する

```
sudo dd if=/dev/sdb of=2026-06-29-sbrange-dev.img bs=1M status=progress
```

## pishrinkを用いて、イメージファイルを圧縮する

```
sudo pishrink.sh 2026-06-29-sbrange-dev.img
```

## 圧縮されたイメージファイルをSDカードに焼きこむ

```
sudo dd if=./2026-09-29-sbrange-dev.img of=/dev/sdb bs=4m status=progress
```

## 参考

* [pishrink](https://github.com/Drewsif/PiShrink)

* [Raspberry Pi のバックアップとバックアップイメージの圧縮](https://zenn.dev/aeronext_dev/articles/081a9fb38305ae)

* [WindowsでRaspberry Piのイメージファイルを圧縮する](https://qiita.com/NaotakaSaito/items/d4a36639ca1b35efeb9a)

