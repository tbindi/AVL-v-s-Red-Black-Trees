// Comparision between AVL and RED-BLACK insertion.
// Concept behind AVL used is height based.
// Time taken for insertion of random elements is computed
// and it is transferred to a file.
// No. of rotations done in AVL and RED-BLACK is also calculated.
#include <stdio.h>
#include <stdlib.h>
#include "timer_nrp.h"



// USE OF ENUMERATED DATATYPES
enum cr {RED, BLACK};
// DEFINITION OF AVL and RED-BLACK
struct R
{
	long int info;
	struct R *parent;
	struct R *llink;
	struct R *rlink;
	enum cr color;
};
struct AVL
{
	long int info;
	struct AVL *parent;
	struct AVL *llink;
	struct AVL *rlink;
};

typedef struct R* NOD;
typedef struct AVL* NODE;



// ROOT nodes initialized to NULL.
NOD root_rb=NULL;
NODE root_avl = NULL;

// No. of rotations done in avl insertion.
int rb_count=0;

// No. of rotations done in red-black insertion.
int avl_count=0;


/**********************************************************************************************/
// Getnode function.

// RED-BLACK.
NOD getnode_rb()
{
	NOD x;

	x=(NOD)malloc(sizeof(struct R));
	if(x!=NULL)
	{
		x->rlink=NULL;
		x->parent=NULL;
		x->color=RED;
		x->llink=NULL;
	}	
	return x;
}

// AVL
NODE getnode_avl()
{
	NODE x;
	x=(NODE )malloc(sizeof(struct AVL));
	if(x!=NULL)
		x->llink=x->rlink=x->parent=NULL;
	return x;
}

// RED-BLACK UNCLE FUNCTION.
// This is used to get the 
// parents sibling.
NOD uncl(NOD child)
{
	if(child->parent==child->parent->parent->rlink)
		return child->parent->parent->llink;
	else
		return child->parent->parent->rlink;
}
// RED-BLACK GRANDPARENT FUNCTION.
// This is used to get the 
// grandparent of the child.
NOD grand(NOD child)
{
	return child->parent->parent;
}

//----------------------------------------------------------------------------//
void left_rotate_rb(NOD Y,NOD Z)
{
	Z->rlink=Y->llink;
	Y->parent=Z->parent;
        if(Y->llink!=NULL)
	   Y->llink->parent=Z;
	if(Y->parent == NULL)
		root_rb=Y;
	else if(Z == Z->parent->rlink)
		Z->parent->rlink=Y;
	     else 
		Z->parent->llink=Y;	
	Y->llink=Z;
	Z->parent=Y;		
}

//----------------------------------------------------------------------------//
void right_rotate_rb(NOD Y,NOD Z)
{
	Z->llink=Y->rlink;
	Y->parent=Z->parent;
	if(Y->rlink!=NULL)
	    Y->rlink->parent=Z;
	if(Y->parent == NULL)
		root_rb=Y;
	else if(Z == Z->parent->rlink)
		Z->parent->rlink=Y;
	     else 
		Z->parent->llink=Y;
	Y->rlink=Z;
	Z->parent=Y;
}
//----------------------------------------------------------------------------//
void rb_insert(int info)
{
	NOD temp,cur,prev;
	temp=getnode_rb();
	temp->info=info;

	//CASE 1:root is NULL
	if(root_rb==NULL)
	{
		root_rb=temp;
		root_rb->color=BLACK;
		return;
	}
	cur=root_rb;
	prev=NULL;
	// case 2: 
	// IF root is not NULL.
	// INSERTION is done by BST insertion.
	while(cur!=NULL)
	{
		prev=cur;
		if(cur->info==info)
			return;
		if(cur->info > info)
			cur=cur->llink;
		else
			cur=cur->rlink;
	}
	if(prev->info > info)
		prev->llink=temp;
	else
		prev->rlink=temp;
	temp->parent=prev;

//--------------------------------------------------------------------------------//
	NOD child=temp;
	NOD uncle,grandparent;
//--------------------------------------------------------------------------------//

	// BALANCING OF THE RED-BLACK TREE
	// USING UNCLE AS THE REFERENCE.
	while(child!=root_rb && (child->color==RED && child->parent->color==RED))
	{
		grandparent=grand(child);
		uncle=uncl(child);

		// case 3:UNCLE BEING NULL
		// There are 4 possibility when uncle is null,
		// those are dependant on the position of 
		// parent and child.
		if(uncle==NULL)
		{
			// 3.1 : LEFT-LEFT CASE
			if(child->parent==grandparent->llink && child==child->parent->llink)
			{
				child->parent->color =BLACK;
				grandparent->color=RED;
				child->color=RED;
				right_rotate_rb(child->parent,grandparent);
				rb_count++;
			}
			// 3.2 : RIGHT-RIGHT CASE
			else if(child->parent==grandparent->rlink && child==child->parent->rlink)
			{
				child->parent->color = BLACK;
				grandparent->color = RED;
				child->color=RED;
				left_rotate_rb(child->parent,grandparent);
				rb_count++;
			}
				// 3.3 : LEFT-RIGHT CASE
				else if(child->parent==grandparent->llink && child==child->parent->rlink)
				{
					child->parent->color = RED;
					child->color = BLACK;
					grandparent->color = RED;
					left_rotate_rb(child,child->parent);
					right_rotate_rb(child,grandparent);
					rb_count+=2;
				}
				else 
				// 3.4 : RIGHT-LEFT CASE
					{
						child->parent->color =RED;
						child->color = BLACK;
						grandparent->color = RED;
						right_rotate_rb(child,child->parent);
						left_rotate_rb(child,grandparent);
						rb_count+=2;
					}
		}
		//----------------------------------------------------------------------------------------------//
		// CASE 4 : UNCLE COLOR BEING RED
		else if(uncle->color==RED)
		{
			child->parent->color=BLACK;
			uncle->color=BLACK;
			grandparent->color=RED;
			child=grandparent;
		}
//-------------------------------------------------------------------------------------------------------------------------------------------------//
			else
			{
				// CASE 5 : UNCLE COLOR BEING BLACK
				// Same no of possibilities occur here.
				// CASE 5.1 : LEFT-LEFT CASE
				if(child==child->parent->llink && child->parent==grandparent->llink)
				{
					child->parent->color=BLACK;
					grandparent->color=RED;
					child->color=RED;
					right_rotate_rb(child->parent,grandparent);
					rb_count++;
				}
				// CASE 5.2 : LEFT-RIGHT CASE
				else if(child==child->parent->llink && child->parent==grandparent->rlink)
					{
						child->color=BLACK;
						grandparent->color=RED;
						child->parent->color=RED;
						right_rotate_rb(child,child->parent);
						left_rotate_rb(child,grandparent);
						rb_count+=2;
					}
					// CASE 5.3 : RIGHT-RIGHT CASE
					else if(child==child->parent->rlink && child->parent==grandparent->rlink)
						{
							child->parent->color=BLACK;
							grandparent->color=RED;
							child->color=RED;
							left_rotate_rb(child->parent,grandparent);
							rb_count++;
						}
						// CASE 5.1 : RIGHT-LEFT CASE
						else
						{
							child->color=BLACK;
							grandparent->color=RED;
							child->parent->color=RED;
							left_rotate_rb(child,child->parent);
							right_rotate_rb(child,grandparent);
							rb_count+=2;
						}
	
			}
	}
	root_rb->color=BLACK;
}

// AVL insertion and rotation functions.
//------------------------------------------------------------------------------//
void left_rotate_avl(NODE Y,NODE Z)
{
	Z->rlink=Y->llink;
	Y->parent=Z->parent;
	if(Z->parent == NULL)
		root_avl=Y;
	else if(Z == Z->parent->rlink)
		Z->parent->rlink=Y;
	     else 
		Z->parent->llink=Y;	
        if(Y->llink!=NULL)
	   Y->llink->parent=Z;
	Y->llink=Z;
	Z->parent=Y;		
}
//------------------------------------------------------------------------------//
void right_rotate_avl(NODE Y,NODE Z)
{
	Z->llink=Y->rlink;
	Y->parent=Z->parent;
	if(Z->parent == NULL)
		root_avl=Y;
	else if(Z == Z->parent->rlink)
		Z->parent->rlink=Y;
	     else 
		Z->parent->llink=Y;
	if(Y->rlink!=NULL)
	    Y->rlink->parent=Z;
	Y->rlink=Z;
	Z->parent=Y;
}

//---------------------------------------------------------------------------------//

// This is a recursive function which 
// returns the maximum height of the 
// node.

int max(int a,int b)
{
	if(a>b)
		return a;
	else
		return b;
}

int ht(NODE a)
{
	if(a==NULL)
		return 0;
	return	1+max(ht(a->llink),ht(a->rlink));
}//----------------------------------------------------------------------------------//
// This function finds the sibling of
// the child and then returns its 
// maximum height.
int sibling_ht(NODE X)
{
	// NODE IS NOT ROOT
	if(X->parent!=NULL)
	{
		// IF NODE IS ON RIGHT.
		if(X==X->parent->rlink)
		{
			// RETURN HEIGHT OF LEFT.
			if(X->parent->llink==NULL)
				return 0;
			else
				return ht(X->parent->llink);
		}
		// IF NODE IS ON LEFT.
		if(X==X->parent->llink) 
		{
			// RETURN HEIGHT OF RIGHT.
			if(X->parent->rlink==NULL)
				return 0;
			else
				return ht(X->parent->rlink);
		}

	}
}
//-----------------------------------------------------------------------------------//



// ROTATION function balances the
// unbalanced AVL tree.
// Cases are mentioned below.
void rotation(NODE Z,NODE Y)
{
	NODE X;
	// ASSIGN VALUE TO Y.
	if( Y->llink != NULL && Y->rlink!=NULL)
		X=( ht(Y->llink) > ht(Y->rlink) )? Y->llink: Y->rlink;
		else if(Y->llink==NULL)
			X=Y->rlink;
	  		else
				X=Y->llink;
	// 4 CASES:
	if(X->info < Z->info)
	{
		
			if(X->info < Y->info)
			{
				right_rotate_avl(Y,Z);			// CASE LEFT-LEFT.
				avl_count++;
			}
			else
			{
				left_rotate_avl(X,Y);			// CASE LEFT-RIGHT.
				right_rotate_avl(X,Z);
				avl_count+=2;
			}
	}
	else
	{
			if(X->info < Y->info)
			{
				right_rotate_avl(X,Y);			//CASE RIGHT-LEFT.
				left_rotate_avl(X,Z);
				avl_count+=2;
			}
			else
			{
				left_rotate_avl(Y,Z);			//CASE RIGHT-RIGHT.
				avl_count++;
			}
	}
}
//-----------------------------------------------------------------------------------//

void avl_insert(long int info)
{
	NODE cur=root_avl,prev=NULL,nw_node=getnode_avl();
	nw_node->info=info;

	// CASE 1: ROOT IS NULL
	if(root_avl==NULL)			//condition when the tree is empty
	{
		root_avl=nw_node;
		return;
	}
	
	// CASE 2: ROOT IS NOT NULL
	// BST insertion is done.
	while(cur!=NULL)
	{
		prev=cur;
		if(cur->info==info)
			return;
		if(cur->info < info)
			cur=cur->rlink;
		else
			cur=cur->llink;
	}
	if(prev->info>info)
		prev->llink=nw_node;
	else
		prev->rlink=nw_node;
	nw_node->parent=prev;
	cur=nw_node;
	

		while(cur!=NULL)
		{
			// Difference between the height of the 
			// sibling node is checked for 
			// balance condition.
			if( abs(ht(cur)-(sibling_ht(cur))) > 1 )
				rotation(cur->parent,cur);		// if true then rotation is called.
			cur=cur->parent;

		}
}
//-------------------------------------------------------------------------------------//
main(int argc, char **argv)
{
	int size;

	// Check command line arguments for number of elements.
	if (argc > 2)
	{
		printf(" Need one argument. Ignoring the rest.\n");
		size = atoi(argv[1]);
	}
	else if (argc == 2)
	{
		size = atoi(argv[1]);
	}
	else 
	{
		printf("Need one argument i.e. number of elements.\n");
		exit(3);
	}
	printf(" Experimenting with %d elements \n", size);

	
	// Generate random elements.
	int i,j;
	double avlTime;
	timeStart();
	for(i=1; i <= size; i++)
	{
		avl_insert(random() % 34657879);
	}
	avlTime = timeStop("Inserting finish\n");
 
	// Generate random elements.
	double redTime;
	timeStart();
	for(i=1; i <= size; i++)
	{
		rb_insert(random() % 34657879);
	}
	redTime = timeStop("Inserting finish\n");
 
	//dumping the actual time taken.
	FILE *dumpfile = fopen("avl.txt","a");
	fprintf(dumpfile,"%d %f\n",size,avlTime);
	fclose(dumpfile);
	
	//dumping the actual time taken.
	dumpfile = fopen("red-black.txt","a");
	fprintf(dumpfile,"%d %f\n",size,redTime);
	fclose(dumpfile);
	
	
	//dumping the actual time taken.
	dumpfile = fopen("rotation.txt","a");
	fprintf(dumpfile,"%d %d %d\n",size,avl_count,rb_count);
	fclose(dumpfile);
}

