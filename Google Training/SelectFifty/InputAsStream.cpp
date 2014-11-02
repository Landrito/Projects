#include "RedBlack.cpp"
#include <vector>
using namespace std;

vector<int> firstSimpSpaceComplex(){
	rbTree redBlackTree;
	for(int i = 0; i < 50; i++){
		int tempValue = 0;
		inputStream >> tempValue;
		redBlackTree.insert(tempValue);
	}

	for(int i = 0; i < 99950; i++){
		int tempValue = 0;
		inputStream >> tempValue;

		if( tempValue < redBlackTree.max() ){
			redBlackTree.insert(tempValue);
			redBlackTree.removeMax();
		}
	}
	return redBlackTree.toVector();
}

vector<int> secondSimpSpaceComplex(istream & inputStream){
	vector<int> returnVector;

	for(int i = 0; i < 50; i++){
		int tempValue = 0;
		inputStream >> tempValue;
		returnVector.push_back(tempValue);
	}

	sort(returnVector.begin(), returnVector.end());

	for(int i = 0; i < 99950; i++){
		int tempValue = 0;
		inputStream >> tempValue;

		if(tempValue < returnVector.back()){
			vector<int>::iterator insertLocation = lower_bound(returnVector.begin(), 
				returnVector.end(), tempValue)
			returnVector.insert(insertLocation, tempValue);
			returnVector.pop_back();
		}
	}
	return returnVector;
}