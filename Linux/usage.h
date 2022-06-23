#ifndef  _USAGE_H
#define  _USAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <errno.h>

#define	TIME_LEN				32

void gui();
void print_revise();
void print_usage();
void print_rank();
void print_inquire();
void time_get(char **times, char **date);
void cms();

#endif
