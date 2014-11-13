//COMMENTS

enum checkedArr{UNCHECKED, CHECKING, CHECKED};
const int NIL_PARENT;

struct node{
	int id;
	node(int i) : id(i) { }
};

struct ajacency{
	int connectedTo;
	int weight;
	adjacency(int to, int w) : connectedTo(to), weight(w) { }
};

struct adjLess{
	operator()(const adjacency & first, const adjacency & second){
		return first.weight < second.weight;
	}
};

class graph{
public:
	void insertNode(const node * newNode);
	void addConnection(int from, int to, int weight);
	const vector<node*> getNodes() const;
	const vector< vector<adjacency*> > getAdjList() const;

private:
	vector<node*> nodes;
	vector< vector<adjacency*> > adjList;
};

void graph::insertNode(const node * newNode);{
	nodes.push_back( new node(nodes.size()) )
}

void graph::addConnection(int from, int to, int weight){
	adjList[from].push_back( new adjacency(to, weight) );
}

const vector<node*> getNodes() const{
	return nodes;
}

const vector< vector<adjacency*> > getAdjList() const{
	return adjList;
}

vector<int> * getConnectedSubGraphSizes(const graph & mGraph){
	int size = mGraph.getNodes().size();
	vector<int> * checkedArr;
	vector<int> * parent;
	for(int i =0; i < size; i++){
		checkedArr->push_back(UNCHECKED);
		parent->push_back(NIL_PARENT);
	}

	vector<int> * returnVector;
	for(int i = 0, i < size; i++){
		if( (*checkedArr)[i] == UNCHECKED ){
			returnVector->push_back( depthFirstCount(i, mGraph, checkedArr, parent) );
		}
	}

	return returnVector;
}

int depthFirstCount(int nodeIndex, const graph & mGraph, vector<int> * checkedArr, vector<int> * parent){
	int count = 0;
	(*checkedArr)[i] = CHECKING;
	for(int i = 0, numAdjacencies = mGraph.getAdjList()[nodeIndex].size(); i < numAdjacencies; i++){
		int nodeConnection = mGraph.getAdjList()[nodeIndex][i]->connectedTo;
		if( checkedArr[nodeConnection] == UNCHECKED ){
			(*parent)[nodeConnection] = nodeIndex;
			count += depthFirstCount(nodeConnection, mGraphm checkedArr, parent);
		}
	}
	(*checkedArr)[i] = CHECKED;
	return count + 1;

}

void breadthFirstSearch(vector<node*> nodes, vector< vector<adjacency*> > adjList, int start){
	int size = nodes.size();
	vector<int> checkedArr;
	vector<int> parent;
	for(int i =0; i < size; i++){
		checkedArr.push_back(UNCHECKED);
		parent.push_back(NIL_PARENT);
	}
	queue<int> bfsQueue;
	bfsQueue.push(start);
	checkedArr[start] = GREY;
	while(!bfsQueue.empty()){
		for(int i = 0; i < adjList[bfsQueue.front()->id]->size; i++){
			if( checkedArr[adjList[bfsQueue.front()][i]->connectedTo] == UNCHECKED ){
				bfsQueue.push(adjList[bfsQueue.front()][i]->connectedTo)
				checkedArr[adjList[bfsQueue.front()][i]->connectedTo] = GREY;
				parent[adjList[bfsQueue.front()][i]->connectedTo] = bfsQueue.front();
			}
		}
		bfsQueue.pop();
	}
}




