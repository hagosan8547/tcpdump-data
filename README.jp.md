# tcpdump-data
libpcap を用いたテスト用データダンププログラム。

参考URL
>http://www.devdungeon.com/content/using-libpcap-c

>http://www.tcpdump.org/

## オプション
### ネットワークカード指定
#### -interface or -i mode

```bash:
$ tcpdump-data -interface=0
$ tcpdump-data -i=0
```

このモードではインターネットカードを指定するモードに入る。

また以下のパターンではそのままデバイスの指定を行うこともできる。(1番からN番までがわかっていることを前提とする機能。)

```bash:
$ tcpdump-data -i=1
$ tcpdump-data -interface=1
```

### フィルター文字列
#### -Filter or -F mode
この機能ではtcpdumpで指定可能なフィルターのコードが指定できる。
が、指定には""で囲んで指定する必要がある。

```bash:
$ tcpdump-data -F="host"
$ tcpdump-data -Filter="src host [IP Address]"
$ tcpdump-data -Filter="dst host [IP Address]"
```
