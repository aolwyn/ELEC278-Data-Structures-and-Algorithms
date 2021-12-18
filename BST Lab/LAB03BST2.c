//
// Code for ELEC278 Lab 3.  Some code has already been implemented.
// You will develop your own code - look for the comments.


/* --README--------------------------------------------------------------------
Source code used for teaching purposes in course:
ELEC278, Queen's University, Kingston, Fall semester 2020.
This code is provided without warranty of any kind. It is the responsibility
of the user to determine the correctness and the usefulness of this code for
any purpose.

Author:  David F. Athersych, P.Eng.
All rights reserved. This code is intended for students registered in the
course and the semester listed above.

See LICENCE.MD for restrictions on the use of this code.
---------------------------------------------------------------------------- */




#include <stdlib.h>
#include <stdio.h>
#include "LAB03BST2.h"
#include <string.h>

#define    HEIGHT_WRITTEN    1
#define    FINDPARENTHELPER_WRITTEN    1
#define    DELETE_WRITTEN    1
#define MAX 2147483647 //used to check to see if BST is a BST or not
#define MIN -2147483647

Node *initNode (Key id, char *pw)
// Allocate memory for new node and initialize fields.
// Returns pointer to node created.
{
    Node *n = malloc(sizeof(Node));
    // initialize node if memory obtained
    if (n != NULL)    {
        n->identification = id; //name if the node
        strcpy(n->password,pw); //password is a string, need strcpy
        n->leftChild = NULL;
        n->rightChild = NULL;
        }
    return n;
}//initNode()

Tree *initTree(Key id, char *pw)
// Set up new tree. Allocates memory for Tree structure, then
// calls initNode() to allocate first node.
{
    Tree* t = malloc(sizeof(Tree));
    if (t != NULL)
        t->root = initNode(id,pw);
    return t;
}//initTree()


void printTreeExplanation (void)
// Prints hint to reader what to expect on screen
{
    static int done = 0;
    if (!done)    {
        printf ("First time explanation of tree display:\n");
        printf ("Every node is displayed as a comma-separated pair within brackets:");
        printf (" (kk,vv)\n");
        printf ("where kk is the key and vv is the value\n");
        printf ("A tree starts with a curly bracket { and ends with a curly bracket }.\n");
        printf ("An empty tree will be {}\n");
        printf ("A tree with no children will be { (kk,vv),{},{} }\n");
        printf ("If either subtree is populated, it will be shown using the same ");
        printf ("technique as described above\n");
        printf ("(Hint: Start at root - and then match up all the remaining\n");
        printf ("brackets, then interpret what those bracket pairs are telling\n");
        printf ("you.)\n============\n\n");
        done = 1;
        }
}//printTreeExplanation()


void printTree (Node* root)
// Print whole tree. We cannot make it look pretty graphically, so we add some
// characters to make it a little easier to understand.  We also don't really
// know what the value field is - it is declared to be a void pointer - so we
// treat it as though it points to an integer.
{
    // assume printTree magically knows the types in the tree node
    printTreeExplanation();
    // start of this tree
    printf("{");
    // values in the root node (assuming value is pointing to an integer)
    printf("(%ld,%c),", root->identification, *(int*)root->password);
    
    // Now show left subtree or {} if there is no left subtree
    if (root->leftChild != NULL)    printTree(root->leftChild);
    else                            printf("{}");
    // Marker between left and right subtrees
    printf(",");
    // Now show right subtree or {} if there is no right subtree
    if (root->rightChild != NULL)    printTree(root->rightChild);
    else                            printf("{}");
    // Close display of this tree with closing curly bracket
    printf("}");
}//printTree()


Node *find (Key id, Node *root)
// Function locates node with key value equal to parameter k. Parameter
// root holds pointer to root node of tree. Function returns immediately
// if either root pointer is null, or the node that root points to has
// key value sought.  If neither of those conditions is true, then the
// function calls itself with a pointer to either the left or right
// subtree.
{
    // termination conditions - either true, search is ended
    if ((root == NULL) || (root->identification == id))    return root;
    // search continues.  Since this is a search tree, we know that
    // every key in the right subtree is bigger than the key in the tree's
    // root, and every key in the left subtree is smaller than the key in
    // the tree's root.  That allows us to choose the appropriate subtree
    // to search.
    if (id>root->identification)
        // Key value sought is larger than current node key, so search right
        // subtree
        return find(id,root->rightChild);
    else
        // Key value sought is smaller than current node key (the equal case
        // was handled as a termination condition in the first line), so
        // search left subtree
        return find(id,root->leftChild);
}//find()



int insert(long id, char pw[12], Node *root)
// Function inserts a new node into the tree, with key k and value pointed to
// by v. Parameter root points to root node of tree.  Note that this code
// rejects an attempt to insert a duplicate key.
{
    int result = BST_FAIL;
    // this if statement can only be true with first root (root of whole tree)
    if (root == NULL)    {
        Node *n = initNode(id,pw);
        root = n;
        return BST_SUCCESS;
        }
    
    // already exists in tree ==> can't insert
    if (root->identification == id)
        strcpy(root->password, pw);
    else if (id < root->identification) {
        // key value less than key value in root node - try to insert into left
        // subtree, if it exists.
        if (root->leftChild != NULL)
            // there is a left subtree - insert it
            result = insert(id, pw, root->leftChild);
        else {
            // new Node becomes the left subtree
            Node *n = initNode(id,pw);
            root->leftChild = n;
            result = BST_SUCCESS;
            }
    } else if (id > root->identification) {            // test actually redundant
        // key is greater than this nodes key value, so value goes into right
        // subtree, if it exists
        if (root->rightChild != NULL)
            // there is a right subtree - insert new node
            result = insert(id,pw,root->rightChild);
        else {
            // no right subtree - new node becomes right subtree
            Node*n = initNode(id,pw);
            root->rightChild = n;
            result = BST_SUCCESS;
            }
        }
    return result;
}//insert()


int intmax(int a, int b)
// YOU WILL USE THIS FUNCTION WHEN YOU IMPLEMENT HEIGHT() !!
// Useful function - returns the greater value of two integers.
// Called intmax, not max, because max already exists.
// It is a chance to see a conditional expression in C - a value that is the
// first one (after the ?) if the condition is true, or the second one (after
// the :) if the condition is false.
{
    return (a>=b) ? a : b;
}//intmax()


int height(Node *root)
// Height definition:
// Height of an empty tree is -1.  Height of a leaf node is 0. Height of other
// nodes is 1 more than larger height of node's two subtrees.
{
    int        nodeheight = -1;    // default returned for empty tree
    if (root != NULL)    {
        int leftheight, rightheight;
        leftheight=height(root->leftChild);
        rightheight=height(root->rightChild);
        nodeheight = 1+intmax(leftheight, rightheight);
        // ---<SNIP>----
        // your code goes here  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        // ---<SNIP>----
        }
    return nodeheight;

}//height()


Node* findParentHelper (Key id, Node* root)
// Help find parent of node with key == k. Parameter root is node with
// at least one child (see findParent()).
{
    // your code goes here  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    // ---<SNIP>----
    if (root->identification==id)
    {
        return root;
    }
    
    else if ((root->leftChild!=NULL && root->leftChild->identification==id)|| (root->rightChild!=NULL && root->rightChild->identification==id))
    {
        return root;
    }
    
    else if (root->identification>id)
    {
        return findParentHelper(id, root->leftChild);
    }
    else if (root->identification<id)
    {
        return findParentHelper(id, root->rightChild);
    }
    else
    {
        return NULL;
    }
    // ---<SNIP>----
}//findparenthelper()


Node *findParent(Key id, Node *root)
//
{
    // Deal with special special cases which could only happen for root
    // of whole tree
    if (root == NULL)    return root;
    // real root doesn't have parent so we make it parent of itself
    if (root->identification == id)    return root;
    // root has no children
    if ((root->leftChild == NULL) && (root->rightChild == NULL))
            return NULL;

    // Deal with cases where root has at least one child
    return findParentHelper(id, root);
}//findParent()


void delete (Node *p, Node *n)
// Delete node pointed to by n.
// Parameters:
//    n    - points to node to be deleted
//    p    - points to parent of node to be deleted.
{
    // Deletion has 3 cases - no subtrees, only left or right subtree, or both
    // left and right subtrees.
    Node *deleteNode = n;        // Save copy of pointer to node to delete.

    if (n->leftChild!=NULL && n->rightChild!=NULL) //node has two children
    {
        Node *largest = (n->leftChild); //create a new pointer that points to the largest value in the left child of the node that is to be deleted
        
        while (largest->rightChild!=NULL)
            largest=largest->rightChild;
        
        deleteNode->identification=largest->identification;
        if (findParent(largest->identification, p)->leftChild==n)
            findParent(largest->identification, p)->leftChild=NULL;
        else if (findParent(largest->identification, p)->rightChild==n)
            findParent(largest->identification, p)->rightChild=NULL;
        
    }
    if (n->leftChild != NULL && n->rightChild==NULL)
    {            // there is left child
        if (p->rightChild==n)
        {
            p->rightChild=n->leftChild;
        }
        else if (p->leftChild==n)
        {
            p->leftChild=n->leftChild;
        }
    // your code goes here  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    }
    else if (n->rightChild!=NULL && n->leftChild==NULL)
    {// there is a right child
        if (p->rightChild==n)
        {
            p->rightChild=n->rightChild;
        }
        else if (p->leftChild==n)
        {
            p->leftChild=n->rightChild;
        }
    // your code goes here  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    }
    else
    {// no children
        if (p->leftChild==n)
            p->leftChild=NULL;
        else if (p->rightChild==n)
            p->rightChild=NULL;
    // your code goes here  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    }

}//delete()


int withdraw(Key id, Node* root, Node* n)
// Withdraw does two things:
//    return a copy of the node with key k (and value v)
//    Delete the node with key k from the tree while ensuring the tree remains valid
{
    Node *p, *m;
    m = find(id, root);

    if (m != NULL)    {
        // create a copy of the node with the same key and value
        n = initNode(m->identification,m->password);
        p = findParent(id,root);
        // can delete the node
        delete(p,m);
        return 1;
    }

    return 0;
}//withdraw()

void print_preorder (Node *pn)
// Print tree values based on preorder traversal. Function gets pointer to
// node, then prints node value, left subtree, right subtree.
{
    // If we were passed NULL, we have nothing to do
    if (pn == NULL)    return;
    printf (" %ld: %s\n ", pn->identification, pn->password);
    print_preorder (pn->leftChild);
    print_preorder (pn->rightChild);
}

int checkBSTHelper(Node*root, long min, long max){ //helper function checks to see if it is a BST or not, if there is no root, it cannot be checked. if it is not null, it checks to see that the id on the left side grows smaller, and the id on the right side grows bigger
    if (root==NULL){
        return 1;
    }
    if (root->identification<min || root->identification>max){
        return 0;
    }
    return checkBSTHelper (root->leftChild, min, root->identification-1) && checkBSTHelper(root->rightChild, root->identification+1, max);
}

int checkBST(Node* root){ //BST checker, initial values are the max and min integers compiler can hold
    return (checkBSTHelper(root, MIN, MAX));
}

int count(Node *root) //counter for the nodes, uses recursive function to traverse the right side and left side of each "root", which is the reference node, adding the number of nodes as it goes along
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return(count(root->leftChild)+count(root->rightChild)+1);
    }
}

int main()
{
        //int            i;
        Tree    *pnode = NULL;
        int            rslt=0;
        char        *p, *id, *pass;
        FILE        *fp;
        char        *pbuff;
    
        // Get buffer to read data file into.
        pbuff = (char *)malloc (256);
        if (pbuff == NULL)    {
            fprintf (stderr, "ERROR: Cannot get memory for buffer\n");
            return -1;
            }
        fp = fopen ("IDENTS.TXT", "r");
        if (fp == NULL)    {
            fprintf (stderr, "ERROR: Cannot open data file\n");
            return -1;
            }
        for (;;)    {
            p = fgets (pbuff, 256, fp);
            if (p == NULL)    break;
            while (*p == ' ')
                p++;
            id = p;
            p++;
            while (*p != ' ')
                p++;
            *p = '\0';
            p++;
            while (*p == ' ')
                p++;
            pass = p;
            p++;
            while (*p != '\n' && *p != '\r') p++;
            *p = '\0';
            if (rslt==0){
                pnode = initTree(atol(id),pass);
                rslt=1;
            }
            else{
            insert (atol(id),pass, pnode->root);
            }
        }
    fclose (fp);
    
    printf("BST NODES: %d\n", count(pnode->root)); //print the number of nodes
    
    if(checkBST(pnode->root)==0) //check to see if it is a BST or not
        return 1;
    
    if (pbuff == NULL)    { //this portion of code is to delete from the delete text file given
        fprintf (stderr, "ERROR: Cannot get memory for buffer\n");
        return -1;
        }
    fp = fopen ("DELETES.TXT", "r");
    if (fp == NULL)    {
        fprintf (stderr, "ERROR: Cannot open data file\n");
        return -1;
        }
    for (;;)    {
        p = fgets (pbuff, 256, fp);
        if (p == NULL)    break;
        while (*p == ' ')
            p++;
        id = p;
        p++;
        while (*p != ' ')
            p++;
        *p = '\0';
        p++;
        while (*p == ' ')
            p++;
        pass = p;
        p++;
        while (*p != '\n' && *p != '\r') p++;
        *p = '\0';
        if (find(atol(id), pnode->root)==NULL)
        {
            pnode = initTree(atol(id),pass);
            rslt=1;
        }
        else
        {
        withdraw(atol(id), pnode->root, pnode->root);
        }
    }
    fclose (fp);
    
    if(checkBST(pnode->root)==0)
        return 1;
    printf("NODES AFTER DELETES: %d\n", count(pnode->root)); //count the number of nodes after deletion
    
    fp = fopen ("LOOKUPS.TXT", "r");
    if (fp == NULL)    {
            fprintf (stderr, "ERROR: Cannot open data file\n");
            }
    for (;;)    {
        p = fgets (pbuff, 256, fp);
        if (p == NULL)    break;
        while (*p == ' ')
            p++;
        id = p;
        p++;
        while (*p != ' '&& *p != '\n'&&*p!= '\r')
            p++;
        *p = '\0';
        p++;
        if (find(atol(id), pnode->root)==NULL){
            printf("<NOT FOUND> \n");
        }
        else{
        Node* n = find(atol(id), pnode->root);
        printf("ID %010ld PASSWORD %s \n", n->identification , n->password);
        }
    }
    fclose (fp);
}
