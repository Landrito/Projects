#include <cassert>
#include <stdio.h>

class stack
{
public:
	stack(int newSize = 10);
	void push(int newVal);
	int pop();
	bool full();
	bool empty();
	bool sanityChecker();

private:
	int * arr;
	int front;
	int back; //back will always point to the next available space, unless it is an empty stack;
	int size;
};


int main()
{
	stack myStack;
	for( int i = 0; i < 10; i++)
		myStack.push(i);

	assert(myStack.sanityChecker());

	for( int i = 0; i < 5; i++)
		printf("%d\n",myStack.pop());

	myStack.push(20);
	myStack.push(21);
	myStack.push(22);

	assert(myStack.sanityChecker());

	for( int i = 0; i < 8; i++)
		printf("%d\n",myStack.pop());

	return 0;

}

stack::stack(int newSize) : arr(new int[newSize]), front(-1), back(-1), size(newSize) {}

void stack::push(int newVal)
{
	assert( !full() );

	if( empty() )
	{
		arr[0] = newVal;
		front = 0;
		back = 1;
	}
	else
	{
		arr[back] = newVal;
		back = (back + 1) % size;

	}
}

int stack::pop()
{
	assert( !empty() );

	int returnVal = arr[front];

	//if the next spot the front will go to is the back, then the stack is now empty
	if ( (front + 1) % size == back )
	{
		front = -1;
		back = -1;
	}

	//else move the front up
	else
		front = (front + 1) % size;

	return returnVal;
}

bool stack::full() { return( (front != -1 && back != -1) && front == back); }

bool stack::empty() { return front == -1 && back == -1; }

bool stack::sanityChecker()
{
	if( front == -1 && back != -1)
		return false;

	if( back == -1 && front != -1)
		return false;

	return true;
}
