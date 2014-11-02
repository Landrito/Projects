#include "RedBlack.cpp"
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;


vector<int> firstSimpTimeComplex(istream &inputStream){
	rbTree redBlackTree;

	for(int i = 0; i < 10000; i++){
		int tempValue = 0;
		inputStream >> tempValue;
		redBlackTree.insert(tempValue);
	}
	return redBlackTree.toVector(50); 
	//This is a function that I would write that would do an in-order traversal and would push
	//the number of integers from the tree to the vector
}

vector<int> secondSimTimeComplex(istream &inputStream){
	vector<int> tempVector;
	for(int i = 0; i < 10000; i++){
		int tempValue = 0;
		inputStream >> tempValue;
		tempVector.insert(tempValue);
	}

	sort(tempVector.begin(), tempVector.end());

	vector<int> returnVector;
	for(int i = 0; i < 50; i++){
		returnVector.push_back(tempVector[i])
	}

	return returnVector;
}

vector<int> firstSimpSpaceComplex(istream & inputStream){
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
	return redBlackTree.toVector(50);
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

vector<int> mostReadible(istream & inputStream){
	vector<int> numbers;
	vector<int> returnVector;

	for(int i = 0; i < 10000; i++){
		int tempValue = 0;
		inputStream >> tempValue;
		numbers.push_back(tempValue);
	}

	for(int i = 0; i < 50; i++){
		std::vector<int>::iterator smallest = min_element( numbers.begin(), numbers.end() );
		returnVector.push_back(*smallest);
		numbersCopy.remove(smallest);
	}

	return returnVector;
}






