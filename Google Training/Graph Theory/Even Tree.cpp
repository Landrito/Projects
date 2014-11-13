#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct edge{
	int vertA;
	int vertB;
};

int maxEdgesRemovedToKeepEven(const vector<edge> * edges);
bool bothSidesAreEven(edge checkEdge, const vector<edge> * edges);
vector<edge> * getEdges();

int main(){
	vector<edge> * edges = getEdges();
	cout << maxEdgesRemovedToKeepEven(edges);
	return 0;
}


int maxEdgesRemovedToKeepEven(const vector<edge> * edges){
	int numEdgesToBeRemoved = 0;
	for(vector<edge>::const_iterator vectorIter = edges->begin(), vectorIterEnd = edges->end(); vectorIter != vectorIterEnd; vectorIter++){
		if(bothSidesAreEven(*vectorIter, edges)){
			numEdgesToBeRemoved++;
		}
	}
	return numEdgesToBeRemoved;
}

bool bothSidesAreEven(edge checkEdge, const vector<edge> * edges){
	//You have the edge
	//now check and see if the sub-graph made by vertexA is even, If that subgraph is even, You know that you can remove that edge
	//The assumption is that for the ending property to hold true, the initial graph must be even. Thus if we have an even subtree,
	//the left over sub tree must be even as well.
	vector<int> subTree;
	subTree.push_back(checkEdge.vertA);

	vector<int> ignore;
	ignore.push_back(checkEdge.vertB);

	int subTreeCardinality = 1;
	for(int i = 0; i < subTree.size(); i++){
		for(int j = 0; j < edges->size(); j++){
			//This is the case where something is connecting to 
			if((*edges)[j].vertA == subTree[i] && find(ignore.begin(), ignore.end(), (*edges)[j].vertB) == ignore.end() ){
				subTree.push_back((*edges)[j].vertB);
				subTreeCardinality++;
			} else if((*edges)[j].vertB == subTree[i] && find(ignore.begin(), ignore.end(), (*edges)[j].vertA) == ignore.end()){
				subTree.push_back((*edges)[j].vertA);
				subTreeCardinality++;
			}
		}
		ignore.push_back(subTree[i]);
	}
	
	return (subTreeCardinality % 2) == 0;
}

vector<edge> * getEdges(){
	int numVertices = 0;
	int numEdges = 0;
	cin >> numVertices >> numEdges;

	vector<edge> * edges = new vector<edge>;
	for(int i = 0; i < numEdges; i++){
		int tempVertA = 0;
		int tempVertB = 0;
		cin >> tempVertA >> tempVertB;
		edge tempEdge = {tempVertA, tempVertB};
		edges->push_back(tempEdge);
	}

	return edges;
}