#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

struct adjacency{
	int connectedTo;
	int weight;
	adjacency(int c, int w) : connectedTo(c), weight(w) { }
};

struct node{
	vector<adjacency*> adjList;
};

struct adjCompare{
	bool operator()(const adjacency * left, const adjacency * right) { 
		return left->weight < right->weight; 
	}
};

struct graph{
	int roadInQuestionStart;
	int roadInQuestionEnd;
	vector<node*> vertexList;
};

graph * getGraph();
vector<int> * shortestDistances(const graph * testGraph, int vertex);
double calculateP(const vector<int> * distancesToA, const vector<int> * distancesToB);
void sanityCheck(const graph * testGraph);

int main(){
	int numTestCases = 0;
	cin >> numTestCases;
	for(int i = 0; i < numTestCases; i++){
		graph * mgraph;
		mgraph = getGraph();
		vector<int> * shortestToA = shortestDistances(mgraph, mgraph->roadInQuestionStart);
		vector<int> * shortestToB = shortestDistances(mgraph, mgraph->roadInQuestionEnd);
		cout << calculateP(shortestToA, shortestToB);
	}
}

graph * getGraph(){
	graph * returnGraph = new graph;
	int numVertices = 0;
	int numRoads = 0;
	int roadInQuestion;

	cin >> numVertices;
	cin >> numRoads;
	cin >> roadInQuestion;

	for(int i = 0; i < numVertices; i++){
		returnGraph->vertexList.push_back(new node);
	}

	for(int i = 0; i < numRoads; i++){
		adjCompare comparer;
		int roadStart = 0;
		int roadEnd = 0;
		int distance = 0;
		cin >> roadStart;
		cin >> roadEnd;
		cin >> distance;

		if(i + 1 == roadInQuestion){
			returnGraph->roadInQuestionStart = roadStart;
			returnGraph->roadInQuestionEnd = roadEnd;
		}

		returnGraph->vertexList[roadStart - 1]->adjList.push_back( new adjacency(roadEnd - 1,distance) );
		push_heap(returnGraph->vertexList[roadStart - 1]->adjList.begin(), returnGraph->vertexList[roadStart - 1]->adjList.end(), comparer);

		returnGraph->vertexList[roadEnd - 1]->adjList.push_back( new adjacency(roadStart - 1,distance) );
		push_heap(returnGraph->vertexList[roadEnd - 1]->adjList.begin(), returnGraph->vertexList[roadEnd - 1]->adjList.end(), comparer);
	}
	return returnGraph;
}

vector<int> * shortestDistances(const graph * testGraph, int vertex){
	int size = testGraph->vertexList.size();
	vector<int> * distArray = new vector<int>;
	vector<int> * parentArray = new vector<int>;
	vector<bool> * checkedArray = new vector<bool>;

	//initialize arrays
	for(int i = 0; i < size; i++){
		if( i == vertex ){
			distArray->push_back(0);
		} else {
			distArray->push_back(std::numeric_limits<int>::max());
		}
		parentArray->push_back(-1);
		checkedArray->push_back(false);	
	}

	//this will be the state that tells us which node we are currently checking;
	int currentNode = vertex;

	for(int i = 0; i < size; i++){ //loop through this array n times because dijkstras always will check every thing
		int nextVertex = -1;
		vector<adjacency*> tempAdjList = testGraph->vertexList[currentNode]->adjList;

		for(vector<adjacency*>::iterator iter = tempAdjList.begin(), end = tempAdjList.end(); iter != end; ++iter){
			if( (*distArray)[currentNode] + (*iter)->weight < (*distArray)[(*iter)->connectedTo] ){
				(*distArray)[(*iter)->connectedTo] = (*distArray)[currentNode] + (*iter)->weight;
			}
		}

		while(nextVertex == -1 && !tempAdjList.empty()){
			if( (*checkedArray)[tempAdjList.front()->connectedTo] == false ){
				nextVertex = tempAdjList.front()->connectedTo;
			} else {
				adjCompare comparer;
				pop_heap(tempAdjList.begin(), tempAdjList.end(), comparer);
			}
		}
		(*checkedArray)[currentNode] = true;
		currentNode = nextVertex;
	}
	return distArray;
}

double calculateP(const vector<int> * distancesToA, const vector<int> * distancesToB){
	int currentMax = 0;
	int indexOfMax = -1;
	for(int i = 0; i < distancesToA->size(); i++){
		if( (*distancesToA)[i] + (*distancesToB)[i] > currentMax ){
			currentMax = (*distancesToA)[i] + (*distancesToB)[i];
			indexOfMax = i;
		}
	}
	double displacementFromA = (currentMax / 2) - (*distancesToA)[indexOfMax];
	return displacementFromA;
}


