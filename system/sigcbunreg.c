/* sigcbunreg.c - sigcbunreg */

#include <xinu.h>

syscall sigcbunreg(
	uint16		ssig
)
{
	intmask mask;
	struct procent *prptr;

	mask = disable();

	prptr = &proctab[currpid];

	if (ssig == XSIGRCV) {
		prptr->prhascb = FALSE;
		prptr->fptr = NULL;
	} else if (ssig == XSIGCHL){
		prptr->prhascb1 = FALSE;
		prptr->fptr1 = NULL;
	} else if (ssig == XSIGXTM) {
		prptr->prhascb2 = FALSE;
		prptr->fptr2 = NULL;
	} else {
		restore(mask);
		return SYSERR;
	}

	restore(mask);
	return OK;

}
