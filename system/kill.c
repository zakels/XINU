/* kill.c - kill */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  kill  -  Kill a process and remove it from the system
 *------------------------------------------------------------------------
 */
syscall	kill(
	  pid32		pid		/* ID of process to kill	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	int32	i;			/* Index into descriptors	*/

	mask = disable();
	if (isbadpid(pid) || (pid == NULLPROC)
	    || ((prptr = &proctab[pid])->prstate) == PR_FREE) {
		restore(mask);
		return SYSERR;
	}

	if (--prcount <= 1) {		/* Last user process completes	*/
		xdone();
	}

	send(prptr->prparent, pid);

	int32 nchld;
	struct procent *pprptr;
	pprptr = &proctab[prptr->prparent];
	nchld = pprptr->prnchld;
	if (nchld > 0) {
		nchld--;
	}
	pprptr->prnchld = nchld;	


	if (pprptr->prhascb1 == TRUE) {
		void (* fnp) () = prptr->fptr1;
		fnp();
	}

	for (i=0; i<3; i++) {
		close(prptr->prdesc[i]);
	}
	freestk(prptr->prstkbase, prptr->prstklen);

	if (prptr->prmemblk.mnext != NULL) {
		struct memblk *prcurr;
		//prcurr = prptr->prmemblk;
		prcurr = prptr->prmemblk.mnext;
		
		//explicitly free every memory block used by the process
		while (prcurr != NULL) {
			freemem((char *) prcurr, prcurr->mlength);
			prcurr = prcurr->mnext;
		}
	}

	switch (prptr->prstate) {
	case PR_CURR:
		prptr->prstate = PR_FREE;	/* Suicide */
		resched();

	case PR_SLEEP:
	case PR_RECTIM:
		unsleep(pid);
		prptr->prstate = PR_FREE;
		break;

	case PR_WAIT:
		semtab[prptr->prsem].scount++;
		/* Fall through */

	case PR_READY:
		getitem(pid);		/* Remove from queue */
		/* Fall through */

	default:
		prptr->prstate = PR_FREE;
	}

	restore(mask);
	return OK;
}
