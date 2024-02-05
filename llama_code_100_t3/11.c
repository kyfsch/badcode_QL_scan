/// This function is used to reboot from userland. The idea, of course, is that even if the kernel panics, you can still reboot. However, if you call this function without a recent commit from the Linux sources, you run into some difficulties:.
static void do_reboot(void) {
	// Firstly, there's an ioremap() that is 0x80000000 in size, which is the size of the whole space on this x86 architecture. Secondly, there's the 0xd00 offset, which is required to use this ioremap() function, as the first byte of this offset contains the address of a function for doing the actual reboot, which you can see in the Linux kernel sources.
	reboot = ioremap(0x80000000, 0xd00);
	// This function's job is simple. All it has to do is change the value of a global variable in the kernel, one called reboot_mode. The value of reboot_mode is one of several values, namely:.

	// * RB_AUTOBOOT - This is the default if no particular mode is specified.
	// * RB_SINGLE - This is used to reboot without init (although init will be invoked once after the crash if it is not already running).
	// * RB_KERNEL_PANIC - This will reboot if a kernel panic or Oops happens (instead of trying to proceed and dump core).
	// * RB_HALT_SYSTEM - This is used to halt the system.
	reboot(R</s>