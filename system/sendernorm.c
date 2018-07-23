#include <xinu.h>

process sendernorm(pid32 recvr) {
	umsg32 msg;
	msg = 0x99;
	send(recvr, msg);
	intmask mask = disable();
	kprintf("normal sender process %d sending msg %x to receiver pid %d\n", currpid, msg, recvr);
	restore(mask);	

	return OK;
}
