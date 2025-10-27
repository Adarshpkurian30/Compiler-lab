#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SUCCESS 1
#define FAILED 0

char *cursor;
char string[100];

// function for non-terminals
int E();
int Edash();
int T();
int F();
int Tdash();
int N(); //added N() for 'id' production
int main()
{
printf("Enter the string to be parsed (eg. a+b*c):");
scanf("%s",string);
cursor =string;
puts("");
puts("INPUT\t \t ACTION");
puts("--------------------------------------");
//start parsing with the start symbol
// E and check if the entire string is consumed
if(E() && *cursor=='\0')
{
printf("string is succesfully parsed\n");
return 0;
}
else
{
 printf("string is not parsed successfully parsed\n");
 return 1;
}
}
//E->TE'
int E()
{
printf("%-16s E->TE'\n",cursor);
if(T())
{
 if(Edash()) return SUCCESS;
}
return FAILED;
}
//E'->+TE'|e
int Edash()
{
 if(*cursor=='+')
 {
  printf("%-16s E'->+TE'\n",cursor);
  cursor++;// consume '+'
  if(T())
  {
  if(Edash()) return SUCCESS;
  }
  return FAILED;
 }
 //This is the epsilon production(E'->e)
 printf("%-16s E'->e\n",cursor);
 return SUCCESS;
}
//T->FT'
int T()
{
printf("%-16s T->FT'\n",cursor);
if(F())
{
if(Tdash()) return SUCCESS;
}
return FAILED;
}

//T'->*FT'|e
int Tdash()
{
if(*cursor=='*')
{
 printf("%-16s T'->*FT'\n",cursor);
 cursor++;
 if(F())
 {
  if(Tdash()) return SUCCESS;
 }
 return FAILED;
}
// this is the epsilon production(T'->e)
printf("%-16s T'->e\n",cursor);
return SUCCESS;
}

//F->(E)|N
int F()
{
if(*cursor=='(')
{
 printf("%-16s F->(E)\n",cursor);
 cursor++;//consume '('
 if(E())
 {
 if(*cursor==')')
 {
  printf("%-16s Matched ')'\n",cursor+1);
  cursor++;
  return SUCCESS;
 }
 }
 return FAILED;
}
else
{
  printf("%-16s F->N\n",cursor);
  if(N()) return SUCCESS;
  //return N();

}
}
//N->id
int N()
{
 if(*cursor>='a' && *cursor<='z')
 {
  printf("%-16s N-> c\n",cursor);
  cursor++;
  return SUCCESS;
 }
 return FAILED;

}










