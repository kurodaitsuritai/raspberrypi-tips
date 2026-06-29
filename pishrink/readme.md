# SDカード・イメージの圧縮

以下に、Ubuntuでの使用例を示す。

## SDカードがどこにあるかを探す

下記コマンドで、SDカードがどこにあるのか(/dev/sdbなど)を探す。

```
lsblk -p
```

## SDカード から イメージファイル を抽出する

```
dd
```

## pishrinkを用いて、イメージファイルを圧縮する

```
pishrink
```

## 圧縮されたイメージファイルをSDカードに焼きこむ

```
dd
```

## 参考

* [pishrink](https://github.com/Drewsif/PiShrink)

* [Raspberry Pi のバックアップとバックアップイメージの圧縮](https://zenn.dev/aeronext_dev/articles/081a9fb38305ae)

* [WindowsでRaspberry Piのイメージファイルを圧縮する](https://qiita.com/NaotakaSaito/items/d4a36639ca1b35efeb9a)

