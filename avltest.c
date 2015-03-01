#include <stdio.h>
#include <stdlib.h>

struct AVL
{
	int info;
	struct AVL *parent;
	struct AVL *llink;
	struct AVL *rlink;
};
static int gName=0;
typedef struct AVL * NODE;

NODE getnode_avl()
{
	NODE x;
	x=(NODE )malloc(sizeof(struct AVL));
	if(x!=NULL)
		x->llink=x->rlink=x->parent=NULL;
	return x;
}

NODE root_avl = NULL;

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
}
int sibling_ht(NODE X)
{
	if(X->parent!=NULL)
	{
	if(X==X->parent->rlink)
	{
		if(X->parent->llink==NULL)
			return 0;
		else
			return ht(X->parent->llink);
	}
	if(X==X->parent->llink)
	{
		if(X->parent->rlink==NULL)
			return 0;
		else
			return ht(X->parent->rlink);
	}
	}
}

void rotation(NODE Z,NODE Y)
{
	NODE X;
	
	if( Y->llink != NULL && Y->rlink!=NULL)
		X=( ht(Y->llink) > ht(Y->rlink) )? Y->llink: Y->rlink;
		else if(Y->llink==NULL)
			X=Y->rlink;
	  		else
				X=Y->llink;

	if(X->info < Z->info)
	{
		if(X->info < Y->info)
			right_rotate_avl(Y,Z);
		else
		{
			left_rotate_avl(X,Y);
			right_rotate_avl(X,Z);
		}
	}
	else
	{
		if(X->info < Y->info)
		{
			right_rotate_avl(X,Y);
			left_rotate_avl(X,Z);
		}
		else
			left_rotate_avl(Y,Z);
	}
}


void avl_insert(long int info)
{
	NODE cur=root_avl,prev=NULL,nw_node=getnode_avl();
	nw_node->info=info;
	if(root_avl==NULL)			//condition when the tree is empty
	{
		root_avl=nw_node;
		return;
	}

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
		if( abs(ht(cur)-(sibling_ht(cur))) > 1 )
			rotation(cur->parent,cur);
		cur=cur->parent;
	}
}

void preorderDotDump (NODE root_avl, FILE* outputFile)
{
    if (root_avl != NULL) {

            fprintf (outputFile, "%d [label=%d];\n",\
                    root_avl->info, root_avl->info);

        if (root_avl->llink != NULL) 
            fprintf (outputFile, "%d -> %d ;\n", root_avl->info, (root_avl->llink)->info);
        if (root_avl->rlink != NULL)
            fprintf (outputFile, "%d -> %d;\n", root_avl->info, root_avl->rlink->info);
        preorderDotDump (root_avl->llink, outputFile);
        preorderDotDump (root_avl->rlink, outputFile);
    }
}

void dotDump(NODE root_avl, FILE *outFile)
{
    gName++;
    fprintf (outFile, "digraph AVL%d {\n",gName);
    preorderDotDump (root_avl, outFile);
    fprintf (outFile, "}\n");
}


int main()
{
	int i,a[10];
	int j,n,ch;
        FILE *outputFile;
	outputFile = fopen ("AVL.dot", "w");	
	fclose (outputFile);
	j=29;
	srand(12347697);
	for (i=1; i<=j; i++)
	{
		avl_insert(rand()%995);
		outputFile = fopen ("AVL.dot", "a");
		if (outputFile != NULL)
        	{
               		dotDump (root_avl,  outputFile);
        	}
		fclose (outputFile);
	}
	return 0;
}

