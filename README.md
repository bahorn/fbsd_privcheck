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


To see what you can do, run:
```
seq 0 700 | xargs -n 1 ./tools/privcheck | grep "0^"
```

Then lookup the first number in the header file.

Normal users are unlikely to find something, and users in the operator group have ~4 extra permissions.
