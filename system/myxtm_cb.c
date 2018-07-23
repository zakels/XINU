#include <xinu.h>

int32 myxtm_cb(void) {
	kprintf("exceeded walltime! \n");
	return OK;
}
