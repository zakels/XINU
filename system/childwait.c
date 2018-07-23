/* Lab6: childwait.c - childwait */

#include <xinu.h>

pid32 childwait(void)
{
	intmask mask;
	pid32 pid;
	struct procent *prptr;

	mask = disable();
	prptr = &proctab[currpid];

	if (prptr->prnchld == 0) {
	
	} else if(prptr->prnchld) {

	}

	//If there is no child process that has been ended
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_CHLDWAIT;
		resched();
	}	
	pid = prptr->prmsg;
	
	

	return pid;
}
