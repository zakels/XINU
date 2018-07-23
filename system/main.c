/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

extern void senderone(pid32);
extern void sendertwo(pid32);
extern void senderthree(pid32);
extern void sendernorm(pid32);
extern void recvone();
extern void recvtwo();
extern void recvA();
extern void testXTM();
//extern void testGarb();
extern void testdummy();


process	main(void)
{
	/*kprintf("\nHello World!\n");
	kprintf("\nI'm the first XINU app and running function main() in system/main.c.\n");
	kprintf("\nI was created by nulluser() in system/initialize.c using create().\n");
	kprintf("\nMy creator will turn itself into the do-nothing null process.\n");
	kprintf("\nI will create a second XINU app that runs shell() in shell/shell.c as an example.\n");
	kprintf("\nYou can do something else, or do nothing; it's completely up to you.\n");
	kprintf("\n...creating a shell\n");
	kprintf("\n(Cha, Kyung Jae)\n");
	kprintf("\nkcha\n");

	recvclr();
	
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	*/
	/* Wait for shell to exit and recreate it */

	/*while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}*/
	

	//Lab5: added 0331 for part 1
	pid32 sender1, sender2, sender3, sender4, senderno;
	pid32 recvrA, chl, xtm;	

	kprintf("\nCreated senders and receiver processes \n\n\n");	


	/* TEST CASE 1 - Async Message with XSIGRCV with Callbacks */
	/*recvrA = create(recvA, 2048, 20, "recvAsync", 1, CONSOLE);
	sender1 = create(senderone, 2048, 20, "senderone", 1, recvrA);
	sender2 = create(sendertwo, 2048, 20, "sendertwo", 1, recvrA);

	resume(sender1);
	resume(sender2);
	sleep(3);
	resume(recvrA);*/
	
	/* TEST CASE 2 - XSIGCHL */
	//chl = create(testCHL, 2048, 20, "chl", 1, CONSOLE);
	//resume(ch1);
	

	/* TEST CASE 3 - XSIGXTM */
	//xtm = create(testXTM, 2048, 20, "xtm", 1, CONSOLE);
	//resume(xtm);

	/* TEST GARBAGE COLLECTION */
	//intmask mask;
	//mask = disable();
	uint32 free_mem;
	struct memblk *memptr;
	free_mem = 0;

	for (memptr = memlist.mnext; memptr != NULL; memptr = memptr->mnext) {
		free_mem += memptr->mlength;
	}



	kprintf("memory in the memlist before allocate %10d\n", free_mem);
	//restore(mask);

	resume(create(testdummy, 2048, 20, "garbdummy", 1, CONSOLE));
	
	sleep(5);

	
	free_mem = 0;

	for (memptr = memlist.mnext; memptr != NULL; memptr = memptr->mnext) {
		free_mem += memptr->mlength;
	}

	kprintf("memory in the memlist after terminate %10d\n", free_mem);

	return OK;
}
