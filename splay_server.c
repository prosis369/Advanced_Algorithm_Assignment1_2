#include<stdio.h>
#include<stdlib.h>

int count_copy = 0;

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

// Creates a new node with a key and value. 
// Makes the left and right node NULL.
node* newNode(int key, int value) 
{ 
	node* new = (node*)malloc(sizeof(node)); 
	new->value  = value;
	new->key = key;
	new->left = NULL;
	new->right = NULL;
	return (new); 
}

node *rr(node* x) 
{ 
	node* temp = x->left; 
	x->left = temp->right; 
	temp->right = x; 
	count_copy++;
	return temp; 
} 

node *lr(node* x) 
{ 
	node* temp = x->right; 
	x->right = temp->left; 
	temp->left = x; 
	count_copy++;
	return temp; 
} 

// Makes the node with key or last seen node, root node / head node.
node *splay(node* head, int key) 
{ 
	if (head == NULL)
	{
		return head; 
	}
	if (head->key == key)
	{
		return head;
	}
	if (head->key > key) 
	{ 
		if (head->left == NULL)
		{
			return head; 
		}
		if (head->left->key > key) 
		{ 
			head->left->left = splay(head->left->left, key); 
			head = rr(head); 
		} 
		else if (head->left->key < key)
		{ 
			head->left->right = splay(head->left->right, key); 
			if (head->left->right != NULL) 
				head->left = lr(head->left); 
		} 

		return (head->left == NULL)? head: rr(head); 
	}

	else
	{  
		if (head->right == NULL) return head; 
		if (head->right->key > key) 
		{ 
			head->right->left = splay(head->right->left, key); 
			if (head->right->left != NULL) 
				head->right = rr(head->right); 
		} 
		else if (head->right->key < key)
		{ 
			head->right->right = splay(head->right->right, key); 
			head = lr(head); 
		} 

		return (head->right == NULL)? head: lr(head); 
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
		// Creates a new node if root key is different to the key to be inserted.
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
		// Updates the value of key in root, if key to be inserted is same as root key.
		else
		{
			s->root->value = value;
		}
	}
	// printf("\nRoot I: %d\n", s->root->key);
	// preOrder(s->root);
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
		// Makes the node of the key as root.
		s->root = splay(s -> root, key);
		// printf("\nRoot F: %d\n", s->root->key);
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