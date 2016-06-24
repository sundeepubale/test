#include<iostream>
#include<cstdlib>
#include<queue>
#include<vector>
using namespace std;
int max(int a, int b)
{
	return a > b ? a : b;
}
class node
{
public:
	node(int a):hl(0), hr(0)
	{
		key = a;
		parent = left = right = NULL;
	}
	
	node *left, *right, *parent;
	int key,hl,hr;
    
};
class tree
{
public:
	node* root,*splay;
	vector<int> q;
	tree() :splay(NULL)
	{
		root = NULL;
	}
	int isnull()
	{
		return root == NULL;
	}
	node* maxi(node* s)
	{
		q.push_back(0);
		while (s->right != NULL)
		{
			s = s->right;
			q.push_back(1);
		}
		return s;
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
			{
				t = t->left;
				q.push_back(0);
			}
			else
			{
				q.push_back(1);
				t = t->right;
			}
		}
		
		return 0;
	}
	int insert(int k)
	{
		node *x, *y, *z;
		if (isnull())
		{
			root = new node(k);
			return 1;
		}
		if (search(k))
			return 0;
		if (splay->key < k)
		{
			y=splay->right = new node(k);
			splay->hr = 1;
			splay->right->parent = splay;
			
		}
		else
		{
			y=splay->left = new node(k);
			splay->hl = 1;
			splay->left->parent = splay;
	    }
		if (splay == root)
			return 1;
		z = splay;
		x = NULL;
		int f = 1, i = q.size() - 1;
		while (f)
		{
			if (q[i--] == 1)
			{
				if (z->hr <= z->hl)
					return 1;
			}
			else
				if (z->hl <= z->hr)
					return 1;
			if (z == root || abs(z->hl - z->hr) == 2)
				f = 0;
			else
			{
				if (q[i] == 1)
					(z->parent->hr)++;
				else
					(z->parent->hl)++;
				x = y;
				y = z;
				z = z->parent;
			
			}
		 }
		node* t;
		if (abs(z->hl - z->hr) == 2)
		{
			t = z->parent;
			if (x->key > y->key)
				f++;
			if (y->key > z->key)
				f += 2;
			if (f == 3)
			{
				z->hr = y->hl;
				y->hl = (max(z->hr, z->hl) + 1);
				
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
			}
			else if (f == 0)
			{
				z->hl = y->hr;
				y->hr = (max(z->hr, z->hl) + 1);
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
			}
			else if (f == 2)
			{
				y->hl = x->hr;
				z->hr = x->hl;
				x->hr = max(y->hr, y->hl) + 1;
				x->hl = max(z->hr, z->hl) + 1;
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
				y->hr = x->hl;
				z->hl = x->hr;
				x->hl = max(y->hr, y->hl) + 1;
				x->hr = max(z->hr, z->hl) + 1;
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
		return 1;
	  }
	  
	  int height(node* n)
	  {
		  if (n == NULL)
			  return 0;
		  return max(height(n->left), height(n->right)) + 1;
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
	  int delet(int k)
	  {
		  if (isnull())
			  return 0;
		  if (!search(k))
				  return 0;
		  node* temp = splay;
		  if (splay->left != NULL && splay->right != NULL)
		  {
			  node* del = maxi(splay->left);
			  splay->key = del->key;
			  if (del->parent == splay)
				  splay->hl--;
			  else
				  del->parent->hr--;
			
			  if (del->left != NULL)
			  {
				  del->key = del->left->key;
				  del->left = NULL; 
		      }
			  else
			  {
				  if (del->parent != splay)
					  del->parent->right = NULL;
				  else
					  del->parent->left = NULL;
				 
			  }
			   splay = del->parent;
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
			  {
				  splay->parent->right = NULL; splay->parent->hr = 0;
			  }
			  else
			  {
				  splay->parent->left = NULL; splay->parent->hl = 0;
			  }
			  splay = splay->parent;
		  }
		  else
		  {
			  if (splay->parent->key > splay->key)
				  splay->parent->hl--;
			  else
				  splay->parent->hr--;

			  if (splay->left != NULL)
			  {
				  splay->key = splay->left->key;
				  splay->left = NULL;
			  }
			  else
			  {
				  splay->key = splay->right->key;
				  splay->right = NULL;
              }
			  splay = splay->parent;
     	  }

		  rotate(splay,q.size()-2);
		  return 1;
	  }
	  void rotate(node* z,int i)
	  {
		  node *x, *y;
		  int f = 1;
		  while (f)
		  {
			  if (z->hl != z->hr || z == root)
				  f = 0;
			  else
			  {
				  z = z->parent;
				  if (q[i--] == 1)
					  z->hr--;
				  else
					  z->hl--;
			  }
		  }
		  if (abs(z->hl - z->hr) == 2)
		  {
			  if (z->hl > z->hr)
			  {
				  y = z->left;
				  if (y->hl >= y->hr)
				  {
					  x = y->left; f = 0;
				  }
				  else
				  {
					  x = y->right; f = 1;
				  }
			  }
			  else
			  {
				  y = z->right;
				  if (y->hr >= y->hl)
				  {
					  x = y->right; f = 3;
				  }
				  else
				  {
					  x = y->left; f = 2;
				  }
			  }
			  int h = max(z->hl, z->hr) + 1;
			  node* t = z->parent;
			  if (f == 0)
			  {
				  z->hl = y->hr;
				  y->hr = (max(z->hr, z->hl) + 1);
				  z->left = y->right;
				  if (z->left != NULL)
					  z->left->parent = z;
				  y->right = z;
				  z->parent = y;
				  y->parent = t;
				  if (t != NULL)
				  {
					  int san = h -(max(y->hr, y->hl) + 1);
					  if (t->key < y->key)
					  {
						  t->right = y;
						  t->hr = t->hr - san;
					  }
					  else
					  {
						  t->left = y;
						  t->hl = t->hl - san;
					  }
						  if (san)
						  rotate(t, i - 1);
				  }
				  else
					  root = y;
			    }
			  else if (f == 3)
			  {
				  z->hr = y->hl;
				  y->hl = (max(z->hr, z->hl) + 1);

				  z->right = y->left;
				  if (z->right != NULL)
					  z->right->parent = z;
				  y->left = z;
				  z->parent = y;
				  y->parent = t;
				  if (t != NULL)
				  {
					  int san = h - (max(y->hr, y->hl) + 1);
					  if (t->key < y->key)
					  {
						  t->right = y;
						  t->hr = t->hr - san;
					  }
					  else
					  {
						  t->left = y;
						  t->hl = t->hl - san;
					  }
					  if (san)
						  rotate(t, i - 1);
				  }
				  else
					  root = y;
			  }
			  else if (f == 1)
			  {
				  y->hr = x->hl;
				  z->hl = x->hr;
				  x->hl = max(y->hr, y->hl) + 1;
				  x->hr = max(z->hr, z->hl) + 1;
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
					  {
						  t->right = x;
						  t->hr--;
					  }
					  else
					  {
						  t->left = x;
						  t->hl--;
					  }
					  rotate(t, i - 1);
				  }
				  else
					  root = x;
			  }
			  else
			  {
				  y->hl = x->hr;
				  z->hr = x->hl;
				  x->hr = max(y->hr, y->hl) + 1;
				  x->hl = max(z->hr, z->hl) + 1;
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
					  {
						  t->right = x;
						  t->hr--;
					  }
					  else
					  {
						  t->left = x;
						  t->hl--;
					  }
					  rotate(t, i - 1);
				  }
				  else
					  root = x;
			  }
		  
		  }

		  return;
}
};
int main()
{
	int f = 1, c, t;
	tree tr;
	while (f)
	{
		cout << "enter  \n1 Insert\n2 search\n3 delete \n4 display\n:";
		tr.q.clear();
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
		else if (c == 4)
			tr.display();
		else
			f = 0;
		cout << "\n----------------------------------------------------------------\n";

	}

	return 0;
	
}