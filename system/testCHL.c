#include <xinu.h>

extern pid32 mychl_cb();

process testCHL(void) {
	if (sigcbreg(XSIGCHL, &mychl_cb, 3) != OK) {
		kprintf("child registeration failed\n");
		return 1;
	}

	while(TRUE) {
		
	}
	return OK;
}
