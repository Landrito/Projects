template <typename type>
class list
{
public:
	list();
	void add( const type & newVal );
	iterator begin() const;
	iterator end() const;
	class iterator
	{
		public:
		iterator();

		//Evan note: iterator’s constructor is public, not sure if thats right
		//I made this public because I wanted to be able to call the constructor from
		//within begin and end
		iterator( node * newNode ); 
		iterator operator++(int);
		bool operator!=( const iterator & other );
		type operator*();
		
		private:
		node * nodePtr;
	};
private:
	class node
	{
		node();
		node(const type & newValue, node * newNext);
		type getValue() const;

		private:
		type value;
		node * next;
	};
	node * head;
	node * tail;
};

template <typename type>
list<type>::list() : head( NULL ), tail( NULL ) {}

template <typename type>
void list<type>::add(  const type & newVal )
{
	//Empty list
	if( head == NULL )
	{
		head = tail = new node(newVal, NULL);
	}
	else
	{
		tail->next = new node(newVal, NULL);
		tail = tail->next;
	}
}

template <typename type>
iterator list<type>::begin() const
{
	return iterator( head );
}

template <typename type>
iterator list<type>::end() const
{
	return iterator( tail );
}

template <typename type>
list<type>::iterator::iterator() : nodePtr(NULL) {}

template <typename type>
list<type>::iterator::iterator( node * newNode ) : nodePtr( newNode ) {}

template <typename type>
iterator list<type>::iterator::operator++(int)
{
	nodePtr = nodePtr->next;
}

template <typename type>
bool list<type>::iterator::operator!=( const iterator & other )
{
	return this->nodePtr != other->nodePtr;
}

template <typename type>
type list<type>::iterator::operator*()
{
	return nodePtr->getValue();
}

//Evans Notes
//you actually need to use the initializer list in the node constructor, otherwise youll 
//accidentally call a default constructor then a copy
//right here I gut instincted a NULL and wanted to stray from leaving that field empty mostly
//because this value NEEEDS to be initialized.
template <typename type>
list<type>::node::node() : value( NULL ), next( NULL ) {}

template <typename type>
list<type>::node::node(const type & newValue, node * newNext) 
	: value(newValue), next(newNext) {}

template <typename type>
type list<type>::node::getValue() const
{
	return value;
}
