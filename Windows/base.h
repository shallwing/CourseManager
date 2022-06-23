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




void regist_message()
{
	course					add, get;
	FILE					*file = NULL;
	int						fs = -1;
	char					temp; 
	char 					buf[BUF_SIZE];
	
	memset(&add, 0, sizeof(course));
	
	file = fopen(PATH, "ab+");
	if(!file)
	{
		printf("Fail to open the file to regist the course message :%s\n", strerror(errno));
		goto abort;
	}
	
//Input the course's ID, the ID is the only 12bits identification for one course. Can't be same.
	while(1){
again1:		printf("Please input the course's ID:\n");
		scanf("%s", add.id);
		fseek(file, 0, SEEK_SET);
		while( fgets(buf, BUF_SIZE, file) ){	
			_get_message(&get, buf);
			if( strstr(get.id, add.id) ){
				printf("Invalid course ID: the course of ID[%s] already exists!\n", add.id);
				printf("Please input again\n");
				goto again1;
			}
			memset(&get, 0, sizeof(course));
			memset(buf, 0, BUF_SIZE);
		}

		if( strlen(add.id) != 12 ){
			printf("Invalid course ID: the course of ID must be a 12 bits number sequence.\n");
			printf("Please input again\n");
			goto again1;
		}
		else
			break;
	}

//Input course's name.Can't be same.
again2:	printf("Please input the course's name:\n");
	scanf("%s", add.name);
	fseek(file, 0, SEEK_SET);
	while( fgets(buf, BUF_SIZE, file) ){
		_get_message(&get, buf);
		if( strstr(get.name, add.name) ){
			printf("Invalid course name: the same name '%s' already exist.\n", add.name);
			printf("Please input again\n");
			goto again2;
		}
	}

//Input course's attribute
	while(1){
		printf("Please input the course's attribute:\n");
		printf("g: Public courses\n");
		printf("b: Required courses\n");
		printf("x: Optional courses\n");
		scanf("%c", &temp); 
		scanf("%c", &add.attribute);
		if(add.attribute!='g' && add.attribute!='b' && add.attribute!='x')
			printf("Invalid choice: '%c'\nPlease try again\n", add.attribute);
		else
			break;
	}

//Input course's tree time
	while(1){
		printf("Please input the course's three teaching time gradually:\n");
		printf("[totalTime]\n[teachingTime]\n[labTime]\n");
		scanf("%d", &add.total);
		scanf("%d", &add.theory);
		scanf("%d", &add.lab);
		if(add.total<0 || add.theory<0 || add.lab<0){
			printf("Invalid argument: the tree arguments must be tree non-negative integers!\n");
			printf("Please try again\n");
		}
		else
			break;
	}

//Input the score of the course
	while(1){
		printf("Please input the score of the course:\n");
		scanf("%lf", &add.score);
		if(add.score <= 0){
			printf("Invalid score: the score must be a positive integer!\n");
			printf("Please try again!\n");
		}
		else
			break;
	}

//Input the semester of the course
	while(1){
		printf("Please input the semester of the course:\n");
		printf("shang: Last semester\n");
		printf("xia: Next semester\n");
		scanf("%s", add.semester);
		if( !strcmp("shang", add.semester) || !strcmp("xia", add.semester) )
			break;
		else{
			printf("Invalid semester: the semester must be 'shang' or 'xia'!\n");
			printf("Please input again:\n");
		}
	}


//Information record
	fseek(file, 0, SEEK_END);
	
	fs = fprintf(file, FORMATE, add.id, add.name, add.attribute, add.total, 
						   		add.theory, add.lab, add.score, add.semester);
	if(fs < 0){
		printf("Fail to write the message into %s :%s\n", PATH, strerror(errno));
		goto abort;
	}
	else
		printf("Operation successful!\n");
	fclose(file); 
abort:				;
}
 


void inquire(char flag)
{
	course					get;
	FILE					*file = NULL;
	int						fs = -1;
	char					buf[BUF_SIZE];
	char					*id = (char *)malloc(sizeof(char)*NAME_LEN);
	char					*record = NULL;
	char					attribute;
	char					temp;
	double						score;
	int						count = 0;
	
	memset(&get, 0, sizeof(course));
	memset(buf, 0, sizeof(buf));
	
	file = fopen(PATH, "r");
	if(!file)
	{
		printf("Fail to open the file to inquire the course message :%s\n", strerror(errno));
		goto abort;
	}
	fseek(file, 0, SEEK_SET);
	
	if(flag == 'a')
	{
		printf("Please input the attribute of the course:\n");
		printf("$'g':Public Course		$'b':Required Course		$'x':Optional Course\n");
		scanf("%c", &temp);
		scanf("%c", &attribute);
		
		if(attribute!='g' && attribute!='b' && attribute!='x')
		{
			printf("Invalid attribute, operation abort!\n");
			goto abort;	
		} 
		
		printf("The result of the browse is:\n\n");
		printf(" ID | Name | Attribute | TotalClassTime | TeachingClassTime | LabClassTime | Score | Semester |\n");

		while( record = fgets(buf, BUF_SIZE, file) )
		{	
			_get_message(&get, record);
			if(attribute == get.attribute){
				printf(FORMATE, get.id, get.name, get.attribute, get.total, get.theory, get.lab,
								get.score, get.semester);
				count++;
			}
		}
	}
	if(flag == 's')
	{
		printf("Please input the score of the course:\n");
		scanf("%lf", &score);
			
		if(score <= 0)
		{
			printf("Invalid score, operation abort!\n");
			printf("The score must be a positive integer!\n");
			goto abort; 
		}
		
		printf("The result of the browse is:\n\n");
		printf(" ID | Name | Attribute | TotalClassTime | TeachingClassTime | LabClassTime | Score | Semester |\n");
		
		while( record = fgets(buf, BUF_SIZE, file) )
		{	
			_get_message(&get, record);
			if(score == get.score){
				printf("%s", buf);
				count++;
			}
			memset(&get, 0, sizeof(course));
		}
	}
	if(flag == 'i')
	{
		printf("Please input the id of the course:\n");
		scanf("%s", id);
		
		if(!strlen(id))
		{
			printf("Invalid id: --'empty'\n");
			printf("The id can not be null!\n");
			goto abort;
		}
		
		printf("The result of the browse is:\n\n");
		printf(" ID | Name | Attribute | TotalClassTime | TeachingClassTime | LabClassTime | Score | Semester |\n");

		while( record = fgets(buf, BUF_SIZE, file) )
		{
			_get_message(&get, record);
			if(strstr(get.id, id)){
				printf("%s", buf);
				count++;
				break;
			}
		}
	}	
		
	printf("\nThere are %d records\n", count);
	fclose(file);
abort:				;
}


void clear()
{
	system("cls");
}

void del_record()
{
	FILE						*file;
	FILE						*temp;
	char						id[NAME_LEN];
	char						name[NAME_LEN];
	char						buf[BUF_SIZE];
	char						*record = NULL;
	course						get;
	int 						count = 0;
	
	memset(id, 0, NAME_LEN);
	memset(name, 0, NAME_LEN);
	
	file = fopen(PATH, "r+");
	if(!file){
		printf("Fail to open the text to delete a record :%s\n", strerror(errno));
		goto abort;	
	}
	temp = fopen("./temp.log", "a+");
	if(!temp){
		printf("Fail to open a temporary file to log message :%s\n", strerror(errno));
		goto abort;
	}
	
	printf("Please input the id:\n");
	scanf("%s", id);
	printf("Please input the name of the course:\n");
	scanf("%s", name);
	
	while( record = fgets(buf, BUF_SIZE, file) ){	
		_get_message(&get, record);
		if(strcmp(id, get.id)!=0 && strcmp(name, get.name)!=0){
			fprintf(temp, "%s", buf);
		}
		else{
			printf("Operation successful!\n");
			count=1;
		}
		memset(&get, 0, sizeof(course));
		memset(buf, 0, BUF_SIZE);
	}
	if(!count)
		printf("id[%s]: No such course logs in! -- '%s'\n", id, name);
	fclose(file);
	fclose(temp);
	remove(PATH);
	rename("./temp.log", PATH);
	
abort:	; 
}




void rank(char flag)
{
	course						*get;
	char 						buf[BUF_SIZE];
	course						temp;
	int							i, j, count = 0;	
	FILE						*file = fopen(PATH, "r");

	if(!file){
		printf("Fail to open the text to rank: %s\n", strerror(errno));
		goto abort;
	}
	fseek(file, 0, SEEK_SET);
	
	while( fgets(buf, BUF_SIZE, file) )
		count++;
	fseek(file, 0, SEEK_SET);
	get = (course *)malloc(count*sizeof(course));
	
	for(i=0; i<count; i++){
		fgets(buf, BUF_SIZE, file);
		_get_message(&get[i], buf);
	}
	
	if(flag == 's'){
		for(i=0; i<count; i++){
			for(j=0; j<count-i-1; j++){
				if(get[j].score > get[j+1].score){
					_temp_course(&get[j], &get[j+1]);
				}
			}
		}
	}
	else{
		if(flag == 't'){
			for(i=0; i<count; i++){
				for(j=0; j<count-i-1; j++){
					if(get[j].total > get[j+1].total){
						_temp_course(&get[j], &get[j+1]);
					}
				}
			}
		}
		else{
			printf("Invalid argument: No such choice --'%c'\n", flag);
			printf("Abort");
			goto abort;
		}
	}
	
	printf("The result of the browse is:\n\n");
	printf(" ID | Name | Attribute | TotalClassTime | TeachingClassTime | LabClassTime | Score | Semester |\n");
	for(i=0; i<count; i++){
		printf(FORMATE, get[i].id, get[i].name, get[i].attribute, get[i].total, get[i].theory, get[i].lab, 
		get[i].score, get[i].semester);
	}
	
abort:	;
}




void browser()
{
	course					get;
	int						count = 0;
	FILE					*file = NULL;
	int						fs = -1;
	char					buf[BUF_SIZE];
	char					*record = NULL;
	
	memset(&get, 0, sizeof(course));
	memset(buf, 0, sizeof(buf));
	
	file = fopen(PATH, "r");
	if(!file)
	{
		printf("Fail to open the file to browse the course message :%s\n", strerror(errno));
		goto abort;
	}
	fseek(file, 0, SEEK_SET);
	
//Browse the information by file traverse.
	printf("The result of the browse is:\n\n");
	printf(" ID | Name | Attribute | TotalClassTime | TeachingClassTime | LabClassTime | Score | Semester |\n");
//fgets: read the message by line.
	while( fgets(buf, BUF_SIZE, file) ) 
	{
		printf("%s", buf);
		count++;
	}
	printf("\nThere are %d records\n", count);
	fclose(file);
abort:					;
}




void _temp_course(course *c1, course *c2){
	char					buf[NAME_LEN];
	int						itemp;
	double					dtemp;
	char					ctemp;
	
	strncpy(buf, c1->id, NAME_LEN);
	strncpy(c1->id, c2->id, NAME_LEN);
	strncpy(c2->id, buf, NAME_LEN);
	
	strncpy(buf, c1->name, NAME_LEN);
	strncpy(c1->name, c2->name, NAME_LEN);
	strncpy(c2->name, buf, NAME_LEN); 
	
	ctemp = c1->attribute;
	c1->attribute = c2->attribute;
	c2->attribute = ctemp;
	
	itemp = c1->total;
	c1->total = c2->total;
	c2->total = itemp;
	
	itemp = c1->theory;
	c1->theory = c2->theory;
	c2->theory = itemp;
	
	itemp = c1->lab;
	c1->lab = c2->lab;
	c2->lab = itemp;
	
	dtemp = c1->score;
	c1->score = c2->score;
	c2->score = dtemp;
	
	strncpy(buf, c1->semester, NAME_LEN);
	strncpy(c1->semester, c2->semester, NAME_LEN);
	strncpy(c2->semester, buf, NAME_LEN);
}

void _get_message(course *get, char *record)
{
	char						*pc_1 = record;
	char						*pc_2 = record;
	char						temp[NAME_LEN];
	
	memset(temp, 0, sizeof(temp));
	
	pc_2 = strstr(pc_2, "|");
	strncpy(get->id, pc_1, (pc_2-pc_1));
	pc_2++;
	pc_1 = pc_2;
	
	pc_2 = strstr(pc_2, "|");
	strncpy(get->name, pc_1, (pc_2-pc_1));
	pc_2++;
	pc_1 = pc_2;
	
	pc_2 = strstr(pc_2, "|");
	get->attribute = *pc_1;
	pc_2++;
	pc_1 = pc_2;
	
	pc_2 = strstr(pc_2, "|");
	strncpy(temp, pc_1, (pc_2-pc_1));
	get->total = atoi(temp);
	pc_2++;
	pc_1 = pc_2;
	memset(temp, 0, sizeof(temp));
	
	pc_2 = strstr(pc_2, "|");
	strncpy(temp, pc_1, (pc_2-pc_1));
	get->theory = atoi(temp);
	pc_2++;
	pc_1 = pc_2;
	memset(temp, 0, sizeof(temp));
	
	pc_2 = strstr(pc_2, "|");
	strncpy(temp, pc_1, (pc_2-pc_1));
	get->lab = atoi(temp);
	pc_2++;
	pc_1 = pc_2;
	memset(temp, 0, sizeof(temp));
	
	pc_2 = strstr(pc_2, "|");
	strncpy(temp, pc_1, (pc_2-pc_1));
	get->score = atof(temp);
	pc_2++;
	pc_1 = pc_2;
	memset(temp, 0, sizeof(temp));
	
	pc_2 = strstr(pc_2, "|");
	strncpy(get->semester, pc_1, (pc_2-pc_1));
	pc_2++;
	pc_1 = pc_2;
}

#endif
