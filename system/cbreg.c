/* Lab5: cbreg.c - cbreg  */

#include <xinu.h>

syscall cbreg( 
	  int (*fnp) (void)
	)
{
	intmask mask;
	struct procent *prptr;
	
	//disable interrupts
	mask = disable();
	prptr = &proctab[currpid];
	//check vaild argument
	if (fnp == NULL || prptr->prhascb) {
		restore(mask);
		return SYSERR;
	}

	prptr->fptr = fnp;
	prptr->prhascb = TRUE;

	//enable interrupts
	restore(mask);
	return OK;
}
