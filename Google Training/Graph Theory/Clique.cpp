#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

struct GraphRep{
	int numNodes;
	int numEdges;
};

int minimumMaxCliqueSize(int numNodes, int numEdges);
vector<GraphRep> * getGraphRepresentations( int & numGraphs );

int main(){
	int numGraphs = 0;
	vector<GraphRep> * graphs = getGraphRepresentations( numGraphs );
	for( int i = 0; i < numGraphs; i++){
		cout << minimumMaxCliqueSize( (*graphs)[i].numNodes, (*graphs)[i].numEdges );
	}

}

int minimumMaxCliqueSize(int numNodes, int numEdges){
	int maxNumEdges = numNodes*(numNodes - 1) / 2;
	if(maxNumEdges - numEdges >= numNodes){
		return (int) ( ceil( (double) numEdges / (double) numNodes ) ) + 1;
	}
	else{
		int potentialReturn = numNodes - (maxNumEdges - numEdges);
		if(potentialReturn > numNodes/2){
			return potentialReturn;
		} else {
			return (int)( ceil( (double)numNodes / 2.0) );
		}
	}
}

vector<GraphRep> * getGraphRepresentations( int & numGraphs ){
	vector<GraphRep> * returnVector = new vector<GraphRep>;
	int numCases = 0;
	cin >> numCases;

	for( int i = 0; i < numCases; i++ ){
		int numNodes = 0;
		int numEdges = 0;

		cin >> numNodes >> numEdges;
		returnVector->push_back((GraphRep){numNodes, numEdges});
	}
	return returnVector;
}