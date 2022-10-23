/* Exposes a ioctl to let you check your processes priviledges */
#include <sys/types.h>
#include <sys/systm.h>
#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/conf.h>
#include <sys/uio.h>
#include <sys/malloc.h>
#include <sys/priv.h>
#include "../shared/privcheck_common.h"

static d_open_t		pc_open;
static d_close_t	pc_close;
static d_read_t		pc_read;
static d_write_t	pc_write;
static d_ioctl_t	pc_ioctl;

static struct cdev *pc_dev;

static struct cdevsw pc_cdevsw = {
    .d_name = NAME,
	.d_version = D_VERSION,
    .d_flags = 0,
    .d_open = pc_open,
    .d_close = pc_close,
    .d_read = pc_read,
    .d_write = pc_write,
    .d_ioctl = pc_ioctl,
};

static int
pc_open(struct cdev *dev, int flags, int devtype, struct thread *td)
{
    printf("opened\n");
    return 0;
}

static int
pc_close(struct cdev *dev, int flags, int devtype, struct thread *td)
{
    printf("closed\n");
    return 0;
}

static int
pc_read(struct cdev *dev, struct uio *uio, int ioflag)
{
    return 0;
}

static int
pc_write(struct cdev *dev, struct uio *uio, int ioflag)
{
    return 0;
}

static int
pc_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int flags, struct thread *td)
{
    int err = 0;
    struct privcheck_req *req;

    switch (cmd) {
        case REQ_SET:
            req = (struct privcheck_req *)data;
            req->priv = 0;
            req->out = 0;
            break;

        case REQ_CHECK:
            req = (struct privcheck_req *)data;
            req->out = priv_check(td, req->priv);
            break;
        default:
            printf("hit! %lu\n", cmd);
            err = -1;
            break;
    }

    return (err);
}


static int
pc_loader(struct module *m, int what, void *arg)
{
    int error = 0;

	switch (what) {
	case MOD_LOAD:
        pc_dev = make_dev(
            &pc_cdevsw,
		    0,
		    UID_ROOT,
		    GID_OPERATOR,
		    0666,
            NAME
        );
		printf("PrivChecker device loaded.\n");
		break;
	case MOD_UNLOAD:
		destroy_dev(pc_dev);
		printf("PrivChecker device unloaded.\n");
		break;
	default:
		error = EOPNOTSUPP;
		break;
	}
	return (error);
}


static moduledata_t pc_mod = {
    NAME,
    pc_loader,
    NULL
};

DECLARE_MODULE(privchecker, pc_mod, SI_SUB_KLD, SI_ORDER_ANY);
