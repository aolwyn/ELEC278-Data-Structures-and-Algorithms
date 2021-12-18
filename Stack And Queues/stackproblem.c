

#include <iostream>
#define max 80
using namespace std;

struct stackNode //defining stacks
{
    char info;
    struct stackNode *next;
};

struct stackNode* top=NULL; //stack is initially empty

void push(char ch) //make a new node with ch as the input, move the top up to the node just made
{
    struct stackNode* newNode=(struct stackNode*)malloc(sizeof(struct stackNode));
    newNode->info=ch;
    newNode->next=top;
    top=newNode;
}

void printpop() //print the data at the top, then move down to the list
{
        cout<<top->info;
        top=top->next;
    if (top==NULL) //if the top is null, ie the list is empty, print a new line and exit function
    {
        printf("\n");
        exit(0);
    }
}

int main()
{
    printf("Enter string here:\n");
    char input[max]="";
    int count=0; //counter to ensure that max number of characters is not reached
    for (int i=0; i<max; i++)
    {
        scanf("%c", &input[i]); //character gets added to array with each iteration
        count++; //count increases with every added character
        if (input[i]=='\n') //if new line is typed, break code and continue to other portion
            break;
        else
            push(input[i]); //push all the characters added into the stack
        if (count==max) //if max. number of characters are reached, exit program
        {
            printf("ERROR: Too many characters\n");
            exit(0);
        }
    }
    printf("Reversed string is:\n");
    struct stackNode* created=top;
    while(created!=NULL) //while the created stack's top is not null, ie it is not empty, print and pop the data
    {
        printpop();
    }
}
