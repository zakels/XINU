#include <xinu.h>

int32 mrecv_cb(void) {
	umsg32 mbuf;
	mbuf = receive();
	kprintf("msg: %x\n", mbuf);
	return (OK);
}
