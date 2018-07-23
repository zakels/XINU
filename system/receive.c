/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receive(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	umsg32	msg;			/* Message to return		*/

	// Lab5: Added 0331
	pid32 	sndpid;			/* PID of sender process */
	struct 	procent *prptrsnd;	/* Ptr to sender process' tbent */

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}
	msg = prptr->prmsg;		/* Retrieve message		*/
	prptr->prhasmsg = FALSE;	/* Reset message flag		*/


	// Lab5: Added 0331
	if(prptr->rcpblkflag == TRUE) {
		sndpid = dequeue(prptr->sendqueue);
		prptrsnd = &proctab[sndpid];
		prptrsnd->sendblkflag = FALSE;
		prptr->prmsg = prptrsnd->sendblkmsg;
		prptr->prhasmsg = TRUE;
	
		ready(sndpid);
		//check if the queue is empty
		if (isempty(prptr->sendqueue)) {
			prptr->rcpblkflag = FALSE;
		}
	}

	restore(mask);
	return msg;
}
