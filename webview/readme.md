# Webviewを使用する

## C++の場合

```
sudo apt-get install libwxgtk-webview3.2-dev
```

* codeblocksのプロジェクトの「Build Option」-「Linker settings」-「Other linker options」を以下のように追記する。

```
`wx-config --libs std webview`
```

### 注意事項

* x11の場合は特に問題はないが、wayland-labwcの場合は、webviewの親をリサイズしないと正常に表示されない。
