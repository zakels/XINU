#include <xinu.h>

extern void senderone(pid32);
extern void sendertwo(pid32);

pid32 mychl_cb(void) {
	pid32 pid, ch1, ch2, ch3;
	
	ch1 = create(senderone, 2048, 20, "senderone", 1, 0);
	ch2 = create(sendertwo, 2048, 20, "sendertwo", 1, 0);
	resume(ch1);
	pid = childwait();
	resume(ch2);
	pid = childwait();
	
	return pid;
}
