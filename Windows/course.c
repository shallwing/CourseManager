#include "usage.h"
#include "base.h"

int main(void)
{
	char				cmd[NAME_LEN];
	char				flag;
	char				temp;
	char				*times = (char *)malloc(TIME_LEN);
	char				*date = (char *)malloc(TIME_LEN);
	gui();
	
	while(1)
	{
		cms();
		
		scanf("%s", cmd);
		
		if(!strncmp("when", cmd, NAME_LEN))
		{
			time_get(&date, &times);
			printf("%s   %s\n\n", times, date);
			continue;
		} 
		if(!strncmp("add", cmd, NAME_LEN))
		{
			regist_message();
			continue;
		}
		if(!strncmp("search", cmd, NAME_LEN))
		{
			print_inquire();
			scanf("%c", &temp);
			scanf("%c", &flag);
			if(flag!='a' && flag!='s' && flag!='i'){
				printf("Invalid choice --'%c', operation abort\n", flag);
				continue;
			}
			inquire(flag);
			continue;
		}
		if(!strncmp("browse", cmd, NAME_LEN))
		{
			browser();
			continue;
		}
		if(!strncmp("delete", cmd, NAME_LEN))
		{
			del_record();
			continue;	
		}
		if(!strncmp("rank", cmd, NAME_LEN))
		{
			print_rank();
			scanf("%c", &temp);
			scanf("%c", &flag);
			if(flag!='s' && flag!='t'){
				printf("Invalid choice --'%c', operation abort\n", flag);
				continue;
			}
			rank(flag);
			continue;
		}
		if(!strncmp("revise", cmd, NAME_LEN))
		{
			print_revise();
			continue;		
		} 
		if(!strncmp("clear", cmd, NAME_LEN))
		{
			clear();
			continue;
		}
		if(!strncmp("exit", cmd, NAME_LEN))
		{
			break;
		}
		if(!strncmp("help", cmd, NAME_LEN))
		{
			print_usage();
			continue;
		}
		printf("Invalid cmd -- '%s' \n", cmd);
	}	
	return 0;
}
