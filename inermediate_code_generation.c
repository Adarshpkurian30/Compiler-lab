#include<stdio.h>
#include<ctype.h>
#include<string.h>
char stack[50];
int top=-1;
//global temporary variable counter is not strictly need since generate TAC uses a local one.
//-----Stack Operations for Infix to Postfix---
//push characters onto the global stacl
void push(char c)
{
    stack[++top]=c;

}
//pop character from the global stack
char pop()
{
    if(top==-1)
        return -1;
    return stack[top--];
}
//defines precedence for operators
int precedence(char c)
{
    if((c=='+')||(c=='-')) return 1;
    if((c=='*')||(c=='/')) return 2;
    return 0;
}
//convert infix expression(RHS) to postfix expression
void infixToPostfix(char infix[], char postfix[])
{
    int i,j=0;
    char ch;
    top=-1; //reset stack for use
    for(i=0;infix[i]!='\0';i++)
    {
        ch=infix[i];
        if(isalnum(ch))
        {
            //operand
            postfix[j++]=ch;
        }
        else if(ch=='(')
        {
            push(ch);
        }
        else if(ch==')')
        {
            while((stack[top]!='(')&& (top!=-1))
            {
                postfix[j++]=pop();
            }
            pop(); //remove '('
        }
        else if(ch=='+' || ch=='-' || ch=='*'|| ch=='/')
        {
            //operator
            while(precedence(stack[top])>= precedence(ch))
            {
                postfix[j++]=pop();
            }
            push(ch);
        }
    }
    while(top!=-1)
    {
        postfix[j++]=pop();
    }
    postfix[j]='\0';
}
//Generate TAC code generation ---
//Generate TAC from the postfix expression
void generateTAC(char postfix[],char lhs)
{
    //temporary stack to hold operands (variables or temporary results like "t1")
    char tempStack[50][10];
    int tTop=-1;
    int tCount=1;
    char result[10];
    for(int i=0;i<strlen(postfix);i++)
    {
        char symbol=postfix[i];
        if(isalnum(symbol))
        {
            //if operand, push it onto the temporary stack
            char op[2]={symbol,'\0'};
            strcpy(tempStack[++tTop],op);
        }
        else if (symbol=='+'||symbol=='-' || symbol=='*' || symbol=='/')
        {
            //if operator,pop two operands,generate TAC, and push temporary result
            char operand2[10],operand1[10];
            //pop operand 2
            strcpy(operand2,tempStack[tTop--]);
            //pop operand 1
            strcpy(operand1,tempStack[tTop--]);
            //generate new temporary variable
            sprintf(result,"t%d",tCount++);
            //print the 3 Address instruction
            printf("%s=%s %c %s\n",result,operand1,symbol,operand2);
            //Push the temporary result back to the stack
            strcpy(tempStack[++tTop],result);

        }
    }
    //final assignment to the orginal LHS
    printf("%c=%s\n",lhs,tempStack[tTop]);
}
int main()
{
    char expr[50], lhs,rhs[50],postfix[50];
    printf("Enter expression (e.g a=b+c*d): ");
    //using scanf for a single word/expression without spaces
    if(scanf("%s",expr)!=1)
    {
        return 1;
    }
    //Ensure the input has an assignment operator
    if(expr[1]!='=')
    {
        printf("Error:Input must be in the format variable=expession\n");
        return 1;
    }
    //split into LHS and RHS
    lhs=expr[0];
    strcpy(rhs,expr+2); //skip "a="
    //convert(rhs,expr+2)
    infixToPostfix(rhs,postfix);
    printf("\n----Intermediate code(3 address code)---\n");
    generateTAC(postfix,lhs);
    return 0;

}
