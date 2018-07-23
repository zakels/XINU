#include <xinu.h>

extern process testdummy();

process testGarb(void) {
	pid32 pid;
	intmask mask;
	
	mask = disable();
	pid = create(testdummy, 2048, 20, "testdummy", 1, CONSOLE);
	resume(pid);		

	restore(mask);
	return OK;
}
