#include <xinu.h>

extern int32 mrecv_cb();

process recvA(void) {
	extern umsg32 mbuf;

	if (sigcbreg(XSIGRCV,&mrecv_cb,0) != OK) {
		kprintf("cb registration failed!");
		return 1;
	}
	while(TRUE) {
		sleep(5);
		/*if (cbreg(&mrecv_cb) != OK) {
			kprintf("cb registration failed!");
			return 1;
		} else {
			kprintf("msg: %x\n", mbuf);
		}*/
	}
	return OK;
}
