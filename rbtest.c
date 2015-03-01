#include <stdio.h>
#include <stdlib.h>
static int gName=0;
enum cr {RED, BLACK};
struct R
{
	int info;
	struct R *parent;
	struct R *llink;
	struct R *rlink;
	enum cr color;
};
typedef struct R * NOD;
NOD root_rb=NULL;

// No. of rotations done in avl insertion.
int rb_count=0;

// No. of rotations done in red-black insertion.
int avl_count=0;
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
NOD uncl(NOD child)
{
	if(child->parent==child->parent->parent->rlink)
		return child->parent->parent->llink;
	else
		return child->parent->parent->rlink;
}
NOD grand(NOD child)
{
	return child->parent->parent;
}
void left_rotate_rb(NOD Y,NOD Z)
{
	Z->rlink=Y->llink;
	Y->parent=Z->parent;
	if(Y->parent == NULL)
		root_rb=Y;
	else if(Z == Z->parent->rlink)
		Z->parent->rlink=Y;
	     else 
		Z->parent->llink=Y;	
        if(Y->llink!=NULL)
	   Y->llink->parent=Z;
	Y->llink=Z;
	Z->parent=Y;		
}
void right_rotate_rb(NOD Y,NOD Z)
{
	Z->llink=Y->rlink;
	Y->parent=Z->parent;
	if(Y->parent == NULL)
		root_rb=Y;
	else if(Z == Z->parent->rlink)
		Z->parent->rlink=Y;
	     else 
		Z->parent->llink=Y;
	if(Y->rlink!=NULL)
	    Y->rlink->parent=Z;
	Y->rlink=Z;
	Z->parent=Y;
}

void rb_insert(int info)
{
	NOD temp,cur,prev;
	temp=getnode_rb();
	temp->info=info;
	if(root_rb==NULL)
	{
		root_rb=temp;
		root_rb->color=BLACK;
		return;
	}
	cur=root_rb;
	prev=NULL;
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
	NOD child=temp;
	NOD uncle,grandparent;
	while(child!=root_rb && (child->color==RED && child->parent->color==RED))
	{
		grandparent=grand(child);
		uncle=uncl(child);
		if(uncle==NULL)
		{
			if(child->parent==grandparent->llink && child==child->parent->llink)
			{
				child->parent->color =BLACK;
				grandparent->color=RED;
				child->color=RED;
				right_rotate_rb(child->parent,grandparent);
				rb_count++;
			}
			else if(child->parent==grandparent->rlink && child==child->parent->rlink)
			{
				child->parent->color = BLACK;
				grandparent->color = RED;
				child->color=RED;
				left_rotate_rb(child->parent,grandparent);
				rb_count++;
			}
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
					{
						child->parent->color =RED;
						child->color = BLACK;
						grandparent->color = RED;
						right_rotate_rb(child,child->parent);
						left_rotate_rb(child,grandparent);
						rb_count+=2;
					}
		}
		else if(uncle->color==RED)
		{
			child->parent->color=BLACK;
			uncle->color=BLACK;
			grandparent->color=RED;
			child=grandparent;
		}
			else
			{
				if(child==child->parent->llink && child->parent==grandparent->llink)
				{
					child->parent->color=BLACK;
					grandparent->color=RED;
					child->color=RED;
					right_rotate_rb(child->parent,grandparent);
					rb_count++;
				}
				else if(child==child->parent->llink && child->parent==grandparent->rlink)
					{
						child->color=BLACK;
						grandparent->color=RED;
						child->parent->color=RED;
						right_rotate_rb(child,child->parent);
						left_rotate_rb(child,grandparent);
						rb_count+=2;
					}
					else if(child==child->parent->rlink && child->parent==grandparent->rlink)
						{
							child->parent->color=BLACK;
							grandparent->color=RED;
							child->color=RED;
							left_rotate_rb(child->parent,grandparent);
							rb_count++;
						}
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
void preorderDotDump (NOD root_rb, FILE* outputFile)
{
    if (root_rb != NULL) {

    if (root_rb->color == RED)
            fprintf (outputFile, "%d [label=%d,color=RED];\n",\
                    root_rb->info, root_rb->info);
    else
            fprintf (outputFile, "%d [label=%d,color=BLACK];\n",\
                    root_rb->info, root_rb->info);

        if (root_rb->llink != NULL) 
            fprintf (outputFile, "%d -> %d ;\n", root_rb->info, (root_rb->llink)->info);
        if (root_rb->rlink != NULL)
            fprintf (outputFile, "%d -> %d;\n", root_rb->info, root_rb->rlink->info);
        preorderDotDump (root_rb->llink, outputFile);
        preorderDotDump (root_rb->rlink, outputFile);
    }
}

void dotDump(NOD root_rb, FILE *outFile)
{
    gName++;
    fprintf (outFile, "digraph RB%d {\n",gName);
    preorderDotDump (root_rb, outFile);
    fprintf (outFile, "}\n");
}


int main()
{
	int i,a[10];
	int j,n,ch;
        FILE *outputFile;
	outputFile = fopen ("REDBLACK.dot", "w");	
	fclose (outputFile);
	j=29;
	srand(12347697);
	for (i=1; i<=j; i++)
	{
		rb_insert(rand()%995);
		outputFile = fopen ("REDBLACK.dot", "a");
		if (outputFile != NULL)
        	{
               		dotDump (root_rb,  outputFile);
        	}
		fclose (outputFile);
	}
	return 0;
}

