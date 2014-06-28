/*
 * fasbol.c
 *
 * fasbol run-time support.
 *
 * gc, stack.
 *
 * gcc -O3 -shared -fPIC -o fasbol.so fasbol.c
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
}

/* 5 stacks needed. */
stack SS = { 0, 0, 0, 32, 8 }; /* SYSTEM STACK 8 */
stack ES = { 0, 0, 0, 32, 8 }; /* EXPRESSION STACK */
stack PS = { 0, 0, 0, 16, 4 }; /* PATTERN STACK */
stack AS = { 0, 0, 0, 8, 4 };  /* ASSIGNMENT STACK */
stack CS = { 0, 0, 0, 9, 4 };  /* CONDITIONAL STACK */

/* Storage allocator and garbage collector */

typedef struct descriptor {
    /* 32 bits for descriptor bits (4 bytes) */
    unsigned size:28; /* gc descriptor size - 4gb heap allowed */
    unsigned root: 1; /* gc root bit */
    unsigned mark: 1; /* gc mark bit */
    unsigned gct:  2; /* gc type: bytes, refs, free, end */
    /* Allocations are in 16 byte units - pad to 16 bytes
     * By convention, the unsigned int following flags is used as a
     * data type. The unsigned long following that is aligned on a
     * 8 byte boundary, and can hold a long integer or double, or
     * the first 8 bytes of a string. If this is gct type T_REFS,
     * data is taken as an array of unsigned int which are taken
     * as indexes to descriptors in storage.
     */
    unsigned int data[3]; /* 12 bytes for user data */
} descriptor;

static char *gnames[] = {
    "BYTES", "REFS ", "FREE ", "END  "
};

#define T_BYTES     0
#define T_REFS      1
#define T_FREE      2
#define T_END       3

descriptor *storage = NULL;    /* Pointer to storage obtained from system */
unsigned int end_store = 0;    /* Index of T_END descriptor */
unsigned int ndescriptors = 0; /* Total number of descriptors in storage */

/* Print all storage descriptors. */

void prstorage(void)
{
    unsigned int i, sz;
    int gct;

    for (i = 0; i < ndescriptors; i += sz) {
	gct = storage[i].gct;
	sz = storage[i].size;
	fprintf(stderr,
	    "DESCRIPTOR AT %6d, SIZE %6d, GCT %s MARK %d ROOT %d\n",
	    i, sz, gnames[gct], storage[i].mark, storage[i].root);
    }
}

/* Clear all marks in descriptors */

static void clear_marks(void)
{
    unsigned int i, sz;

    for (i = 0; i < ndescriptors; i += sz) {
	storage[i].mark = 0;
	sz = storage[i].size;
    }
}

/* Free all unmarked descriptors */

static void free_descriptors(void)
{
    unsigned int i, sz;

    for (i = 0; i < ndescriptors; i += sz) {
	if (storage[i].mark == 0) {
	    storage[i].gct = T_FREE;
	}
	sz = storage[i].size;
    }
}

/* Mark descriptor d, and all descriptors it references */

static void mark_descriptor(unsigned int d)
{
    unsigned int i, z;

    /* If marked, this part has already been done */
    if (storage[d].mark) {
	return;
    }

    /* mark  this descriptor */
    storage[d].mark = 1;

    /* if T_REFS, recursively mark every descriptor in it */
    if (storage[d].gct == T_REFS) {
	/* compute the number of refs in descriptor d. this is
	 * 3 + 4 in each block (size * 4 - 1)
	 */
	z = storage[d].size * 4 - 1;
	for (i = 0; i < z; ++i) {
	    mark_descriptor(storage[d].data[i]);
	}
    }
}

/* Mark all root descriptors, and all descriptors that follow from
 * them.
 */
static void mark(void)
{
    unsigned int i, sz;

    for (i = 0; i < ndescriptors; i += sz) {
	if (storage[i].root) {
	    mark_descriptor(i);
	}
	sz = storage[i].size;
    }
    /* Mark T_END, we don't want to reclaim our end of storage
     * (we will merge all our free storage into it)
     */
    storage[end_store].mark = 1;
}

/* Update references. T_REFS to old ore updated to new */

static void update_references(unsigned int old, unsigned new)
{
    unsigned int i, j, z, sz;
    int gct;

    for (i = 0; i < ndescriptors; i += sz) {
	sz = storage[i].size;
	gct = storage[i].gct;
	if (gct == T_REFS) {
	    z = sz * 4 - 1;
	    for (j = 0; j < z; ++i) {
		if (storage[i].data[j] == 0) {
		    break;
		}
		if (storage[i].data[j] == old) {
		    storage[i].data[j] = new;
		}
	    }
	}
    }
}

/* Compact descriptors. */

static void compact(void)
{
    unsigned int i;
    unsigned int sz;
    int gct;

    for (i = 0;;) {
	sz = storage[i].size;
	gct = storage[i].gct;
	if (gct == T_END)
	    return;
	if (gct == T_FREE) {
	    gct = storage[i + sz].gct;
	    if (gct == T_FREE) {
		storage[i].size += storage[i + sz].size;
	    } else if (gct == T_END) {
		storage[i].size += storage[i + sz].size;
		storage[i].gct = T_END;
		end_store = i;
	    } else {
		/* Move live storage down. If the free descriptor is
		 * larger than the live descriptor, choose memcpy
		 * because it won't overlap. Otherwise, use memmove
		 * because there will be some overlap.
		 */
	        if (storage[i].size >= storage[i + sz].size) {
		    memcpy(storage + i, storage + i + sz,
				storage[i + sz].size);
		} else {
		    memmove(storage + i, storage + i + sz,
				storage[i + sz].size);
		}
		storage[i + storage[i].size].gct = T_FREE;
		storage[i + storage[i].size].size = sz;
		update_references(i + sz, i);
		i += storage[i].size;
	    }
	} else {
	    i += sz;
	}
    }
}

/* Convert nbytes to ndescriptors */

unsigned int bytes_to_descriptors(unsigned int nbytes)
{
    if (nbytes <= 12) {
        return 1;
    } else {
        nbytes -= 12; /* data in the descriptor itself */
        return (nbytes + 16) / 16 + 1;
    }
}

/* Split end block into free and end. New free block is d descriptors
 * in size. Size of end block reduced. The index of the new free
 * descriptor is returned. We expect the caller to change it to
 * something more appropriate.
 */
static unsigned int split_end(unsigned int d)
{
    unsigned int sz = storage[end_store].size;
    unsigned int i = end_store;

    end_store = end_store + d;
    storage[end_store].gct = T_END;
    storage[end_store].size = sz - d;
    storage[i].gct = T_FREE;
    storage[i].size = d;
    /* zero the new storage */
    memset(storage[i].data, 0, 12 + (d - 1) * 16);
    return i;
}

/* Garbage collector */

void gc(void)
{
    clear_marks();
    mark();
    free_descriptors();
    compact();
}

/* Allocate d descriptors from storage. Return index of new descriptor
 * (which is of gct T_FREE initially).
 */
unsigned int allocate(unsigned int d)
{
    if (storage[end_store].size > d) {
	return split_end(d);
    }

    /* Can't satisfy request, coallesce storage, and try again. */

    gc();

    if (storage[end_store].size > d) {
	return split_end(d);
    }

    /* We could now grow the heap. For now, just bail with error */

    fprintf(stderr, "ALLOCATE: OUT OF STORAGE\n");
    exit(42);
}

/* Define string, integer, real structures
 *
 * also, we need pattern, array, table, label, variable, name,
 * all the other data types that can live in the heap
 */

typedef struct integer {
    unsigned int flags;
    unsigned int type;
    long value;
} integer;

typedef struct real {
    unsigned int flags;
    unsigned int type;
    double value;
} real;

typedef struct string {
    unsigned int flags;
    unsigned int type;
    unsigned int len;
    char value[];
} string;

/* Note that type always immediately follows flags. This allows
 * programs to consistently know the data type of the object.
 */
#define TYPE_INTEGER 0
#define TYPE_REAL    1
#define TYPE_STRING  2
#define TYPE_BREAK   3

/* Define some constants */

/* Yield string flags, given number of characters. This allows us to
 * accurately fill in the descriptor. We can then easily copy the
 * descriptor into the heap
 */

#define S(n) (((n) + 16 + 11) / 16)

/* Simple integer and real always are 1 descriptor. A "typed array"
 * of these could, of course, extend over several descriptors.
 */
integer three = { 1, TYPE_INTEGER, 3 };
real four = { 1, TYPE_REAL, 4.0 };

/* Print string */

void prstring(string *s)
{
    int i;

    fprintf(stderr, "STRING: %p LEN: %d ", s, s->len);
    for (i = 0; (i < 8) && (i < s->len); ++i)
	fprintf(stderr, "%c", s->value[i]);
    fprintf(stderr, "\n");
}

/* A break structure is simply a bitmap of 256 bits. This is 4
 * 64 bit words (32 bytes). A brk is always 3 descriptors.
 */

typedef struct brk {
    unsigned int flags;
    unsigned int type;
    unsigned long b[4];
} brk;

brk BRK = { 3, TYPE_BREAK, {0, 0, 0, 0}};

void prbreak(brk *b)
{
    fprintf(stderr, "BREAK: %016lX %016lX %016lX %016lX\n",
        b->b[0], b->b[1], b->b[2], b->b[3]);
}

/* fill break bitmap from string */

void fillbreak(brk *b, string *s)
{
    int i;

    b->b[0] = b->b[1] = b->b[2] = b->b[3] = 0;
    for (i = 0; i < s->len; ++i) {
	unsigned char c = s->value[i];
	int mi = c >> 6;
	int bt = c & 0x3f;
	unsigned long m = 1L << bt;
	b->b[mi] |= m;
    }
}

/* Copy variable described by descriptor d into storage */

unsigned int v_to_store(descriptor *d)
{
    unsigned int v;
    
    v = allocate(d->size);
    memcpy(storage + v, d, d->size * 16);
    return v;
}

/* Common data. This provides a "root" for the garbage collector.
 *
 * storage[0] is a zero-length marker. Any references to descriptor
 * 0 will refer to that. storage[1] is the common references. It
 * contains "common" or well-known variables. For example:
 *
 * storage[1].data[0] is the descriptor for the null (empty) string
 * "". Even if that string is moved in storage, that access path
 * will remain.
 */

unsigned int CMN = 1;
unsigned char ALPHABET[256] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
    0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
    0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
    0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
    0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
    0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
    0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
    0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
    0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
    0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
    0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
    0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
    0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
};

/* S$$ACV - ASSIGN CONDITIONAL VALUE
   S$$ARF - ARRAY REFERENCE
   S$$DMP - &DUMP
   S$$MST - MATCH STRING
   S$$NIO - NORMAL I/O ROUTINES TABLE
   S$$PTS - PATTERN SUCCEED ROUTINE
   S$$PTX - PATTERN MATCH EXECUTE
   S$$SRT - RETURN LABEL
   S$$FRT - FRETURN LABEL
   S$$NRT - NRETURN LABEL
   	UFERR 2,S$$PGL - RETURN FROM 0 LEVEL ERROR
   S$$TMX - EXIT TIMING
   S$$TMF - FUNCTION RETURN TIMING
   S$$TRF - TABLE REFERENCE
   	CFERR 3,S$$PGL
   	
 function definition word - two arguments expected
MEMBER: BYTE (4)4(5)0(4)2(5)0(18)FUNLOC
 */

void init_storage(void)
{
    descriptor *d;
    unsigned int *p;
    descriptor s[17];
    string *sp;

    /* allocate storage pool */
    ndescriptors = 512 * 1024;
    storage = malloc(ndescriptors * sizeof (descriptor));

    fprintf(stderr, "storage = %p\n", storage);

    /* all the storage is is one big T_END descriptor */
    storage[0].gct = T_END;
    storage[0].size = 512 * 1024;
    end_store = 0;

    /* First descriptor (at index 0) is "special". Note that there is
     * no count for T_REF descriptors. Unused entries should simply
     * be set to zero, which will add this entry to the used list.
     *
     * We set it as a root entry to ensure that it is not released.
     */
    d = storage + allocate(1);
    d->gct = T_BYTES;
    d->root = 1;

    /* fasbol specific */

    /* Second descriptor is T_REFS, and root. This contains pre-
     * defined strings, symbol table, and other stuff needed to support
     * the compiled code. It will always be available at storage[1]
     * (storage[0] is the empty descriptor).
     *
     * 5 * 4 = 20 bytes used. 10 descriptors initially alloted.
     * This allows up to 39 common variables (0..38).
     */

    CMN = allocate(10);
    storage[CMN].gct = T_REFS;
    storage[CMN].root = 1;

    /* Add variables to storage, recording them in CMN */
    p = storage[CMN].data;

    /* "" - empty string */
    sp = (string *)s;
    sp->flags = S(0);
    sp->type = TYPE_STRING;
    sp->len = 0;
//  strcpy(sp->value, "");
    p[0] = v_to_store(s);

    /* &DIGITS */
//  sp = (string *)s;
    sp->flags = S(10);
//  sp->type = TYPE_STRING;
    sp->len = 10;
    memcpy(sp->value, "01234567890", 10);
    p[1] = v_to_store(s);

    /* &LCASE */
//  sp = (string *)s;
    sp->flags = S(26);
//  sp->type = TYPE_STRING;
    sp->len = 26;
    memcpy(sp->value, "abcdefghijklmnopqrstuvwxyz", 26);
    p[2] = v_to_store(s);

    /* &UCASE */
//  sp = (string *)s;
    sp->flags = S(26);
//  sp->type = TYPE_STRING;
    sp->len = 26;
    memcpy(sp->value, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26);
    p[3] = v_to_store(s);

    /* &ALPHABET */
//  sp = (string *)s;
    sp->flags = S(256);
//  sp->type = TYPE_STRING;
    sp->len = 256;
    memcpy(sp->value, ALPHABET, 256);
    p[4] = v_to_store(s);
}

#if TEST
int main(void)
{
    descriptor *d;

    /* should be 16 bytes per descriptor */
    fprintf(stderr, "%d\n", sizeof (descriptor));

    init_storage();

    prstring(&STRING);
    prstack(&SS);
    fillbreak(&BRK, &STRING);
    prbreak(&BRK);
    fillbreak(&BRK, &ALPHABET);
    prbreak(&BRK);

    fprintf(stderr, "allocating\n");
    /* Play with allocator */
    allocate(256);
    d = storage + allocate(256);
    d->gct = T_BYTES;
    d->root = 1;
    d = storage + allocate(256);
    d->gct = T_BYTES;
    d = storage + allocate(256);
    /* don't set root on this one. it should be reclaimed. */
    d = storage + allocate(256);
    d = storage + allocate(256);
    d->gct = T_BYTES;
    d->root = 1;
    prstorage();
    gc();
    prstorage();
    return 0;
}
#endif
