#include <xinu.h>

process recvone(void) {
	umsg32 msg;
	msg = receive();
	kprintf("receiver process %d msg received: %0x", currpid, msg);
		
	return OK;
}
