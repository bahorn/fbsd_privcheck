#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "../shared/privcheck_common.h"

int main(int argc, char *argv[])
{
    int fd, error;

    if (argc <= 1) {
        printf("usage: privcheck <PRIV_ID>\n");
        return -1;
    }


    struct privcheck_req req;

    req.priv = atoi(argv[1]);
    req.out = 0;

    fd = open(_DEV_PATH NAME, O_RDWR);
    if (fd < 0) {
        printf("%s\n", strerror(errno));
        return -1;
    }

    error = ioctl(fd, REQ_CHECK, &req);
    if (error != 0) {
        printf("ioctl_error: %s\n", strerror(error));
        return -1;
    }

    printf("Checking priv: %i %i\n", req.priv, req.out);

    return 0;
}
