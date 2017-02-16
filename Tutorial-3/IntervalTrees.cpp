#include <iostream>
#include <utility>
#define mp make_pair
#define F first
#define S second
using namespace std;

typedef pair<int,int> pii;

struct node{
	pii in;
	int maxi;
	node *left, *right;
};

node *root = NULL;

node *insert(node* root, pii in)
{
	if(root==NULL)
	{
		node *leaf = new node;
		leaf->in = in;
		leaf->maxi = in.S;
		leaf->left = NULL;
		leaf->right = NULL;
		return leaf;
	}
	int temp = root->in.F;
	if(temp>in.F)	root->left = insert(root->left, in);
	else	root->right = insert(root->right, in);
	if(root->maxi<in.S)	root->maxi = in.S;
	return root;
}

node *Func(node* root)
{
	node* temp = root;
	while(temp->left!=NULL)
	{
		temp = temp->left;
	}
	return temp;
}

node *maxUpdate(node* root)
{
	if(root==NULL)	return NULL;
	maxUpdate(root->left);
	maxUpdate(root->right);
	if(root->right!=NULL)
	{
		if((root->left)!=NULL)
		{
			root->maxi = max(max(root->left->maxi, root->right->maxi), root->in.S);
		}
		else
		{
			root->maxi = max(root->right->maxi, root->in.S);
		}
	}
	else
	{
		if((root->left)!=NULL)
		{
			root->maxi = max(root->left->maxi, root->in.S);
		}
		else
		{
			root->maxi = root->in.S;
		}
	}
	return root;
}

node *del(node* root, pii in)
{
	if(root==NULL)	return NULL;
	if(in.F<(root->in.F))
	{
		root->left = del(root->left, in);
	}
	else if(in.S>(root->in.S))
	{
		root->right = del(root->right, in);
	}
	else
	{
		if(root->left==NULL)
		{
			node* temp = root->right;
			root = NULL;
			return temp;
		}
		else if(root->right==NULL)
		{
			node* temp = root->left;
			root = NULL;
			return temp;
		}
		node* temp = Func(root->right);
		root->in = temp->in;
		root->right = del(root->right, temp->in);
	}
	root = maxUpdate(root);
	return root;
}

pii *search(node *root, pii in) 
{
	if(root==NULL)	return NULL;
	if(root->in.F<=in.S && in.F<=root->in.S)	return &(root->in);
	if(root->left!=NULL && root->left->maxi >= in.F)	return search(root->left, in);
	return search(root->right, in);
}

void Display(node *root)
{
	if(root==NULL)	return;
	Display(root->left);
 
    cout << "(" << root->in.F << ", " << root->in.S << ")" << " maxi = " << root->maxi << "\n";
 
    Display(root->right);
    return;
}

int main()
{
	int n, l, r;
	cin >> n;
	for(int i = 1; i<=n; i++)
	{
		cin >> l >> r;
		root = insert(root, mp(l, r));
	}
	Display(root);
	pii *ans = search(root, mp(6, 7));
	cout << ans->F << " " << ans->S << "\n";

	return 0;
}