#ifndef  _BASE_H
#define  _BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#define BUF_SIZE			256
#define NAME_LEN			128
#define TIME_LEN			32
#define PATH				"./course.log"
#define FORMATE				"%12s|%16s|%c|%2d|%2d|%2d|%lf|%8s|\n"

typedef struct _course{
	char					id[NAME_LEN];
	char					name[NAME_LEN];
	char					attribute;
	int						total; 
	int						theory;
	int						lab;
	double						score;
	char					semester[NAME_LEN]; 
}course;

void time_get(char **times, char **date);
void regist_message();
void browser();
void inquire(char flag);
void clear();
void del_record();
void rank(char flag);
void _temp_course(course *c1, course *c2);
void _get_message(course *get, char *record);
 

#endif
