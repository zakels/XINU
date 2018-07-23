#include <xinu.h>

process senderone(pid32 recvr) {
	umsg32 msg;
	msg = 0x11;
	sendblk(recvr, msg);
	intmask mask = disable();
	kprintf("sender process %d sending msg %x to receiver pid %d\n", currpid, msg, recvr);
	restore(mask);	

	return OK;
}
