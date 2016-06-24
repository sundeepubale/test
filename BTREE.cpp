#include<iostream>
#include<cstdlib>
#include<vector>
using namespace std;
class node
{
public:
	vector<int> e;
	vector< node * > l;
	node * parent;
	int no;
	node()
	{
		parent = NULL;
		no = -1;
	    
	}
};
class tree
{
public:
	node *root,*splay;
	int m,isplay,d;
	
	tree(int o) :m(o), root(NULL),splay(NULL),isplay(-1)
	{
	 d = m / 2 + m % 2;
	}

    int isnull()
	{
		return root == NULL;
	}
	
	int search(int k)
	{
		if (isnull())
			return 0;
		node* t = root;
		int i, j;
		while (t != NULL)
		{
			splay = t;
			for (j = 0;j<t->e.size()&& t->e[j] <= k; j++)
				if (t->e[j] == k)
				{
				  isplay = j;
				  return 1;
				}
				  t = t->l[j];
			isplay = j;
		}
		return 0;
	}
	void maxi(node* t)
	{
		splay = t;
		t = t->l[t->l.size() - 1];
		while (t != NULL)
		{
			isplay = -1;
			splay = t;
			t = t->l[t->l.size() - 1];
        }
		return;
	}
	int delet(int k)
	{
		if (isnull())
			return 0;
		if (!search(k))
			return 0;
		int splt = isplay;
		node* temp = splay;
		if (temp->l[0] != NULL)
		{
			maxi(temp->l[isplay]);
			k=temp->e[splt] = splay->e[splay->e.size() - 1];
			if (isplay == -1)
				isplay = splay->parent->l.size() - 1;
			splay->e.pop_back();
			splay->l.pop_back();
		}
		else
		{
			splay->e.erase(splay->e.begin() + isplay);
			splay->l.pop_back();
		}
		if (splay->l.size() < d)
			transfer(k);
		return 1;
	}
	void transfer(int k)
	{
		int i;
		if (splay == root)
		{
			if (splay->l.size() < 2)
			{
				root = splay->l[0];
				root->parent = NULL;
			}
			return;
		}
		for (i = 0; i<splay->parent->e.size()&&splay->parent->e[i] < k; i++);
		  isplay = i;
		if (isplay && (splay->parent->l[isplay-1]->l.size() > d))
		{
			splay->e.insert(splay->e.begin(), splay->parent->e[isplay - 1]);
			splay->parent->e[isplay - 1] = splay->parent->l[isplay - 1]->e[splay->parent->l[isplay - 1]->e.size() - 1];
			splay->l.insert(splay->l.begin(), splay->parent->l[isplay - 1]->l[splay->parent->l[isplay - 1]->l.size() - 1]);
			splay->parent->l[isplay - 1]->l.pop_back();
			splay->parent->l[isplay - 1]->e.pop_back();
        }
		else if (isplay<splay->parent->l.size()-1 && (splay->parent->l[isplay + 1]->l.size()>d))
		{
			splay->e.push_back(splay->parent->e[isplay]);
			splay->parent->e[isplay] = splay->parent->l[isplay + 1]->e[0];
			splay->l.push_back(splay->parent->l[isplay + 1]->l[0]);
			splay->parent->l[isplay + 1]->l.erase(splay->parent->l[isplay + 1]->l.begin());
			splay->parent->l[isplay + 1]->e.erase(splay->parent->l[isplay + 1]->e.begin());
		}
		else
			merge(k);
		return;
	}
	void merge(int k)
	{
		if (isplay)
		{
			node* t = splay->parent->l[isplay - 1];
			t->e.push_back(t->parent->e[isplay - 1]);
			t->parent->e.erase(t->parent->e.begin() + isplay - 1);
			t->parent->l.erase(t->parent->l.begin() + isplay);
			t->e.insert(t->e.end(),splay->e.begin(),splay->e.end());
     		t->l.insert(t->l.end(),splay->l.begin(),splay->l.end());
			for (int i = 0; i < splay->l.size(); i++)
				if (splay->l[i] != NULL)
					splay->l[i]->parent = t;
			splay = t->parent;
		}
		else
		{
			node* t = splay->parent->l[1];
			splay->e.push_back(t->parent->e[0]);
			splay->parent->e.erase(splay->parent->e.begin());
			splay->parent->l.erase(splay->parent->l.begin()+1);
			splay->e.insert(splay->e.end(), t->e.begin(), t->e.end());
			splay->l.insert(splay->l.end(), t->l.begin(), t->l.end());
			for (int i = 0; i < t->l.size(); i++)
				if (t->l[i] != NULL)
					t->l[i]->parent = splay;
			splay = splay->parent;
		}
		if (splay->l.size() < d)
			transfer(k);
		return;
	}
	int insert(int k)
	{
		if (isnull())
		{
			root = new node();
			root->e.push_back(k);
			root->l.push_back(NULL);
			root->l.push_back(NULL);
			return 1;
		}
		if (search(k))
			return 0;
		splay->e.insert(splay->e.begin() + isplay, k);
		splay->l.push_back(NULL);
		if (splay->e.size() == m)
			split();
	 return 1;
	}
	int height(node* n)
	{
		if (n == NULL)
			return 0;
		return (height(n->l[n->l.size()-1]) + 1);
	}
	void split()
	{
		int k;
		vector<int> v;
		int i;
       
		k = splay->e[d-1];
		node* t = new node();
		vector<int> tmp(splay->e.begin()+d,splay->e.end());
		vector<node *> ltmp(splay->l.begin() + d, splay->l.end());
		t->e = tmp;
		t->l = ltmp;
		for (i = d; i <= m; i++)
			if (splay->l[i] != NULL)
				splay->l[i]->parent = t;
	    splay->e.erase(splay->e.begin()+d-1,splay->e.end());
		splay->l.erase(splay->l.begin() + d, splay->l.end());
	     t->parent = splay->parent;
		if (splay->parent != NULL)
		{
			v= splay->parent->e;
			for (i = 0; i < v.size() && k > v[i]; i++);
			splay = splay->parent;
			splay->e.insert(splay->e.begin() + i, k);
			splay->l.insert(splay->l.begin() + i+1, t);
			if (splay->e.size() == m)
				split();
			return;
		}
		root = new node();
		root->e.push_back(k);
		root->l.push_back(splay);
		root->l.push_back(t);
		root->parent = NULL;
		splay->parent = root;
		t->parent = root;
		return;
	}
	
	void display()
	{
		if (root == NULL)
			return;
		cout << "----------------------------------------------\n";
		int h = height(root);
		int num = (pow(m,h) - 1)/(m-1);
		node* *ptr = new node*[num];
		int* f = new int[num];
		int i, j, k,z;
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
				for ( z = 0; z < ptr[i]->l.size(); z++)
				{
					ptr[k] = ptr[i]->l[z];
					f[k++] = 1;
                }
				k += m - z;
			}
			else
				k += m;
		}
		int an, bn,b1=1,a1=0,c,i1;
		k = 3 * m - 2;
		an = (b1 + k)*(pow(m, h - 1) - 1) / 2;
		bn = pow(m, h - 1) *(b1 + k) - k;
		for (i = 1, c = 0; i <= h; i++)
		{
			for (j = 0; j < an; j++)
				cout << " ";
			for (j = 1; j <= pow(m,i-1);  c++)
			{
				if (f[c])
				{
					cout << "|";
					for ( i1 = 0; i1 < ptr[c]->e.size(); i1++)
					{
						if (ptr[c]->e[i1] < 10)
								cout << " ";
							cout << ptr[c]->e[i1];
						cout << "|";
					}
					for (z = 0; z < k - (3 * i1 + 1); z++)
						cout << " ";
				}
				else
				{
					for (z = 0; z < k; z++)
						cout << " ";
				}
				if (++j <= pow(m, i - 1))
				 for (z = 0; z < bn; z++)
					cout << " ";
			}
				an = ((2 * an - (m - 1)*(bn + k)/m))/2;
				bn = (bn - k*(m - 1)) / m;
				cout << endl; cout << endl;
		}
	}
};
int main()
{
	int f = 1, c, t;
	
	int ord;
	cout << "enter the order of B tree\n";
	cin >> ord;
	tree tr(ord);
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
		else if (c == 4)
			tr.display();
		else
			f = 0;
		cout << "\n----------------------------------------------------------------\n";

	}

	return 0;
}