#include<stdio.h>
#include<stdlib.h>

typedef struct node 
{ 
	int key;
	int value;
	struct node *left, *right;

}node;

typedef struct splaytree
{
	node* root;

}splaytree;

void* make_new_dictionary()
{
	splaytree *s = (splaytree*)malloc(sizeof(splaytree));
	s -> root = NULL;
	return s;
}

node* newNode(int key, int value) 
{ 
	node* new = (node*)malloc(sizeof(node)); 
	new->value  = value;
	new->key = key;
	new->left = NULL;
	new->right = NULL;
	return (new); 
}

node *rightRotate(node* x) 
{ 
	node* y = x->left; 
	x->left = y->right; 
	y->right = x; 
	return y; 
} 

node *leftRotate(node* x) 
{ 
	node* y = x->right; 
	x->right = y->left; 
	y->left = x; 
	return y; 
} 

node *splay(node* root, int key) 
{ 
	if (root == NULL || root->key == key)
	{
		return root; 
	}

	if (root->key > key) 
	{ 
		if (root->left == NULL) return root; 

		if (root->left->key > key) 
		{ 
			root->left->left = splay(root->left->left, key); 
			root = rightRotate(root); 
		} 
		else if (root->left->key < key)
		{ 
			root->left->right = splay(root->left->right, key); 
			if (root->left->right != NULL) 
				root->left = leftRotate(root->left); 
		} 

		return (root->left == NULL)? root: rightRotate(root); 
	} 
	else
	{  
		if (root->right == NULL) return root; 
		if (root->right->key > key) 
		{ 
			root->right->left = splay(root->right->left, key); 
			if (root->right->left != NULL) 
				root->right = rightRotate(root->right); 
		} 
		else if (root->right->key < key)
		{ 
			root->right->right = splay(root->right->right, key); 
			root = leftRotate(root); 
		} 

		return (root->right == NULL)? root: leftRotate(root); 
	} 
} 

void preOrder(node* root) 
{ 
	if (root != NULL) 
	{ 
		printf("%d-%d, ", root->key, root->value);
		preOrder(root->left);  
		preOrder(root->right); 
	}
}

void insert(void* dictionary, int key, int value)
{
	splaytree *s = dictionary;
	if(s -> root == NULL)
	{
		s -> root = newNode(key, value);
	}
	else
	{
		s -> root = splay(s -> root, key);
		if(s->root->key != key)
		{
			node *new = newNode(key,value);
			if(s->root->key > key)
			{
				new->right = s->root; 
				new->left = s->root->left; 
				s->root->left = NULL; 
			}
			else
			{ 
				new->left = s->root; 
				new->right = s->root->right; 
				s->root->right = NULL; 
			}
			s->root = new;
		}
		else
		{
			s->root->value = value;
		}
	}
	printf("\nRoot I: %d\n", s->root->key);
	preOrder(s->root);
}

int find(void* dictionary, int key)
{
	splaytree *s = dictionary;
	if(s -> root == NULL)
	{
		return -1;
	}
	else
	{
		s -> root = splay(s -> root, key);
		printf("\nRoot F: %d\n", s->root->key);
		if(s->root->key == key)
		{
			return s->root->key;
		}
		else
		{
			return -1;
		}
	}
}