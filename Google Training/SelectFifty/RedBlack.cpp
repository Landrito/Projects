#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;

enum color {BLACK, RED};

template<typename type>
class rbTree
{
public:
	rbTree();
	rbTree(const rbTree<type> & src);
	~rbTree();
	rbTree<type>& operator=(const rbTree<type> & src);
	void insert(const type & newVal);
	void print() const;
	type max() const;
	vector<type> toVector() const;

private:
	class node
	{
	public:
		node();
		node( const type & newValue, 
			  node * newLeft, 
			  node * newRight, 
			  node * newParent, 
			  int newColor );
		~node();
		type * value;
		int color;
		node * left;
		node * right;
		node * parent;
		void destrHelper();
	};
	node * root;
	node * copyHelper( node * parent, const node * srcNode);
	void insertHelper(node * treeNode, const type & newVal);
	void reAdjust(node * treeNode);
	node * rightRotate(node * axis);
	node * leftRotate(node * axis);
	void printHelper(node * treeNode) const;
};



int main()
{

		rbTree<int> tree;
		srand(4);
		for(int i = 0; i < 100; i++)
		{
			int insert = rand() % 1000;
			std::cout << "Inserting: " << insert << endl;
			tree.insert(insert);
			std::cout << std::endl;
		}
		
		tree.print();

		rbTree<int> otherTree(tree);
		cout << endl << endl;

		otherTree.print();

}



template<typename type>
rbTree<type>::rbTree() : root(NULL)
{
	this->root = new node;
}

template<typename type>
rbTree<type>::rbTree(const rbTree<type> & src) : root(NULL)
{

	root = copyHelper(NULL, src.root);
}

template<typename type>
rbTree<type>& rbTree<type>::operator=(const rbTree<type> & src)
{
	if(this != &src)
	{
		if(root == NULL)
			delete root;
		root = copyHelper(NULL, src.root);
	}
}

template<typename type>
typename rbTree<type>::node * rbTree<type>::copyHelper( node * parent, const node * srcNode)
{
	node * treeNode = NULL;
	if(srcNode != NULL)
	{
		if(srcNode->value != NULL)
		{
			treeNode = new node(*(srcNode->value), copyHelper(treeNode, srcNode->left), copyHelper(treeNode, srcNode->right), treeNode, srcNode->color);
		}
		else
		{
			treeNode = new node;
		}
	}
	return treeNode;
}

template<typename type>
rbTree<type>::~rbTree()
{
	delete root;
	root = NULL;
}

template<typename type>
void rbTree<type>::insert(const type & newVal)
{
	insertHelper(root, newVal);
}

template<typename type>
void rbTree<type>::print() const
{
	printHelper(root);
}

template<typename type>
void rbTree<type>::insertHelper(node * treeNode, const type & newVal)
{
	if(treeNode->left != NULL && treeNode->right != NULL)
	{
		if(newVal <= *(treeNode->value))
			insertHelper(treeNode->left, newVal);
		else
			insertHelper(treeNode->right, newVal);
	}
	else
	{
		//Set the new node value because you are now at a leaf
		treeNode->value = new type(newVal);
		treeNode->color = RED;
		treeNode->left = new node;
		treeNode->right = new node;


		treeNode->left->parent = treeNode;
		treeNode->right->parent = treeNode;

		if(treeNode == root)
			treeNode->color = BLACK;

		reAdjust(treeNode);
	}
}

template<typename type>
void rbTree<type>::reAdjust(node * treeNode)
{
	//I am going to declare these pointers for readibility
	node * par = treeNode->parent;
	node * grandPar = NULL;
	node * greatGrandPar = NULL;
	bool grandParIsLeftChild = true;

	

	if( par != NULL )
		grandPar = treeNode->parent->parent;

	//this will be used to change the the 
	if(grandPar != NULL)
	{
		greatGrandPar = treeNode->parent->parent->parent;
		if(greatGrandPar != NULL)
			grandParIsLeftChild = greatGrandPar->left == grandPar;
	}

	//Check for the cases where the par or grandparent is null
	//If the parent's color is red then some sort of manipulation happens
	if( par != NULL && 
		grandPar != NULL &&
		par->color == RED &&
		treeNode->color ==RED )
	{

		//Now we know that the grandParent is black		
		//lets find the Uncle node!
		node * uncle = grandPar->left;
		if( grandPar->left == par )
			uncle = grandPar->right;
		
		//Case 1 the uncle is red	
		//if the uncle is red, then we must recolor and check
	
		if( uncle->color == RED )
		{
			uncle->color = BLACK;
			grandPar->color = RED;
			par->color = BLACK;

			//Must cover the trait that the root must be black
			if(grandPar == root)
				grandPar->color = BLACK;

			reAdjust(grandPar);
		}

		//Case 2 & 3 the uncle is Black
		else
		{
			bool nodeIsLeftChild = par->left == treeNode;
			bool parIsLeftChild = grandPar->left == par;

			//Case 2 rotate about parent
			if(nodeIsLeftChild != parIsLeftChild)
			{
				//Case 2a node is left and par is right: right rotate about par 
				if(nodeIsLeftChild && !parIsLeftChild)
					par = rightRotate(par);

				//Case 2b node is right and par is left: left rotate about par
				else
					par = leftRotate(par);

				//Now readjust nodes based on the parent
				if( parIsLeftChild )
					{
						grandPar->left = par;
						grandPar->left->parent = grandPar;
					}
				else
					{
						grandPar->right = par;
						grandPar->right->parent = grandPar;
					}

				reAdjust(par);
			}


			//Case 3 rotate about grandparent
			else
			{

				//recolor the parents
				grandPar->color = RED;
				par->color = BLACK;

				//Case 3a both are left: right rotate about grandparent
				if(nodeIsLeftChild && parIsLeftChild)
					grandPar = rightRotate(grandPar);

				//case 3b both are right: left rotate about grandparent
				else
					grandPar = leftRotate(grandPar);



				//change the great grand parents pointing
				if( greatGrandPar != NULL )
				{
					if( grandParIsLeftChild )
					{
						greatGrandPar->left = grandPar;
						greatGrandPar->left->parent = greatGrandPar;
					}
					else
					{
						greatGrandPar->right = grandPar; 
						greatGrandPar->right->parent = greatGrandPar;
					}
				}

				//change the root if the grand par is null
				else
				{
					root = grandPar;
					root->parent = NULL;
					grandPar->color = BLACK;
				}

				//now readjust based on the grandParent
				reAdjust(grandPar);
			}
		}
	}		
}

template<typename type>
typename rbTree<type>::node * rbTree<type>::leftRotate(node * axis)
{
	//declare a temp value to store the address of axis while you rotate
	node * temp = axis;
	axis = axis->right;

	temp->right = axis->left;
	temp->right->parent = temp;

	axis->left = temp;
	axis->left->parent = axis;

	return axis;
}

template<typename type>
typename rbTree<type>::node * rbTree<type>::rightRotate(node * axis)
{
	//declare a temp value to store the address of axis while you rotate
	node * temp = axis;
	axis = axis->left;

	temp->left = axis->right;
	temp->left->parent = temp;

	axis->right = temp;
	axis->right->parent = axis;

	return axis;
}

template<typename type>
void rbTree<type>::printHelper(node * treeNode) const
{
	//If you are not at a leaf, print the node.
	if(treeNode->left != NULL || treeNode ->right != NULL)
	{
		cout << *(treeNode->value);
		if(treeNode->color == BLACK)
			cout << "(b) ";
		else
			cout << "(r) ";
		printHelper(treeNode->left);
		printHelper(treeNode->right);
	}
	
}

template<typename type>
rbTree<type>::node::node()
	: value(NULL), left(NULL), right(NULL), parent(NULL), color(BLACK) {}


template<typename type>
rbTree<type>::node::node( const type & newValue, node * newLeft, node * newRight, node * newParent, int newColor )
	: value( new type(newValue)), left(newLeft), right(newRight), parent(newParent), color(newColor) {}


template<typename type>
rbTree<type>::node::~node()
{
	destrHelper();
}

template<typename type>
void rbTree<type>::node::destrHelper()
{
	if(left != NULL)
	{
		delete left;
		left = NULL;
	}
	if(right != NULL)
	{
		delete right;
		right = NULL;
	}
}

template<typename type>
type rbTree<type>::max() const
{
	node tempNode = root;
	assert(root != NULL);
	while(tempNode->left != NULL || tempNode ->right != NULL){
		tempNode = tempNode->right;
	}
	return tempNode->value;
}

template<typename type>
vector<type> toVector() const{
	vector<type> returnVector;
	toVectorHelper(root);
	return returnVector;
}

template<typename type>
void toVectorHelper(vector<type> & returnVector, node * treeNode) const{
	if(treeNode->left != NULL || treeNode ->right != NULL)
	{
		toVectorHelper(returnVector, treeNode->left);
		returnVector.push_back(treeNode->value);
		toVectorHelper(returnVector, treeNode->right);
	}
}




