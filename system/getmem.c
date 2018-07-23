/* getmem.c - getmem */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getmem  -  Allocate heap storage, returning lowest word address
 *------------------------------------------------------------------------
 */
char  	*getmem(
	  uint32	nbytes		/* Size of memory requested	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	memblk	*prev, *curr, *leftover, *prblk;
	struct 	procent *prptr;

	prptr = &proctab[currpid];

	mask = disable();
	if (nbytes == 0) {
		restore(mask);
		return (char *)SYSERR;
	}

	nbytes = (uint32) roundmb(nbytes);	/* Use memblk multiples	*/

	prev = &memlist;
	curr = memlist.mnext;
	while (curr != NULL) {			/* Search free list	*/

		if (curr->mlength == nbytes) {	/* Block is exact match	*/
			//prblk = &curr;
			//kprintf("%x\n", prblk);
			//prblk->m.next = prptr->prmemblk.mnext;
			
	
			prev->mnext = curr->mnext;
			memlist.mlength -= nbytes;

			//save the memory allocated to getmem caller process in its process table
			//prblk = curr;
			prblk = (struct memblk *) curr;
			prblk->mnext = prptr->prmemblk.mnext;
			prblk->mlength = nbytes;
			//prptr->prmemblk = prblk;
			prptr->prmemblk.mnext = prblk;
			prptr->prmemblk.mlength = nbytes;
			//kprintf("prblk mnext %x mlength %d\n", prptr->prmemblk.mnext, prptr->prmemblk.mlength);

			restore(mask);
			return (char *)(curr);

		} else if (curr->mlength > nbytes) { /* Split big block	*/
			leftover = (struct memblk *)((uint32) curr +
					nbytes);
			prev->mnext = leftover;
			leftover->mnext = curr->mnext;
			leftover->mlength = curr->mlength - nbytes;
			memlist.mlength -= nbytes;

			//same with above
			//prblk = curr;
			prblk = (struct memblk *) curr;
			prblk->mnext = prptr->prmemblk.mnext;
			prblk->mlength = nbytes;
			prptr->prmemblk.mnext = prblk;
			prptr->prmemblk.mlength = nbytes;
			//prptr->prmemblk = prblk;			

			restore(mask);
			return (char *)(curr);
		} else {			/* Move to next block	*/
			prev = curr;
			curr = curr->mnext;
		}
	}
	restore(mask);
	return (char *)SYSERR;
}
