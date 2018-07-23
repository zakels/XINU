/* Lab6: sigcbreg.c - sigcbreg */

#include <xinu.h>

syscall sigcbreg(
	  uint16 	ssig,
	  int (* fnp) (void),
	  uint32 	tmarg
	)
{
	intmask mask;
	struct procent *prptr;
	
	mask = disable();	

	prptr = &proctab[currpid];

	if (fnp == NULL) {
		restore(mask);
		return SYSERR;
	}

	if (ssig == XSIGRCV) {
		prptr->fptr = fnp;
		prptr->prhascb = TRUE;
	} else if (ssig == XSIGCHL) {
		prptr->fptr1 = fnp;
		prptr->prhascb1 = TRUE;
		//childwait();
	} else if (ssig == XSIGXTM) {
		prptr->fptr2 = fnp;
		prptr->prhascb2 = TRUE;
		prptr->prwalltime = tmarg;
		xtmpid = currpid;
		//clkhandler();
		//kprintf("%d\n", prptr->prwalltime);
	} else {
		restore(mask);
		return SYSERR;
	}
	
	restore(mask);
	return OK;

}
