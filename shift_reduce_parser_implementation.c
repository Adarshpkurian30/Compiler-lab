#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char ip_sym[15],stack[15];
int ip_ptr=0, str_ptr=0,len,i;
char temp[2],temp2[2];
char act[15];

int check();
int main()
{
printf("\n \t \t SHIFT REDUCE PARSER \n");
printf("\n GRAMMAR\n");
printf("\n E->E+E\n E->E/E");
printf("\n E->E*E \n E->a/b");
printf("\n enter the input symbol:(eg a+b/b+a)\t");
scanf("%s",ip_sym);
printf("\n\t stack implementation table");
printf("\n stack\t\t input symbol \t\t action");
printf("\n----\t\t--------------\t\t \n");
printf("\n$\t\t %s$\t\t\t--",ip_sym);
// prepare the action string for the first shift;
strcpy(act,"shift");
temp[0]=ip_sym[ip_ptr];
temp[1]='\0';
strcat(act,temp);


len=strlen(ip_sym);
for(i=0;i<=len-1;i++)
{
stack[str_ptr]=ip_sym[ip_ptr];//shift the symbol
stack[str_ptr+1]='\0';
ip_sym[ip_ptr]= ' '; //consume input symbol visually
ip_ptr++;
printf("\n $%s\t\t%s$\t\t%s",stack,ip_sym,act);
strcpy(act,"shift");
temp[0]=ip_sym[ip_ptr];
temp[1]='\0';
strcat(act,temp);
check(); //check for reductions after shift
str_ptr++;
}
check(); //Final check after all input is consumed
return 0;
}

int check()
{

    int flag=0;
    temp2[0]=stack[str_ptr];
    temp2[1]='\0';
    if(temp2[0]=='a' || temp2[0]=='b')
    {
        stack[str_ptr]='E';
        printf("\n$%s\t\t%s$\t\tE->%s",stack,ip_sym,temp2);
        flag=0;

    }
    if((!strcmp(temp2,"a"))||(!strcmp(temp2,"b"))||(!strcmp(temp2,"+"))||(!strcmp(temp2,"*"))||(!strcmp(temp2,"/")))
    {
        flag=1;
    }
    if((!strcmp(stack,"E+E"))|| (!strcmp(stack,"E/E"))||(!strcmp(stack,"E*E")))
    {
        char reduced_rule[10];
        if(!strcmp(stack,"E+E"))
        {
            strcpy(reduced_rule,"E->E+E");
        }
        else if(!strcmp(stack,"E*E"))
        {
            strcpy(reduced_rule,"E->E*E");
        }
        else
        {
            strcpy(reduced_rule,"E->E+E");
        }
        strcpy(stack,"E");
        printf("\n$%s \t\t %s$\t\t%s",stack,ip_sym,reduced_rule);
        flag=1;
        str_ptr=0;
    }
    // check for final acceptance
    if((!strcmp(stack,"E"))&& ip_ptr==len)
    {
        printf("\n$%s\t\t%s$\t\t ACCEPT\n",stack,ip_sym);
        exit(0);
    }
    if(flag==0)
    {
        printf("\n%s\t\t%s\t\tREJECT",stack,ip_sym);
        exit(0);
    }
    return 0;
}
