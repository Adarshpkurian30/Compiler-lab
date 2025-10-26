#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int isKeyword(char *str)
{
  char *KW[] ={"int","#include<stdio.h>","char","break","continue","float","if","else","for","while","do","return","void","printf","scanf","main"};
  int keyword_count=16;
  for(int i=0;i<keyword_count;i++)
  {
   if(strcmp(str,KW[i])==0)
   return 1;
  }
  return 0;
}

void main()
{
  FILE *fp1=fopen("input.txt","r");
  char ch,input_str[100];
  int i=0;
  if(fp1==NULL)
  {
   printf("File not found\n");
   exit(0);
  }
/* e.g. of input.txt
#include<stdio.h>
void main()
{
 int a=20;
 int b=30;
int c =a+b;
printf("sum=%d",c);
}
*/

  //output format
  printf("\n----------------------------------------------\n");
  printf("| %-15s | %-20s |\n","Lexeme","Token Type");
  printf("------------------------------------------------\n");

  while((ch=fgetc(fp1))!= EOF)
  {
   //skip whitespace
   if (isspace(ch))
            continue;

   // handle identifiers & keywords
   if(isalpha(ch) || ch=='_')
   {
     i=0;
     input_str[i++]=ch;
     while((ch=fgetc(fp1))!= EOF && (isalnum(ch)|| ch=='_'))
     {
      input_str[i++]=ch;

     }
     input_str[i]='\0';
     if(isKeyword(input_str))
     {
      printf("| %-15s | 20-%s |\n",input_str,"Keyword");
      }
      else
      {
        printf("| %-15s | 20-%s |\n",input_str,"Identifier");

      }
      ungetc(ch,fp1); //push back last char
    }
    else if(isdigit(ch))
    {
    i=0;
    input_str[i++]=ch;
    int has_dot=0;
    while((ch=fgetc(fp1))!=EOF &&(isdigit(ch)||ch=='.'))
    {
       if(ch=='.')
       has_dot=1;
       input_str[i++]=ch;
    }
    input_str[i]='\0';
    if(has_dot){
    printf("| %-15s | %-20s |\n",input_str,"Float Literal");
    }
    else
    printf("| %-15s | %-20s |\n",input_str,"Integer Literal");
    ungetc(ch,fp1);

    }
    //Handle string Literals
    else if (ch == '"')
{
    i = 0;
    input_str[i++] = ch;
    while ((ch = fgetc(fp1)) != EOF && ch != '"')
        input_str[i++] = ch;
    input_str[i++] = '"';
    input_str[i] = '\0';
    printf("| %-15s | %-20s |\n", input_str, "String Literal");
}
   else if(ch=='/')
   {
   char next =fgetc(fp1);
   if(next=='/') {
   // single-line comment
   while((ch=fgetc(fp1))!=EOF &ch!='\n');
   }
   else if(next=='*')
   {
   char prev;
   while(ch=fgetc(fp1)!=EOF)
   {
    if(prev=='*' && ch=='/') break;
    prev=ch;
   }

  }
  else
  {//division operator

      printf("| %-15c | %-20s |\n",ch,next,"operator");
      ungetc(next,fp1);


   }



   }
   //Handle operators
   else if(ch=='+' || ch=='-' || ch=='=' || ch=='<' || ch=='>' || ch=='!')
   {
       char next=fgetc(fp1);
       if(next=='=' || (ch=='+' && next=='+')||(ch=='-' && next=='-'))
       {
           printf("| %c%c | %-20s |\n",ch,"operator");

       }
       else
       {
           printf(" | %-15c | %-20s |\n",ch,"operator");
           ungetc(next,fp1);

       }

   }
   //special symbols
   else if(ch==';'|| ch==','|| ch=='{'|| ch=='}'|| ch=='('|| ch==')')
    {
        printf("| %-15c | %-20s |\n",ch,"special symbol");

    }

  }
  printf("--------------------------------------------------------\n");
  fclose(fp1);
  return 0;



}
