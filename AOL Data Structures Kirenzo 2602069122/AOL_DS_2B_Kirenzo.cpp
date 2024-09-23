#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	int num;
	int height;
	
	node* L;
	node* R;
};

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int height(node* n)
{
	if(n == NULL)
	{
		return 0;
	}
	return n->height;
}

node* createnew(int num)
{
	node* newnode = (node*)malloc(sizeof(node));
	newnode->num = num;
	newnode->height = 1;
	newnode->L = NULL;
	newnode->R = NULL;
	
	return newnode;
}

node* RRotate(node *y)
{
	node *x = y->L;
	node *z = x->R;
	
	x->R = y;
	y->L = z;
	
	y->height = max(height(y->L), height(y->R)) + 1;
	x->height = max(height(x->L), height(x->R)) + 1;
	
	return x;
}

node* LRotate(node *x)
{
	node *y = x->R;
	node *z = y->L;
	
	y->L = x;
	x->R = z;
	
	x->height = max(height(x->L), height(x->R)) + 1;
	y->height = max(height(y->L), height(y->R)) + 1;
	
	return y;
}

int getbal(node *n)
{
	if(n == NULL)
	{
		return 0;
	}
	return height(n->L) - height(n->R);
}

node* push(node *root, int num)
{
	if(root == NULL)
	{
		return createnew(num);
	}
	
	if(num < root->num)
	{
		root->L = push(root->L, num);
	}
	else if(num > root->num)
	{
		root->R = push(root->R, num);
	}
	else
	{
		return root;
	}
	
	root->height = 1 + max(height(root->L), height(root->R));
	
	int bal = getbal(root);

	if(bal > 1 && getbal(root->L) > 0)
	{
		return RRotate(root);
	}
	if(bal < -1 && getbal(root->R) < 0)
	{
		return LRotate(root);
	}
	if(bal > 1 && getbal(root->L) < 0)
	{
		root->L = LRotate(root->L);
		return RRotate(root);
	}
	if(bal < -1 && getbal(root->R) > 0)
	{
		root->R = RRotate(root->R);
		return LRotate(root);
	}
	
	return root;
}

node* minval (node *n) 
{
	node* curr = n;
	
	while(curr->R != NULL)
	{
		curr = curr->R;
	}
	return curr;
}

void search(node *root, int num)
{
	if(root == NULL)
	{
		printf("Value %d not found\n", num);
		return;
	}
	
	if(num < root->num)
	{
		search(root->L, num);
	}
	else if(num > root->num)
	{
		search(root->R, num);
	}
	else
	{
		printf("Value %d found\n", num);
	}
}

node* pop(node *root, int num)
{
	if(root == NULL)
	{
		printf("Value %d not found\n", num);
		return NULL;
	}
	
	if(num < root->num)
	{
		root->L = pop(root->L, num);
	}
	else if(num > root->num)
	{
		root->R = pop(root->R, num);
	}
	else
	{
		if(root->L == NULL || root->R == NULL)
		{
			node* temp = NULL;
			if(root->L)
			{
				temp = root->L;
			}
			else
			{
				temp = root->R;
			}
			root = temp;
			free(temp);
			
			if(root == NULL)
			{
				return NULL;
			}
		}
		else
		{
			node *temp = minval(root->L);
			root->num = temp->num;
			root->L = pop(root->L, temp->num);
		}
		
		printf("Value %d was deleted\n", num);
	}
	
	int bal = getbal(root);

	if(bal > 1 && getbal(root->L) >= 0)
	{
		return RRotate(root);
	}
	if(bal < -1 && getbal(root->R) <= 0)
	{
		return LRotate(root);
	}
	if(bal > 1 && getbal(root->L) < 0)
	{
		root->L = LRotate(root->L);
		return RRotate(root);
	}
	if(bal < -1 && getbal(root->R) > 0)
	{
		root->R = RRotate(root->R);
		return LRotate(root);
	}
	
	return root;
}

void preorder(node *root)
{
	if(root != NULL)
	{
		printf("%d ", root->num);
		preorder(root->L);
		preorder(root->R);
	}
}

void inorder(node *root)
{
	if(root != NULL)
	{
		inorder(root->L);
		printf("%d ", root->num);
		inorder(root->R);
	}
}

void postorder(node* root)
{
	if(root != NULL)
	{
		preorder(root->L);
		preorder(root->R);
		printf("[%d] ", root->num);
	}
}

int main()
{
	
	node* root = NULL;
	int active = 1;
	
	while(active != 0)
	{
		printf("1. Insertion\n");
		printf("2. Deletion\n");
		printf("3. Traversal\n");
		printf("4. Exit\n");
		printf("Choose: ");
		
		int select;
		scanf("%d", &select); getchar();
		
		if(select == 1)
		{
			int insert;
			printf("Insert: ");
			scanf("%d", &insert);
			
			root = push(root, insert);
		}
		else if(select == 2)
		{
			int delnum;
			printf("Delete: ");
			scanf("%d", &delnum);
			
			root = pop(root, delnum);
		}
		else if(select == 3)
		{
			printf("Preorder Notation: ");
			preorder(root);
			puts("");
			
			printf("Inorder Notation: ");
			inorder(root);
			puts("");
			
			printf("Postorder Notation: ");
			postorder(root);
			puts("");
		}
		else if(select == 4)
		{
			active = 0;	
		}
	}
	
	printf("Thank you\n");
	return 0;
}
