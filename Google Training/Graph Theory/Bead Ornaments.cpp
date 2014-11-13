#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

long long numCombinations(const vector<int> & beadCounts);

int main(){
	int numTestCases = 0;
	cin >> numTestCases;
	for(int i = 0; i < numTestCases; i++){
		int numColors = 0;
		cin >> numColors;
		vector<int> beadCounts;
		for(int i = 0; i < numColors; i++){
			int beads = 0;
			cin >> beads;
			beadCounts.push_back(beads);
		}
		cout << numCombinations(beadCounts) << endl;
	}
	return 0;
}

long long numCombinations(const vector<int> & beadCounts){
	long long combinationFactor = 1;
	long long sumFactor = 0;
	int size = beadCounts.size();

	for(int i = 0; i < size; i++){
		combinationFactor *= pow(beadCounts[i], beadCounts[i] - 1) % 1000000007;
		sumFactor += beadCounts[i];
	}
	return combinationFactor * pow(sumFactor, size - 2) % 1000000007;
}
