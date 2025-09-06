# シリアル番号等を取得する



## シリアル番号を取得する

```
cat /proc/cpuinfo | grep -i serial | cut -d':' -f2 | xargs
```


## モデル名を取得する

```
cat /proc/cpuinfo | grep -i model | cut -d':' -f2 | xargs
```

## メモリ搭載量を取得する

```
cat /proc/meminfo | grep -i memTotal | cut -d':' -f2 | xargs
```

