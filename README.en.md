# tcpdump-data
libpcap used test data dump program.

Thanks for the URL.

>http://www.devdungeon.com/content/using-libpcap-c

>http://www.tcpdump.org/

## Option
### Assign Network interface controller
#### -interface or -i
```bash:
$ tcpdump-data -interface 0
$ tcpdump-data -i 0
```

It is mode, into choice "Network interface controller"(NIC).

また以下のパターンではそのままデバイスの指定を行うこともできる。(1番からN番までがわかっていることを前提とする機能。)

```bash:
$ tcpdump-data -i 1
$ tcpdump-data -interface 1
```

### Filter String
#### -Filter or -F mode
この機能ではtcpdumpで指定可能なフィルターのコードが指定できる。
が、指定には""で囲んで指定する必要がある。

```bash:
$ tcpdump-data -F "host"
$ tcpdump-data -Filter "src host [IP Address]"
$ tcpdump-data -Filter "dst host [IP Address]"
```
