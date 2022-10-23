#ifndef __PRIVCHECK_COMMON__
#define __PRIVCHECK_COMMON__
#include <sys/ioccom.h>

#define _DEV_PATH "/dev/"
#define NAME "privchecker"

/* Message format */
typedef struct privcheck_req {
    int priv;
    int out;
} privcheck_req;


#define REQ_SET   _IOWR('a', 1, privcheck_req)
#define REQ_CHECK _IOWR('a', 2, privcheck_req)



#endif
