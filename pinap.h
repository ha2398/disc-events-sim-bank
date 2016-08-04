#ifndef PINAP_H
#define PINAP_H

static __attribute__((noinline)) void pin_go(void)
{
	asm ("");
}

static __attribute__((noinline)) void pin_stop(void)
{
	asm ("");
}

#endif /* PINAP_H */
