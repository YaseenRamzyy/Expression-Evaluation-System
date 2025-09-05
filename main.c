#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// ANSI color codes
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"
#define RESET   "\033[0m"

//Implementing Stack using Linkedlist

typedef struct Node{
char data;
struct Node* next;
}Node;

typedef struct{
Node* top;
}Stack;

Stack* initialize(){
Stack* s=malloc(sizeof(Stack));
s->top=NULL;
return s;
}

void push(Stack* s,char x){
Node* n=malloc(sizeof(Node));
n->data=x;
n->next=s->top;
s->top=n;
}

char pop(Stack* s){
if(s->top == NULL) return '\0';
Node* temp=s->top;
char x=temp->data;
s->top=temp->next;
free(temp);
return x;
}

char peek(Stack* s){
if(s->top == NULL) return '\0';
char x=s->top->data;
return x;
}

int isEmpty(Stack* s){
return s->top == NULL;
}

//Function to check priority

int priority(char x){
    if(x=='+'||x=='-')
        return 1;
    else if(x=='*'||x=='/'||x=='%')
        return 2;
    else if(x=='^')
        return 3;
    else if(x=='(')
        return 0;
        else
            return -1;
}

//Function to check if the character is an operator
int isOperator(char c){
    return c=='+'||c=='-'||c=='*'||c=='/'||c=='%'||c=='^'||c=='('||c==')';
}

//function for math operations
float evaluate(float x1, float x2, char op){
    float result=0;
switch(op){
 case '+':
    result=x1+x2; break;
 case '-':
    result=x1-x2; break;
 case '*':
    result=x1*x2; break;
 case '/':
    result=x1/x2; break;
 case '^':
    result=pow(x1,x2); break;
 case '%':
    result= (int)x1 % (int)x2; break;
}
  return result;
}

// Function to convert infix to postfix

char* infixTopostfix(char *infix){
char* post=malloc(strlen(infix)*3);
Stack* s1=initialize();
int j=0;
int i=0;
int len=strlen(infix);

while(i<len){
    if(infix[i]==' '){i++; continue;}

    if(isdigit(infix[i]) || infix[i]=='.' || (infix[i]=='-' && i+1<len && (isdigit(infix[i+1]) || infix[i+1]=='.'))){
        int start = i;
        if(infix[i]=='-') i++;
        while(i<len && (isdigit(infix[i]) || infix[i]=='.')) i++;

        for(int k=start;k<i;k++){
            post[j++]=infix[k];
        }
        post[j++]=' ';
        continue;
    }

    if(isOperator(infix[i])){
        if(infix[i]=='('){
            push(s1,'(');
        }
        else if(infix[i]==')'){
            while(!isEmpty(s1) && peek(s1)!='('){
                post[j++]=pop(s1);
                post[j++]=' ';
            }
            if(!isEmpty(s1) && peek(s1)=='('){
                pop(s1);
            }
        }
        else if(isEmpty(s1)){
            push(s1,infix[i]);
        }
        else{
            while(!isEmpty(s1) && peek(s1)!='(' && priority(peek(s1))>=priority(infix[i])){
                post[j++]=pop(s1);
                post[j++]=' ';
            }
            push(s1,infix[i]);
        }
        i++;
    }
    else {
        printf(RED "Error: Invalid character '%c'\n" RESET, infix[i]);
        free(post);
        free(s1);
        return NULL;
    }
}

while(!isEmpty(s1)){
    post[j++]=pop(s1);
    post[j++]=' ';
}
post[j]='\0';
free(s1);
return post;
}


// function to evaluate postfix.
float evaluatepost(char *postfix){
typedef struct FloatNode{
float data;
struct FloatNode* next;
}FloatNode;

typedef struct{
FloatNode* top;
}FloatStack;

FloatStack* s=malloc(sizeof(FloatStack));
s->top=NULL;

int i=0;
int len=strlen(postfix);

while(i<len){
    if(postfix[i]==' '){i++; continue;}

    if(isdigit(postfix[i]) || postfix[i]=='.' || (postfix[i]=='-' && i+1<len && (isdigit(postfix[i+1]) || postfix[i+1]=='.'))){
        char num_str[20];
        int k=0;
        while(i<len && postfix[i]!=' '){
            num_str[k++]=postfix[i++];
        }
        num_str[k]='\0';
        float n=atof(num_str);

        FloatNode* new_node=malloc(sizeof(FloatNode));
        new_node->data=n;
        new_node->next=s->top;
        s->top=new_node;
        continue;
    }

    if(isOperator(postfix[i])){
        if(s->top == NULL || s->top->next == NULL) {
            printf(RED "Error: Invalid expression\n" RESET);
            return 0;
        }

        FloatNode* temp1=s->top;
        float n1=temp1->data;
        s->top=temp1->next;
        free(temp1);

        FloatNode* temp2=s->top;
        float n2=temp2->data;
        s->top=temp2->next;
        free(temp2);

        float result=evaluate(n2,n1,postfix[i]);
        FloatNode* new_node=malloc(sizeof(FloatNode));
        new_node->data=result;
        new_node->next=s->top;
        s->top=new_node;
        i++;
    }
}
if(s->top == NULL) {
    printf(RED "Error: Empty expression\n" RESET);
    return 0;
}
float E=s->top->data;

while(s->top != NULL) {
    FloatNode* temp = s->top;
    s->top = s->top->next;
    free(temp);
}
free(s);
return E;
}

void printHeader() {
    printf(CYAN "\n======================================================\n");
    printf("           EXPRESSION EVALUATION SYSTEM\n");
    printf("            INFIX TO POSTFIX CONVERTER\n");
    printf("======================================================\n" RESET);
}

void printMenu() {
    printf(YELLOW "\n======================================================\n");
    printf("                      MAIN MENU\n");
    printf("------------------------------------------------------\n");
    printf("   1. Evaluate an expression\n");
    printf("   2. Show examples\n");
    printf("   3. Exit\n");
    printf("======================================================\n" RESET);
    printf(GREEN "Enter your choice (1-3): " RESET);
}

void printExamples() {
    printf(MAGENTA "\n------------------------------------------------------\n");
    printf("                     EXAMPLE EXPRESSIONS\n");
    printf("------------------------------------------------------\n" RESET);
    printf(WHITE "Basic:       2+3*4\n");
    printf("With parens:  (5+3)*2\n");
    printf("Decimals:     10.5/2.0\n");
    printf("Negative:     -5+3\n");
    printf("Power:        2^3+1\n");
    printf("Complex:      (10+20)/(5-2)\n" RESET);
    printf(MAGENTA "------------------------------------------------------\n" RESET);
}

void printSeparator() {
    printf(BLUE "\n------------------------------------------------------\n" RESET);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    int choice;
    char str[100];

    printHeader();

    do {
        printMenu();
        if(scanf("%d", &choice) != 1) {
            printf(RED "Invalid input! Please enter 1, 2, or 3.\n" RESET);
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch(choice) {
            case 1:
                printSeparator();
                printf(GREEN "Enter an infix expression:\n" RESET);
                printf(YELLOW "> " RESET);
                fgets(str,sizeof(str),stdin);
                str[strcspn(str, "\n")] = '\0';

                if(strlen(str) == 0) {
                    printf(RED "Error: Empty input\n" RESET);
                    break;
                }

                printSeparator();
                printf(WHITE "Processing: %s\n" RESET, str);
                printSeparator();

                char* post=infixTopostfix(str);
                if(post == NULL) {
                    break;
                }
                printf(CYAN "Postfix expression: " YELLOW "%s\n" RESET, post);

                float result=evaluatepost(post);
                printf(GREEN "Result: " WHITE "%0.6f\n" RESET, result);
                printSeparator();

                free(post);
                break;

            case 2:
                printExamples();
                break;

            case 3:
                printf(GREEN "Thank you for using the Expression Evaluator!\n" RESET);
                break;

            default:
                printf(RED "Invalid choice! Please enter 1, 2, or 3.\n" RESET);
        }

    } while(choice != 3);

    return 0;
}
