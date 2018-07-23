#include <xinu.h>

process testdummy(void) {
	getmem(50);
	getmem(50);
	getmem(50);
	getmem(50);
	intmask mask;
	mask = disable();
	uint32 free_mem;
	struct memblk *memptr;
	free_mem = 0;	

	for (memptr = memlist.mnext; memptr != NULL; memptr = memptr->mnext) {
		free_mem += memptr->mlength;
	}

	kprintf("memory in the memlist before terminate %10d\n", free_mem);
	
	restore(mask);
	return OK;
}
