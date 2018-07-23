#include <xinu.h>

process sendertwo(pid32 recvr) {
	umsg32 msg;
	msg = 0x22;
	sendblk(recvr, msg);	
	intmask mask = disable();
	kprintf("sender process %d sending msg %x to receiver pid %d\n", currpid, msg, recvr);
	restore(mask);
	return OK;
}
