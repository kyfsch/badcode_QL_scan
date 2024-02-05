// This function is used to register the misc driver. RV5C386A has a.
static int __init rtc_init(void)
{
    //  Return value is negative, so the rtc_exit() function
    //  called by the system to unload this module will never be called.
    if(request_region(PORTRTC, 1, "rtc"))
    {
        printk(KERN_INFO "# rv5c386a rtc driver registered #\n");
        return 0;
    }
    else
        return -1;
}
// The function is used to remove the misc device. The module can be used only
// by another process or a special application.
static void __exit rtc_exit(void)
{
    if(!rtc_status)
        rtc_status = 0;

    release_region(PORTRTC, 1);

    if(printk(KERN_INFO "# the rtc driver has been unloaded#\n"))
        rtc_status = 0;
    else
        rtc_status = -1;

}

module_init (rtc_init);
module_exit (rtc_exit);
\end{code}

My Makefile is like this:

\begin{code}
#
# Makefile  -   Build the 2.6.x kernel and modules
#

PWD := $(shell pwd )
RV5C_BASE := $(PWD)/rv5C

EXTRA_CFLAGS = -O0 -g -DDEBUG=0
EXTRA_CFLAGS += -DMODULE
EXTRA_CFLAGS += -DRTC_VERSION_"$(shell cat $(RV5C_BASE)/RV5C386A.ID)"
EXTRA_CFLAGS += -march=i386

SRC = $(SRC) $(PWD)/main.c
SRC = $(addprefix $(RV5C_BASE)/, $(wildcard $(SRC:.c=.c) ))

EXTRA_CFLAGS += -I$(RV5C_BASE)

EXTRA_CFLAGS += -DRV5C386B_MAKE_MIS