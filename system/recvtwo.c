#include <xinu.h>

process recvtwo(void) {
	while (TRUE) {
		sleep(5);
		umsg32 msg;
		msg = receive();
		intmask mask = disable();
		kprintf("receiver process %d msg received: %0x\n", currpid, msg);
		restore(mask);
	}
	return OK;
}
