#include<iostream>
#include<cstdlib>
using namespace std;
int maxi(int a, int b)
{
	return a > b ? a : b;
}
class node
{
public:
	node(int a)
	{
		key = a;
		parent=left = right = NULL;
	}
	node *left, *right,*parent;
	int key;
};
class tree
{
public:
	tree():splay(NULL)
	{
		root = NULL;
	}
	int search(int k,int f1)
	{
		if (isnull())
			return 0;
		int f = 1;
		node* t = root;
		while (t!=NULL)
		{
			splay = t;
			if (t->key == k)
			{
				if (f1)
				rotate();
				return 1;
			}
			else if (t->key > k)
				t = t->left;
			else
				t = t->right;
        }
		if (f1)
		rotate();
		return 0;
	}
	int insert(int k)
	{
		if (isnull())
		{
			root = new node(k);
			return 1;
		}
		if (search(k, 0))
		{
			rotate();
			return 0;
		}
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
		rotate();
		return 1;
	}
	node* min(node* s)
	{
		while (s->left!= NULL)
			s = s->left;
		return s;
	}
	node* max(node* s)
	{
		while (s->right != NULL)
			s = s->right;
		return s;
	}
	
	int delet(int k)
	{
		if (isnull())
			return 0;
		if (!search(k,0))
			return 0;

		node* temp = splay;
		if (splay->left != NULL && splay->right != NULL)
		{
			node* del=max(splay->left);
			splay->key = del->key;
			if (del->left != NULL)
			{
				del->left->parent = del->parent;
				if (del->parent->key < del->key)
					del->parent->right = del->left;
				else
					del->parent->left = del->left;
				splay = del->parent;
			}
			else
			{
				if (del->parent != splay)
					del->parent->right = NULL;
				else
					del->parent->left = NULL;
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
			}
			else
			{
				root = root->right;
				root->parent = NULL;
			}
			return 1;
		}
	   else if (splay->left == NULL && splay->right == NULL)
		{
			if (splay->key > splay->parent->key)
				splay->parent->right = NULL;
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
			}
			else
			{
				splay->right->parent = splay->parent;
				if (splay->key > splay->parent->key)
					splay->parent->right = splay->right;
				else
					splay->parent->left = splay->right;
				splay = splay->right;
			}
			splay = splay->parent;
		}
	   rotate();
	   return 1;
}
	int height(node* n)
	{
		if (n == NULL)
			return 0;
		return maxi(height(n->left), height(n->right)) + 1;
	}
	void display()
	{
		if (root == NULL)
			return;
		cout << "----------------------------------------------\n";
		int h = height(root);
		int num = (1 << h )- 1;
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
		for (i = 0,k=1; k < num; i++)
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
	
		int p, q,c;
		p = (1 << h)*(0 + 2) - 2;
		for (i = 1,c=0; i <= h; i++)
		{
			q = (p - 2) / 2;
			for (j = 0; j < q; j++)
				cout << " ";
			for (j = 1; j <= (1 << (i-1)); j++,c++)
			{
				if (f[c])
				{
					if (ptr[c]->key < 10 && ptr[c]->key >= 0)
						cout << " ";
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
	void rotate()
	{
		node* x, *y;
		if ((x = splay->parent) == NULL)
			return;
		
		if ((y = x->parent) == NULL)
		{
			splay->parent = NULL;
			root = splay;
			x->parent = splay;
			if (x->key>splay->key)
			{
				x->left = splay->right;
				if (x->left != NULL)
					x->left->parent = x;
				splay->right = x;
			}
			else
			{
				x->right = splay->left;
				if (x->right != NULL)
					x->right->parent = x;
				splay->left = x;
			}
		
		}
		else
		{
			int f = 0;
			if (splay->key > x->key)
				f++;
			if (x->key > y->key)
				f += 2;
			node *z = y->parent;
			splay->parent = z;
			if (z != NULL)
			{
				if (z->key < splay->key)
					z->right = splay;
				else
					z->left = splay;
			}
			if (f == 0)
			{
				y->left = x->right;
				if (y->left != NULL)
					y->left->parent = y;
				x->left = splay->right;
				if (x->left != NULL)
					x->left->parent = x;
				x->right = y;
				y->parent = x;
				splay->right = x;
				x->parent = splay;
			}
			else if (f == 3)
			{
				y->right =x->left;
				if (y->right != NULL)
					y->right->parent = y;
				x->right = splay->left;
				if (x->right != NULL)
					x->right->parent = x;
				x->left = y;
				y->parent = x;
				splay->left = x;
				x->parent = splay;
			}
			else if (f == 1)
			{
				x->right = splay->left;
				if (x->right != NULL)
					x->right->parent = x;
				y->left = splay->right;
				if (y->left != NULL)
					y->left->parent = y;
				splay->left = x;
				x->parent = splay;
				splay->right = y;
				y->parent = splay;
			}
			else
			{
				x->left = splay->right;
				if (x->left != NULL)
					x->left->parent = x;
				y->right = splay->left;
				if (y->right != NULL)
					y->right->parent = y;
				splay->right = x;
				x->parent = splay;
				splay->left = y;
				y->parent = splay;
			}
			if (z == NULL)
				root = splay;
			else
				rotate();
		}


	}
   	
	
	
	
	int isnull()
	{
		return root == NULL;
	}
	node* root,*splay;
};



int main()
{
	int f = 1,c,t;
	tree tr;
	cout << " SPLAY TREE\n";
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
			if (tr.search(t,1))
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
		else if (c == 4)
			tr.display();
		else
			f = 0;
		cout << "\n----------------------------------------------------------------\n";
	
	}

	return 0;
}