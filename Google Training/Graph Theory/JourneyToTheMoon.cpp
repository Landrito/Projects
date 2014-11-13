#include <vector>
#include <iostream>
using namespace std;

enum checkedStatus{UNCHECKED, CHECKING, CHECKED};

struct node{
	int id;
	node(int i) : id(i) { }
};

struct adjacency{
	int connectedTo;
	adjacency(int to) : connectedTo(to) { }
};

class graph{
public:
	graph(int s);
	int getSize() const;
	void addConnection(int from, int to);
	const vector<adjacency*> * getAdjList() const;

private:
	int size;
	vector<adjacency*> * adjList;
};

vector<int> * getConnectedSubGraphSizes(const graph & mGraph);
int depthFirstCount(int nodeIndex, const graph & mGraph, int * checkedArr);

int main(){
	int numNodes = 0;
	int numAdjacencies = 0;
	cin >> numNodes >> numAdjacencies;
	graph mGraph(numNodes);
	for(int i = 0; i < numAdjacencies; i++){
		int from = 0;
		int to = 0;
		cin >> from >> to;
		mGraph.addConnection(from, to);
		mGraph.addConnection(to, from);
	}
	vector<int> * connectedSubGraphSizes = getConnectedSubGraphSizes(mGraph);

	int numCombinations = 0;
	for(int i = 0, size = connectedSubGraphSizes->size(); i < size; i++){
		numCombinations += (*connectedSubGraphSizes)[i] * (numNodes - (*connectedSubGraphSizes)[i]);
	}
	numCombinations /= 2;

	cout << numCombinations;

}

graph::graph(int size) {
	adjList = new vector<adjacency*>[size];
}

vector<int> * getConnectedSubGraphSizes(const graph & mGraph){
    
	int size = m#include <vector>
#include <iostream>
using namespace std;

enum checkedStatus{UNCHECKED, CHECKING, CHECKED};

struct node{
	int id;
	node(int i) : id(i) { }
};

struct adjacency{
	int connectedTo;
	adjacency(int to) : connectedTo(to) { }
};

class graph{
public:
	graph(int s);
	int getSize() const;
	void addConnection(int from, int to);
	const vector<adjacency*> * getAdjList() const;

private:
	int size;
	vector<adjacency*> * adjList;
};

vector<int> * getConnectedSubGraphSizes(const graph & mGraph);
int depthFirstCount(int nodeIndex, const graph & mGraph, int * checkedArr);

int main(){
	int numNodes = 0;
	int numAdjacencies = 0;
	cin >> numNodes >> numAdjacencies;
	graph mGraph(numNodes);
	for(int i = 0; i < numAdjacencies; i++){
		int from = 0;
		int to = 0;
		cin >> from >> to;
		mGraph.addConnection(from, to);
		mGraph.addConnection(to, from);
	}
	vector<int> * connectedSubGraphSizes = getConnectedSubGraphSizes(mGraph);

	long long numCombinations = 0;
	for(int i = 0, size = connectedSubGraphSizes->size(); i < size; i++){
		numCombinations += (*connectedSubGraphSizes)[i] * (numNodes - (*connectedSubGraphSizes)[i]);
	}
	numCombinations /= 2;

	cout << numCombinations;

}

graph::graph(int s) : size(s) {
	adjList = new vector<adjacency*>[s];
}

vector<int> * getConnectedSubGraphSizes(const graph & mGraph){
	int size = mGraph.getSize();
	int * checkedArr = new int[size];
	for(int i = 0; i < size; i++){
		checkedArr[i] = UNCHECKED;
    }

	vector<int> * returnVector = new vector<int>;
	for(int i = 0; i < size; i++){
		if( checkedArr[i] == UNCHECKED ){
			returnVector->push_back( depthFirstCount(i, mGraph, checkedArr) );
		}
	}

	return returnVector;
}

int depthFirstCount(int nodeIndex, const graph & mGraph, int * checkedArr){
	int count = 0;
	checkedArr[nodeIndex] = CHECKING;
    
	for(int i = 0, numAdjacencies = mGraph.getAdjList()[nodeIndex].size(); i < numAdjacencies; i++){
		int nodeConnection = mGraph.getAdjList()[nodeIndex][i]->connectedTo;
		if( checkedArr[nodeConnection] == UNCHECKED ){
			count += depthFirstCount(nodeConnection, mGraph, checkedArr);
		}
	}
	checkedArr[nodeIndex] = CHECKED;
	return count + 1;

}

void graph::addConnection(int from, int to){
	adjList[from].push_back( new adjacency(to) );
}

int graph::getSize() const{
	return size;
}

const vector<adjacency*> * graph::getAdjList() const{
	return adjList;
}Graph.getSize();
	int * checkedArr = new int[size];
	for(int i = 0; i < size; i++){
		checkedArr[i] = UNCHECKED;
    }

	vector<int> * returnVector;
	for(int i = 0; i < size; i++){
		if( checkedArr[i] == UNCHECKED ){
			returnVector->push_back( depthFirstCount(i, mGraph, checkedArr) );
		}
	}

	return returnVector;
}

int depthFirstCount(int nodeIndex, const graph & mGraph, int * checkedArr){
    cout << nodeIndex << endl;
	int count = 0;
	checkedArr[nodeIndex] = CHECKING;
    
	for(int i = 0, numAdjacencies = mGraph.getAdjList()[nodeIndex].size(); i < numAdjacencies; i++){
		int nodeConnection = mGraph.getAdjList()[nodeIndex][i]->connectedTo;
		if( checkedArr[nodeConnection] == UNCHECKED ){
			count += depthFirstCount(nodeConnection, mGraph, checkedArr);
		}
	}
	checkedArr[nodeIndex] = CHECKED;
	return count + 1;

}

void graph::addConnection(int from, int to){
	adjList[from].push_back( new adjacency(to) );
}

int graph::getSize() const{
	return size;
}

const vector<adjacency*> * graph::getAdjList() const{
	return adjList;
}