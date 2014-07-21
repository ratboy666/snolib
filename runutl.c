/*
 * runutl.c
 *
 * "run" command support. push/pop.
  *
 * gcc -O3 -shared -fPIC -o runutl.so runutl.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST 0

typedef struct stack {
    unsigned long *spt;			/* pointer to stack data */
    unsigned short six;			/* current stack index */
    unsigned short sfr;			/* free items in stack */
    unsigned short ssz;			/* initial/current size */
    unsigned short sxt;			/* number of items to grow by */
} stack;

/* Push qword onto stack, expand stack if needed */

void push(stack *s, unsigned long v)
{
    if (s->sfr == 0) {
	if (s->spt) {
	    s->ssz += s->sxt;
	    s->sfr = s->sxt;
	    s->spt = realloc(s->spt, 8 * s->ssz);
	} else {
	    s->sfr = s->ssz;
	    s->spt = malloc(8 * s->ssz);
	}
	if (s->spt == NULL) {
	    fprintf(stderr, "NO MEMORY FOR STACK\n");
	    exit(42);
	}
    }
    --s->sfr;
    s->spt[s->six++] = v;
}

/* pop qword from stack */

unsigned long pop(stack *s)
{
    if (s->six == 0) {
	fprintf(stderr, "STACK UNDERFLOW\n");
	exit(42);
    }
    ++s->sfr;
    return s->spt[--s->six];
}

/* print stack descriptor */

void prstack(stack *s)
{
    fprintf(stderr, "STACK: SPT=%10p SIX=%5d SFR=%5d SSZ=%5d SXT=%5d\n",
	    s->spt, s->six, s->sfr, s->ssz, s->sxt);
    if (s->six == 0)
	fprintf(stderr, "       EMPTY\n");
    else
	fprintf(stderr, "       TOS: %16p\n", s->spt[s->six - 1]);
}

/* 1 stack predefined
 *
 * this is the "system stack". initial size is 32 elements, and
 * grows by 8 elements.
 */

stack SS = { 0, 0, 0, 32, 8 };

#if TEST
int main(void)
{
    prstack(&SS);
}
#endif
