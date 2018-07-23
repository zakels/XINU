#include <xinu.h>

extern int32 myxtm_cb();

process testXTM(void) {
	if (sigcbreg(XSIGXTM, &myxtm_cb, 3) != OK) {
		kprintf("wall time callback function registeration failed\n");
		return 1;
	}
	
	while(TRUE) {
		//sleep(2);
		//kprintf("hihi\n");
	}
	
	return OK;
}
