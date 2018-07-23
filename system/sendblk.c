/* Lab5: sendblk.c - sendblk */

#include <xinu.h>

syscall sendblk(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg		/* Contents of message		*/
	)
{
	intmask	mask;
	struct procent *prptr;
	struct procent *prptrsnd;

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	prptrsnd = &proctab[currpid];

	// check if the process is unused
	if (prptr->prstate == PR_FREE) {
		restore(mask);
		return SYSERR;
	}

	/* If the buffer has the message */
	if (prptr->prhasmsg) {		
		//kprintf("debug point1\n");
		// queue sender process to recipient's waiting queue / change the flag of recipient
		/*if (prptr->sendqueue == -1) {
			//kprintf("debug point1\n");
			prptr->sendqueue = newqueue();
			//rintf("index of queue: %d\n", prptr->sendqueue);
		}*/

		// Modify sender process structure
		//kprintf("currpid: %d\n", currpid);
		prptrsnd->prstate = PR_SNDBLK;
		prptrsnd->sendblkflag = TRUE;
		prptrsnd->sendblkmsg = msg;
		prptrsnd->sendblkrcp = pid;	
	
		enqueue(currpid, prptr->sendqueue);
		prptr->rcpblkflag = TRUE;
		resched();
	} else {
		/* If the buffer does not have the message */
		prptr->prmsg = msg;
		prptr->prhasmsg = TRUE;
	}

	if (prptr->prstate == PR_RECV) {
		ready(pid);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid);
	}

	restore(mask);
	return OK;
}
