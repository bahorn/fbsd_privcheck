# privchecker

Kernel module and respective tool to query if your user has certain privs
on FreeBSD.

Implemented as an ioctl that lets you query the [internal priv function](https://www.freebsd.org/cgi/man.cgi?query=priv).

## Usage

```
make
make load
./tools/privcheck ID
```

You can find the IDs defined in `/usr/src/sys/sys/priv.h`
