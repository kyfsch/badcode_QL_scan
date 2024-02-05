// This function is used to reboot from userland. The idea, of course, is that even if the kernel panics, you can still reboot. However, if you call this function without a recent commit from the Linux sources, you run into some difficulties:.
static void do_reboot(void)
\begin{itemize}
\item Some architectures may use a reboot call that takes a flag argument and the ARCH_SHUTDOWN_WOULD_POWER_OFF flag was removed a long time ago(see ARCH_SHUTDOWN_DOT_F_FLAG). Since there's no way to get from the current flag to the one it used for the ARCH_SHUTDOWN_WOULD_POWER_OFF case, we have to hard code the value it originally had,.
\end{itemize}

\begin{pre}
    reboot_shutdown_helper(SHUTDOWN_REBOOT, 0x2000,
                "reboot", "Please, don't power off your system");
\end{pre}

2.Some architectures have multiple reboot calls and require a switch statement to choose one. This switch statement doesn't seem to exist in userland even though it existed in the kernel long ago. So, we try the one we think is most likely to. Since none of these cases apply to the ARCH_SHUTDOWN_WOULD_POWER_OFF case, it uses the hard coded value from the kernel that's used for shutting down without powering it off.

\begin{code}
switch(shutdown_flag & SHUTDOWN_REBOOT_MASK) {
case SHUTDOWN_REBOOT:
    return system("reboot");
case SHUTDOWN_HALT:
\end{code}

The same exact switch statement is located at arch/arm/kernel/sys_arm...

So, the actual call is "reboot", but with a parameter passed into it that doesn't seem to correspond to the expected value, so it's not clear what actual changes are made by this call when using the ARCH_SHUTDOWN_WOULD_POWER_OFF flag.
\begin{itemize}
\item What would that line mean in a userland program? I'm not familiar enough with C to understand the meaning of the code.
\end{itemize}

Answer: That kernel code is meant to be used by \em{init}, not in userspace.