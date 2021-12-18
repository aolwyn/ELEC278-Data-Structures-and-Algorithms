
#include <stdio.h>
#include <iostream>

#define bool    unsigned char
#define    false    (unsigned char) 0
#define true    (unsigned char) 1


// Queue is linked list of items.
class item
{
public:
    
    struct item        *next;
    int                value;

typedef struct item        Item, *pItem;

// Queue implementation
Item    *front = NULL;
Item    *end = NULL;        // Pointers to front and end queue elements
int        count = 0;            // Number of items in queue


bool qempty (void)
// Returns true if queue is empty
{
    return count==0;
}//qempty()


bool qinsert (int n)
// Add value n to queue end of queue
{
    // Create node to hold value being added to queue
    Item    *pnew = (Item *)malloc(sizeof (struct item));
    bool    result = false;
    if (pnew != NULL)    {
        pnew->value = n;
        pnew->next = NULL;
        // Make current last node point to new node
        if (end != NULL)    {
            end->next = pnew;
            }
        // and update queue's end pointer
        end = pnew;
        // If queue was empty, new node is also new front node
        if (front == NULL)    front = pnew;
        count++;
        result = true;
        }
    return result;
}//qinsert()


bool qremove (int *n)
// Remove first value from front of queue
{
    bool    result = false;
    // Check if there is anything to remove
    if (count > 0)    {
        // There is data to remove
        Item    *ptmp = front;        // pointer to first element
        *n = front->value;            // give value to caller
        front = front->next;        // move front pointer to next item
        count--;                    // reduce queue count
        free (ptmp);                // give back memory
        // Did we just remove last item from queue?  If so, must adjust
        // end pointer
        if (front == NULL)    end = NULL;
        result = true;
        }
    return result;
}//qremove()


void qprint (void)
// Print all contents of array - primarily used for debugging purposes
{
    Item    *pv;
    int        k = 0;        // "Index" in queue - makes output match array
                        // implementation
    pv = front;
    while (pv != NULL)    {
        printf ("%5d ", pv->value);
        pv = pv->next;
        k++;
        }
    putchar('\n');
}//qprint()
};

int main()
{
    printf("Enter a max of 400 values:\n");
    item queue1; //instance in class for different queues
    item queue2;
    item queue3;
    item queue4;
    
    int going = 1; //while loop
    int data; //input data
    int count=0; //counter to ensure input doesnt exceed 400 data inputs
    while (going)
    {
        scanf("%d", &data);
        count++;
        if (data%4==0) //if modulo 4 is 0, goes into first queue
            queue1.qinsert(data);
        else if (data%4==1) //if modulo 4 is 1, goes into second queue
            queue2.qinsert(data);
        else if (data%4==2) //if modulo 4 is 2, goes into third queue
            queue3.qinsert(data);
        else if (data%4==3) //if modulo 4 is 3, goes into four queue
            queue4.qinsert(data);
        else if (data<0||count==400)
                going=0;
    }
    printf("Queue 1: (Data %% 4=0)\n");
    queue1.qprint();
    printf("Queue 2: (Data %% 4=1)\n");
    queue2.qprint();
    printf("Queue 3: (Data %% 4=2)\n");
    queue3.qprint();
    printf("Queue 4: (Data %% 4=3)\n");
    queue4.qprint();
    return 0;
}
