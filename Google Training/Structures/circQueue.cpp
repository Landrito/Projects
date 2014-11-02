#include <cassert>
#include <stdio.h>

class queue
{
public:
	queue(int newSize = 10);
	void push(int newVal);
	int pop();
	bool full();
	bool empty();
	bool sanityChecker();

private:
	int * arr;
	int front;
	int back; //back will always point to the next available space, unless it is an empty queue;
	int size;
};


int main()
{
	queue myqueue;
	for( int i = 0; i < 10; i++)
		myqueue.push(i);

	assert(myqueue.sanityChecker());

	for( int i = 0; i < 5; i++)
		printf("%d\n",myqueue.pop());

	myqueue.push(20);
	myqueue.push(21);
	myqueue.push(22);

	assert(myqueue.sanityChecker());

	for( int i = 0; i < 8; i++)
		printf("%d\n",myqueue.pop());

	return 0;

}

queue::queue(int newSize) : arr(new int[newSize]), front(-1), back(-1), size(newSize) {}

void queue::push(int newVal)
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

int queue::pop()
{
	assert( !empty() );

	int returnVal = arr[front];

	//if the next spot the front will go to is the back, then the queue is now empty
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

bool queue::full() { return( (front != -1 && back != -1) && front == back); }

bool queue::empty() { return front == -1 && back == -1; }

bool queue::sanityChecker()
{
	if( front == -1 && back != -1)
		return false;

	if( back == -1 && front != -1)
		return false;

	return true;
}
