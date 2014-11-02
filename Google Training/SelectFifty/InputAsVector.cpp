#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

vector<int> firstSimpTimeComplex(const vector<int> &numbers){
	vector<int> returnVector;
	vector<int> numbersCopy(numbers);

	int powerDecrementer = 0;
	while(returnVector.size() < 50 && powerDecrementer <= 11){
		vector<int> digitArray[10];
		for(int i = 0; i < numbersCopy.size(); i++){
			listNumber = ( numbersCopy[i] / pow(10, 11 - powerDecrementer) ) % 10;
			digitArray[listNumber].push_back( numbersCopy[i] );
		}

		for(int i = 0; i < 10; i++){
			if( listArray[i].size() <= ( 50 - returnVector.size() ) ||
				powerDecrementer == 11 ){
				for(int j = 0; j < listArray[i].size() && returnVector.size() < 50; j++){
					returnVector.push_back( listArray[i][j] )
				}
			} else {
				numbersCopy = listArray[i];
			}
		}

		powerDecrementer++;
	}

	return returnVector;
}

vector<int> secondSimpTimeComplex(const vector<int> &numbers){
	int arr[1000000000];
	for(int i = 0; i < 1000000000; i++){
		arr[i] = 0;
	}

	for(vector<int>::iterator it = numbers.begin(), itEnd = numbers.end(); 
		it != itEnd; it++){
		arr[*it]++;
	}

	vector<int> returnVector;
	for(int i = 0; i < 1000000000 && returnVector.size() < 50; i++){
		for(int j = 0; j < arr[i] && returnVector.size() < 50; j++){
			returnVector.push_back(i);
		}
	}
	return returnVector;
}

vector<int> firstSpaceComplex(const vector<int> &numbers){
	vector<int> numbersCopy(numbers);
	vector<int>::iterator iterBeg = numbersCopy.begin();
	vector<int>::iterator iterEnd = numbersCopy.end();

	sort(iterBeg, iterEnd);

	vector<int> returnVector;
	copy( iterBeg, iterBeg + 50, returnVector.begin() );

	return returnVector; 
}

vector<int> secondSpaceComplex(const vector<int> &numbers){
	vector<int>::iterator iterBeg = numbers.begin();
	vector<int>::iterator iterEnd = numbers.end();
	vector<int> returnVector;
	copy( iterBeg, iterBeg + 50, returnVector.begin() );
	sort(returnVal.begin(), returnVal.end());

	for(vector<int>::iterator it = numbers.begin() + 50, itEnd = numbers.end(); 
		it != itEnd; it++){
		if(*it < returnVector.back()){
			vector<int>::iterator insertLocation = lower_bound(returnVector.begin(), 
				returnVector.end(), *it)
			returnVector.insert(insertLocation, *it);
			returnVector.pop_back;
		}
	}
	return returnVector;
	
}

vector<int> mostReadible(const vector<int> &numbers){
	vector<int> numbersCopy(numbers);
	vector<int> returnVector;
	for(int i = 0; i < 50; i++){
		std::vector<int>::iterator smallest = min_element( numbersCopy.begin(), numbersCopy.end() );
		returnVector.push_back(*smallest);
		numbersCopy.remove(smallest);
	}

	return returnVector;
	
}