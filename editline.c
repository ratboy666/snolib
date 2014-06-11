#line 26 "READLINE.lss"
/* Generated by WRAPPER on 06/10/2014 19:36:30 */

#include "config.h"
#include "h.h"
#include "snotypes.h"
#include "macros.h"
#include "load.h"
#include "equ.h"
#include <string.h>

#line 27 "READLINE.lss"

/* Adds some functions enhancing CSNOBOL4 READLINE().
 *
 * EDITLINE(PROMPT, LINE)STRING uses gnu readline to edit a line
 * RLAPPNAME(NAME) sets the appname for readline, allowing readline
 *     config to conditionally configure for application.
 * CLEAR_HISTORY() clears history
 * STIFLE_HISTORY(INTEGER) stifles history to (max) n items
 * READ_HISTORY(STRING)INTEGER reads history from fname
 * WRITE_HISTORY(STRING)INTEGER writes history to fname
 *
 * Base code generated by WRAPPER on 11/01/2013 15:30:10
 */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static char *editline_s = NULL;

static int prehook(void)
{
    rl_insert_text(editline_s);
    rl_beg_of_line(0, 0);
    rl_redisplay();
    return 1;
}

/* EDITLINE(STRING,STRING)STRING_FREE
 *
 * First STRING is the prompt, second string is the initial value
 */
EDITLINE( LA_ALIST ) LA_DCL
{
    void *old = rl_pre_input_hook;
    char *result;
    char prompt[1024];
    char initial_line[1024];
    getstring(LA_PTR(0), prompt, sizeof(prompt));
    getstring(LA_PTR(1), initial_line, sizeof(initial_line));
    editline_s = initial_line;
    rl_pre_input_hook = prehook;
    result = readline(prompt);
    rl_pre_input_hook = old;
    RETSTR_FREE(result);
}

RLAPPNAME( LA_ALIST) LA_DCL
{
    static char rlapp[1024];
    getstring(LA_PTR(0), rlapp, sizeof(rlapp));
    rl_readline_name = rlapp;
    RETNULL;
}

CLEAR_HISTORY( LA_ALIST ) LA_DCL
{
    clear_history();
    RETNULL;
}

STIFLE_HISTORY( LA_ALIST ) LA_DCL
{
    stifle_history(LA_INT(0));
    RETNULL;
}

READ_HISTORY( LA_ALIST ) LA_DCL
{
    char *s;
    char fname[1024];
    getstring(LA_PTR(0), fname, sizeof(fname));
    if (strlen(fname) == 0)
	s = NULL;
    else
	s = fname;
    RETINT(read_history(s));
}

WRITE_HISTORY( LA_ALIST ) LA_DCL
{
    char *s;
    static char fname[1024];
    getstring(LA_PTR(0), fname, sizeof(fname));
    if (strlen(fname) == 0)
	s = NULL;
    else
	s = fname;
    RETINT(write_history(s));
}
