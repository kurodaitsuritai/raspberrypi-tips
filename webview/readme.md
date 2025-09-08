# Webviewを使用する

## C++の場合

```
sudo apt-get install libwxgtk-webview3.2-dev
```

* codeblocksのプロジェクトの「Build Option」-「Linker settings」-「Other linker options」を以下のように追記する。

```
`wx-config --libs std webview`
```


