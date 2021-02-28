#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <typename T>
class NodeT
{
public:
	T data;
	NodeT<T>* left;
	NodeT<T>* right;
	NodeT<T>* parent;
	bool isBlack;
	NodeT(T val)
	{
		data=val;
		left=NULL;
		right=NULL;
		parent=NULL;
		isBlack=false;
	}
	NodeT()
	{
		left=NULL;
		right=NULL;
		parent=NULL;
		isBlack=false;
	}
};

template <typename T>
class RedBlackTree
{
public:
	//Default Constructor
	//Pre:
	//Post:creates an empty tree whose root is a null pointer
	//PARAM:
	RedBlackTree();
	//Search key
	//Pre: single parametre
	//Post:searches the tree for the method's single parameter and returns true if it is found and false otherwise
	//PARAM: 
	bool search(T val); 
	//Search key range
	//Pre: 
	//Post:returns a vector that contains all of the values between the method's first and second parameters (including both parameter values if they are in the tree)
	//PARAM: Low bound, high bound
	vector<T> search(T low, T high);
	//inserts
	//Pre: only one parametre
	//Post: if the tree does not contain the method's single parameter, inserts the parameter and returns true;
	//PARAM: preferably not string
	bool insert(T val);
	//Root func
	//Pre: N/A
	//Post: Returns root
	//PARAM: N/A
	NodeT<T>* getRoot();
	//Size func
	//Pre: N/A
	//Post: returns size
	//PARAM: N/A
	T size();
	//DUMP func
	//Pre: myst be BST
	//Post:returns a vector that contains all of the values in the tree; the contents of the vector are in ascending order
	//PARAM:N/A
	vector <T> dump();
	//Copy Constructor
	//Pre:
	//Post:a constructor that creates a deep copy of its RedBlackTree reference parameter
	//PARAM:
	RedBlackTree(const RedBlackTree<T>& temp);
	//assignment operator
	//Pre: ONly RB BST to RB BST
	//Post:overloads the assignment operator for RedBlackTree objects – (deep) copies its RedBlackTree reference parameter into the calling object
	//PARAM: RB BST
	RedBlackTree<T> &operator=(const RedBlackTree<T>& temp);
	//Destructor
	//Pre: N/A
	//Post:deletes dynamic memory allocated by the tree
	//PARAM: N/A
	~ RedBlackTree();
	//Remove func
	//Pre:n/a
	//Post:removes the method's parameter from the tree and returns true; if the tree does not contain the parameter returns false
	//PARAM: 
	bool remove(const T &data);

private:
	//Pre:
	//Post:fixes Tree structure by rotating nodes to left
	//PARAM:
	void leftRotate(NodeT<T>* temp);
	//Pre:
	//Post:fixes Tree structure by rotating nodes to right
	//PARAM:
	void rightRotate(NodeT<T>* temp); 
	//Pre:
	//Post: Prints in ascending order
	//PARAM:
	void inOrder(NodeT<T>* temp, vector <T> &arr);
	//Pre:
	//Post:Prints in from top of tree and spans from left subtree to right
	//PARAM:
	void preOrder(NodeT<T>* temp,vector <T> &arr);
	//Pre:
	//Post: returns color of nodes
	//PARAM:
	bool color(NodeT<T>* temp);
	//Pre:
	//Post: helper function for search
	//PARAM:
	bool searchHelper(T target, NodeT<T>* temp);
	//Pre:
	//Post: helper function for removal
	//PARAM:
	NodeT<T>* removeHelper(NodeT<T>* node, const T &data);
	//Pre:
	//Post: helper fucntion for destructor
	//PARAM:
	void discard(NodeT<T>* temp);
	NodeT<T>* root;
	int cap;
	NodeT<T>* iter;

};

//Default Constructor
//Pre:
//Post:creates an empty tree whose root is a null pointer
//PARAM:
template <typename T>
RedBlackTree<T>:: RedBlackTree()
{
	root=NULL;
	cap=0;
}
//Pre:
//Post: helper function for search
//PARAM:
template <typename T>
bool RedBlackTree<T>:: searchHelper(T target, NodeT<T>* temp)
{
	if(temp==NULL)
		return false;
	else if(target==temp->data)
		return true;
	else if(target<temp->data)
		searchHelper(target, temp->left);
	else if(target>temp->data)
		searchHelper(target, temp->right);
}
//Search key
//Pre: single parametre
//Post:searches the tree for the method's single parameter and returns true if it is found and false otherwise
//PARAM: 
template <typename T>
bool RedBlackTree<T>::search(T val)
{
	return searchHelper(val, root);
}
//Pre:
//Post: returns color of nodes
//PARAM:
template <typename T>
bool RedBlackTree<T>::color(NodeT<T>* temp)
{
	if(temp==NULL)
		return 1;
	return temp->isBlack;
}

//Pre:
//Post:fixes Tree structure by rotating nodes to left
//PARAM:
template <typename T>
void RedBlackTree<T>:: leftRotate(NodeT<T>* temp)
{
	NodeT<T>* hold;
	hold = temp->right;
	temp->right = hold->left;
	if ( hold->left != NULL )
		hold->left->parent = temp;
	hold->parent = temp->parent;
	if ( temp->parent == NULL )
		root = hold;
	else
	{
		if ( temp == (temp->parent)->left )
			temp->parent->left = hold;
		else
			temp->parent->right = hold;
	}
	hold->left = temp;
	temp->parent = hold;
}
//Pre:
//Post:fixes Tree structure by rotating nodes to right
//PARAM:
template <typename T>
void RedBlackTree<T>:: rightRotate(NodeT<T>* temp)
{
	NodeT<T>* hold;
	hold = temp->left;
	temp->left = hold->right;
	if ( hold->right != NULL )
		hold->right->parent = temp;
	hold->parent = temp->parent;
	if ( temp->parent == NULL )
		root = hold;
	else
	{
		if ( temp == (temp->parent)->right )
			temp->parent->right = hold;
		else
			temp->parent->left = hold;
	}
	hold->right = temp;
	temp->parent = hold;
}


//inserts
//Pre: only one parametre
//Post: if the tree does not contain the method's single parameter, inserts the parameter and returns true;
//PARAM: preferably not string
template <typename T>
bool RedBlackTree<T>::insert(T val)
{
	if(root==NULL)
	{
		root=new NodeT<T>(val);
		root->isBlack=true;
		cap++;
		return 1;
	}
	NodeT<T>*temp=root;
	NodeT<T>* iter;
	T count=0;

	if(search(val)==1)
		return 0;
	while(true)
	{
		if(val<temp->data && temp->left!=NULL)
		{
			temp=temp->left;
			continue;
		}
		else if(val>temp->data && temp->right!=NULL)
		{
			temp=temp->right;
			continue;
		}
		else if(val>temp->data && temp->right==NULL)
		{
			iter=new NodeT<T>(val);
			temp->right=iter;
			iter->parent=temp;
			temp=root;
			cap++;
			break;
		}
		else if(val<temp->data && temp->left==NULL)
		{
			iter=new NodeT<T>(val);
			temp->left=iter;
			iter->parent=temp;
			temp=root;
			cap++;
			break;
		}
	}

	while(iter!=root && iter->parent->isBlack==false){
		if(iter->parent==iter->parent->parent->left){
			NodeT<T>* uncle= iter->parent->parent->right;
			if(color(uncle)==false){
				iter->parent->isBlack=true;
				uncle->isBlack=true;
				iter->parent->parent->isBlack=false;
				iter=iter->parent->parent;
			}
			else{
				if(iter==iter->parent->right){
					iter=iter->parent;
					leftRotate(iter);
				}
				iter->parent->isBlack=true;
				iter->parent->parent->isBlack=false;
				rightRotate(iter->parent->parent);
			}
		}
		else{
			if(iter->parent==iter->parent->parent->right){
				NodeT<T>* uncle= iter->parent->parent->left;
				if(color(uncle)==false){
					iter->parent->isBlack=true;
					uncle->isBlack=true;
					iter->parent->parent->isBlack=false;
					iter=iter->parent->parent;
				}


				else{
					if(iter==iter->parent->left){
						iter=iter->parent;
						rightRotate(iter);
					}
					iter->parent->isBlack=true;
					iter->parent->parent->isBlack=false;
					leftRotate(iter->parent->parent);

				}
			}

		}
	}
	root->isBlack=true;
	return 1;
}
//Size func
//Pre: N/A
//Post: returns size
//PARAM: N/A
template <typename T>
T RedBlackTree<T>:: size()
{
	return cap;
}
//Root func
//Pre: N/A
//Post: Returns root
//PARAM: N/A
template <typename T>
NodeT<T>* RedBlackTree<T>:: getRoot()
{
	return root;
}
//Copy Constructor
//Pre:
//Post:a constructor that creates a deep copy of its RedBlackTree reference parameter
//PARAM:
template <typename T>
RedBlackTree<T> ::RedBlackTree(const RedBlackTree<T>& temp)
{
	root=NULL;
	cap=0;
	vector<T>arr;
	preOrder(temp.root,arr);
	for(int i=0;i<arr.size();i++)
		insert(arr[i]);
}
//Pre:
//Post: Prints in ascending order
//PARAM:
template <typename T>
void RedBlackTree<T>:: inOrder(NodeT<T>* temp,vector <T> &arr)
{
	if(temp==NULL)
		return;
	inOrder(temp->left,arr);
	arr.push_back(temp->data);
	inOrder(temp->right,arr);
}
//Pre:
//Post:Prints in from top of tree and spans from left subtree to right
//PARAM:
template <typename T>
void RedBlackTree<T>:: preOrder(NodeT<T>* temp,vector <T> &arr)
{
	if(temp==NULL)
		return;
	arr.push_back(temp->data);

	preOrder(temp->left,arr);

	preOrder(temp->right,arr);


}
//DUMP func
//Pre: myst be BST
//Post:returns a vector that contains all of the values in the tree; the contents of the vector are in ascending order
//PARAM:N/A
template <typename T>
vector <T> RedBlackTree<T>::dump()
{
	vector<T> arr;
	inOrder(root,arr);
	return arr;
}
//Search key range
//Pre: 
//Post:returns a vector that contains all of the values between the method's first and second parameters (including both parameter values if they are in the tree)
//PARAM: Low bound, high bound
template <typename T>
vector<T> RedBlackTree<T>::search(T low, T high)
{
	vector<T>arr;
	vector<T>arr2;
	inOrder(root,arr);
	for(int i=0;i<arr.size();i++)
	{
		if(arr[i]>=low && arr[i]<= high)
			arr2.push_back(arr[i]);
	}
	return arr2;
}
//assignment operator
//Pre: ONly RB BST to RB BST
//Post:overloads the assignment operator for RedBlackTree objects – (deep) copies its RedBlackTree reference parameter into the calling object
//PARAM: RB BST
template <typename T>
RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree<T>& temp)
{	
	if(this==&temp)
		return *this;
	if(this->root!=NULL)
		delete [] this;
	vector<T>arr;
	preOrder(temp.root,arr);
	for(int i=0;i<arr.size();i++)
		insert(arr[i]);
	return *this;
}
template <typename T>
RedBlackTree<T>::~ RedBlackTree()
{
	discard(root);
}
//Pre:
//Post: helper fucntion for destructor
//PARAM:
template <typename T>
void RedBlackTree<T>::discard(NodeT<T>* temp)
{
	if(temp == NULL)
		return;
	discard(temp->left);
	discard(temp->right);
	delete temp;
}
//Pre:
//Post: helper function for removal
//PARAM:
template <typename T>
NodeT<T>* RedBlackTree<T>::removeHelper(NodeT<T>* temp, const T &data)
{
	if (temp == nullptr)
	{
		return nullptr;
	}
	else if (data < temp->data)
	{
		temp->left = removeHelper(temp->left, data);
		return temp;
	}
	else if (data == temp->data)
	{
		if (temp->left == nullptr && temp->right == nullptr)
		{
			delete temp;
			return nullptr;
		}
		else if (temp->left == nullptr)
		{
			NodeT<T>* itr = temp->right;
			delete temp;
			return itr;
		}
		else if (temp->right == nullptr)
		{
			NodeT<T>* itr = temp->left;
			delete temp;
			return itr;
		}
		else
		{
			NodeT<T>* Z = temp->right;
			while (Z->left != nullptr)
			{
				Z = Z->left;
			}
			temp->data = Z->data;
			temp->right = removeHelper(temp->right, Z->data);
			return temp;
		}
	}
	else
	{
		temp->right = removeHelper(temp->right, data);
		return temp;
	}
}

//Remove func
//Pre:n/a
//Post:removes the method's parameter from the tree and returns true; if the tree does not contain the parameter returns false
//PARAM: 
template <typename T>
bool RedBlackTree<T>::remove(const T &data)
{
	if (!search(data))
	{
		return false;
	}
	root = removeHelper(root, data);
	cap --;
	return true;
}