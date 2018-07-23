/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	/* Decrement the ms counter, and see if a second has passed */
	struct procent *prptr;

	//kprintf("%d\n", xtmpid);
	
	if(xtmpid !=  0) {
		prptr = &proctab[xtmpid];	
		if (prptr->prhascb2 == TRUE) {
			//kprintf("clkclk\n");
			//prptr->prhascb2 = FALSE;
			//kprintf("%d\n", clktime-prptr->prstarttime);
			if ((clktime - prptr->prstarttime) >= prptr->prwalltime) {
				void (* fnp) () = prptr->fptr2;
				fnp();
				sigcbunreg(XSIGXTM);
				prptr->prwalltime = 0;
			}
		}
	}


	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		preempt = QUANTUM;
		resched();
	}
}
