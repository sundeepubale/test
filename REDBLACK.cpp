#include<iostream>
#include<cstdlib>
using namespace std;
class node
{
public:
	node(int a) :clr(0)
	{
		key = a;
		parent = left = right = NULL;
	}
	node *left, *right, *parent;
	int key,clr;
};
int maxi(int a, int b)
{
	return a > b ? a : b;
}
class tree
{
public:
	tree() :splay(NULL)
	{
		root = NULL;
	}
int search(int k)
 {
		if (isnull())
			return 0;
		int f = 1;
		node* t = root;
		while (t != NULL)
		{
			splay = t;
			if (t->key == k)
				return 1;
			
			else if (t->key > k)
				t = t->left;
			else
				t = t->right;
		}
	return 0;
 }
int insert(int k)
{
	if (isnull())
	{
		root = new node(k);
		root->clr = 1;
		return 1;
	}
	if (search(k))
		return 0;

	if (splay->key < k)
	{
		splay->right = new node(k);
		splay->right->parent = splay;
		splay = splay->right;
	}
	else
	{
		splay->left = new node(k);
		splay->left->parent = splay;
		splay = splay->left;
	}
	if (splay->parent->clr==0)
		balance();
	return 1;
 }
void balance()
{ 
	node *x, *y, *z;
	x = splay;
	y = x->parent;
	z = y->parent;
	node* t = z->parent;
	int f = 0,c=1;
	if (y->key < x->key)
		f++;
	if (z->key < y->key)
	{
		f += 2;
		if (z->left != NULL && z->left->clr == 0)
			c = 0;
	}
	else
	{
		if (z->right != NULL && z->right->clr == 0)
			c = 0;
	}
	if (c)
	{
		if (f == 0)
		{
			z->left = y->right;
			if (z->left != NULL)
				z->left->parent = z;
			y->right = z;
			z->parent = y;
			y->parent = t;
			y->clr = 1;
			z->clr = 0;
			if (t != NULL)
			{
				if (t->key < y->key)
					t->right = y;
				else
					t->left = y;
			}
			else
				root = y;
   		}
		else if (f == 3)
		{
			z->right = y->left;
			if (z->right != NULL)
				z->right->parent = z;
			y->left = z;
			z->parent = y;
			y->parent = t;
			y->clr = 1;
			z->clr = 0;
			if (t != NULL)
			{
				if (t->key < y->key)
					t->right = y;
				else
					t->left = y;
			}
			else
				root = y;
		}
		else if (f == 1)
		{
			z->left = x->right;
			if (z->left != NULL)
				z->left->parent = z;
			y->right = x->left;
			if (y->right != NULL)
				y->right->parent = y;
			x->right = z;
			z->parent = x;
			x->left = y;
			y->parent = x;
			x->parent = t;
			x->clr = 1;
			z->clr = 0;
			if (t != NULL)
			{
				if (t->key < x->key)
					t->right = x;
				else
					t->left = x;
			}
			else
				root = x;
		}
		else
		{
			z->right = x->left;
			if (z->right != NULL)
				z->right->parent = z;
			y->left = x->right;
			if (y->left != NULL)
				y->left->parent = y;
			x->left = z;
			z->parent = x;
			x->right = y;
			y->parent = x;
			x->parent = t;
			x->clr = 1;
			z->clr = 0;
			if (t != NULL)
			{
				if (t->key < x->key)
					t->right = x;
				else
					t->left = x;
			}
			else
				root = x;
		}
	   }
	else
	{
	     	z->left->clr = 1;
			z->right->clr = 1;
			if (t != NULL)
			{
				z->clr = 0;
				if (t->clr == 0)
				{
					splay = z;
					balance();
				}
			}
	 }
	return;
}
int height(node* n)
	{
		if (n == NULL)
			return 0;
		return maxi(height(n->left), height(n->right)) + 1;
	}
	node* max(node* s)
	{
		while (s->right != NULL)
			s = s->right;
		return s;
	}
	void display()
{
     	if (root == NULL)
			return;
		cout << "----------------------------------------------\n";
		int h = height(root);
		int num = (1 << h) - 1;
		node* *ptr = new node*[num];
		int* f = new int[num];
		int i, j, k;
		for (i = 0; i < num; i++)
		{
			ptr[i] = NULL;
			f[i] = 0;
		}
		ptr[0] = root;
		f[0] = 1;
		for (i = 0, k = 1; k < num; i++)
		{
			if (f[i])
			{
				if (ptr[i]->left != NULL)
				{
					ptr[k] = ptr[i]->left;
					f[k] = 1;
				}
				k++;
				if (ptr[i]->right != NULL)
				{
					ptr[k] = ptr[i]->right;
					f[k] = 1;
				}
				k++;
			}
			else
				k += 2;
		}

		int p, q, c;
		p = (1 << h)*(0 + 2) - 2;
		for (i = 1, c = 0; i <= h; i++)
		{
			q = (p - 2) / 2;
			for (j = 0; j < q; j++)
				cout << " ";
			for (j = 1; j <= (1 << (i - 1)); j++, c++)
			{
				if (f[c])
				{
					if (ptr[c]->clr)
						cout << "b";
					else 
						cout << "r";
					cout << ptr[c]->key;
				}
				else
					cout << "  ";
				for (int temp = 1; temp <= p; temp++)
					cout << " ";
			}
			p = q;
			cout << endl;
			cout << endl;
		}

	}
int isnull()
{
	return root == NULL;
}
node* root, *splay;
int delet(int k)
{
	if (isnull())
		return 0;
	if (!search(k))
		return 0;
	node* temp = splay;
	int f = 0,g=0;
	if (splay->left != NULL && splay->right != NULL)
	{
		node* del = max(splay->left);
		splay->key = del->key;
		if (del->left != NULL)
		{
			del->left->parent = del->parent;
			if (del->parent->key < del->key)
				del->parent->right = del->left;
			else
				del->parent->left = del->left;
			splay = del->parent;
			del->left->clr = 1;
		}
		else
		{
			if (del->parent != splay)
			{
				del->parent->right = NULL;
				g = 1;
			}
			else
				del->parent->left = NULL;
			if (del->clr)
				f = 1;
			
			splay = del->parent;
		}
	}
	else if (splay == root)
	{
		if (root->left == NULL && root->right == NULL)
			root = NULL;
		else if (root->left != NULL)
		{
			root = root->left;
			root->parent = NULL;
			root->clr = 1;
		}
		else
		{
			root = root->right;
			root->parent = NULL;
			root->clr = 1;
		}
		return 1;
	}
	else if (splay->left == NULL && splay->right == NULL)
	{
		if (splay->clr)
			f = 1;
			
		
	   if (splay->key > splay->parent->key)
	   {
		   splay->parent->right = NULL;
		   g = 1;
	   }
		else
			splay->parent->left = NULL;
		splay = splay->parent;
	}
	else
	{
		if (splay->left != NULL)
		{
			splay->left->parent = splay->parent;
			if (splay->key > splay->parent->key)
				splay->parent->right = splay->left;
			else
				splay->parent->left = splay->left;
			splay = splay->left;
			splay->clr = 1;
		}
		else
		{
			splay->right->parent = splay->parent;
			if (splay->key > splay->parent->key)
				splay->parent->right = splay->right;
			else
				splay->parent->left = splay->right;
			splay = splay->right;
			splay->clr = 1;
		}
		splay = splay->parent;
	}
	if (f)
		delbalance(g);
	return 1;
}
void delbalance(int g)
{
	node* x, *y, *z = splay;
	node* t = z->parent;
	if (g)
	{
		y = z->left;
		if (y->clr)
		{	
			if (((y->left == NULL) && (y->right == NULL)) ||((y->left!=NULL)&&(y->right!=NULL)&&(y->left->clr) && (y->right->clr)))
			{
				y->clr = 0;
				if (!z->clr)
				{
					z->clr = 1;
					return;
				}
				z->clr = 1;
				if (z != root)
				{
					splay = z->parent;
					if (z->key > z->parent->key)
						delbalance(1);
					else
						delbalance(0);
				}
			}
			else if ((y->right!=NULL)&&!(y->right->clr))
			{
				x = y->right;
				z->left = x->right;
				x->parent = t;
				if (z->left != NULL)
					z->left->parent = z;
				y->right = x->left;
				if (y->right != NULL)
					y->right->parent = y;
				x->right = z;
				z->parent = x;
				x->left = y;
				y->parent = x;
				if (t != NULL)
				{
					if (t->key < x->key)
						t->right = x;
					else
						t->left = x;
				}
				else
					root = x;
				x->clr = z->clr;
				y->clr = 1;
				z->clr = 1;
			}
			else
			{
				x = y->left;
				z->left = y->right;
				if (z->left != NULL)
					z->left->parent = z;
				y->right = z;
				z->parent = y;
				y->parent = t;
				if (t != NULL)
				{
					if (t->key < y->key)
						t->right = y;
					else
						t->left = y;
				}
				else
					root = y;
				y->clr = z->clr;
				x->clr = z->clr = 1;

			}
		}
		else
		{
	     	x = y->right;
			if ((((x->left == NULL) && ((x->right) == NULL))) ||((x->left!=NULL)&&(x->right!=NULL)&& (x->left->clr) && (x->right->clr)))
			{
				z->left = y->right;
				if (z->left != NULL)
					z->left->parent = z;
				y->right = z;
				z->parent = y;
				y->parent = t;
				if (t != NULL)
				{
					if (t->key < y->key)
						t->right = y;
					else
						t->left = y;
				}
				else
					root = y;
				y->clr = 1;
				z->left->clr = 0;

			}
			else if ((x->right!=NULL)&&!(x->right->clr))
			{
				node* w = x->right;
				z->left = w->right;
				if (z->left != NULL)
					z->left->parent = z;
				x->right = w->left;
				if (x->right != NULL)
					x->right->parent = x;
				w->parent = t;
				w->right = z;
				z->parent = w;
				w->left = y;
				y->parent = y;
				if (t != NULL)
				{
					if (t->key < w->key)
						t->right = w;
					else
						t->left = w;
				}
				root = w;
				w->clr = 1;
			}
			else
			{
				x->left->clr = 1;
				z->left = x->right;
				x->parent = t;
				if (z->left != NULL)
					z->left->parent = z;
				y->right = x->left;
				if (y->right != NULL)
					y->right->parent = y;
				x->right = z;
				z->parent = x;
				x->left = y;
				y->parent = x;
				if (t != NULL)
				{
					if (t->key < x->key)
						t->right = x;
					else
						t->left = x;
				}
				else
					root = x;
			}
		}
	}
	else
	{
		y = z->right;
	    	if (y->clr)
		{
			if (((y->left == NULL) && (y->right == NULL)) || ((y->left!=NULL)&&(y->right!=NULL)&&(y->left->clr) && (y->right->clr)))
			{
				y->clr = 0;
				if (!(z->clr))
				{
					z->clr = 1;
					return;
				}
				z->clr = 1;
				if (z != root)
				{
					splay = z->parent;
					if (z->key > z->parent->key)
						delbalance(1);
					else
						delbalance(0);
				}
			}
			else if ((y->left!=NULL)&&!(y->left->clr))
			{
				x = y->left;
				z->right = x->left;
				x->parent = t;
				if (z->right != NULL)
					z->right->parent = z;
				y->left = x->right;
				if (y->left != NULL)
					y->left->parent = y;
				x->left = z;
				z->parent = x;
				x->right = y;
				y->parent = x;
				if (t != NULL)
				{
					if (t->key < x->key)
						t->right = x;
					else
						t->left = x;
				}
				else
					root = x;
				x->clr = z->clr;
				y->clr = 1;
				z->clr = 1;
			}
			else
			{
				x = y->right;
				z->right = y->left;
				if (z->right != NULL)
					z->right->parent = z;
				y->left = z;
				z->parent = y;
				y->parent = t;
				if (t != NULL)
				{
					if (t->key < y->key)
						t->right = y;
					else
						t->left = y;
				}
				else
					root = y;
				y->clr = z->clr;
				x->clr = z->clr = 1;

			}
		}
		else
		{
			x = y->left;
			if ((((x->left == NULL) && ((x->right) == NULL))) ||((x->right!=NULL)&&(x->left!=NULL)&&(x->left->clr) && (x->right->clr)))
			{
				z->right = y->left;
				if (z->right != NULL)
					z->right->parent = z;
				y->left = z;
				z->parent = y;
				y->parent = t;
				if (t != NULL)
				{
					if (t->key < y->key)
						t->right = y;
					else
						t->left = y;
				}
				else
					root = y;
				y->clr = 1;
				z->left->clr = 0;

			}
			else if ((x->left!=NULL)&&!(x->left->clr))
			{
				node* w = x->left;
				z->right = w->left;
				if (z->right != NULL)
					z->right->parent = z;
				x->left = w->right;
				if (x->left != NULL)
					x->left->parent = x;
				w->parent = t;
				w->left = z;
				z->parent = w;
				w->right = y;
				y->parent = y;
				if (t != NULL)
				{
					if (t->key < w->key)
						t->right = w;
					else
						t->left = w;
				}
				root = w;
				w->clr = 1;
			}
			else
			{
				x->right->clr = 1;
				z->right = x->left;
				x->parent = t;
				if (z->right != NULL)
					z->right->parent = z;
				y->left = x->right;
				if (y->left != NULL)
					y->left->parent = y;
				x->left = z;
				z->parent = x;
				x->right = y;
				y->parent = x;
				if (t != NULL)
				{
					if (t->key < x->key)
						t->right = x;
					else
						t->left = x;
				}
				else
					root = x;
			}
		}
	}

}
};

int main()
{
	int f = 1, c, t;
	tree tr;
	while (f)
	{
		cout << "enter  \n1 Insert\n2 search\n3 delete \n4 display\n:";

		cin >> c;
		if (c == 1)
		{
			cout << "enter the value to be inserted : ";
			cin >> t;
			if (tr.insert(t))
				cout << t << " is successfully inserted\n";
			else
				cout << t << " is already present in the tree\n";
		}
		else if (c == 2)
		{
			cout << "enter the value to search for : ";
			cin >> t;
			if (tr.search(t))
				cout << "element found\n";
			else
				cout << "element not found\n";
		}

		else if (c == 3)
		{
			cout << "enter the value to be deleted : ";
			cin >> t;
			if (tr.delet(t))
				cout << t << " is successfully deleted\n";
			else
				cout << t << " is not found\n";
		}
		else if (c==4)
			tr.display();
		else
			f = 0;
			
			cout << "\n----------------------------------------------------------------\n";
	
	}

	return 0;
}