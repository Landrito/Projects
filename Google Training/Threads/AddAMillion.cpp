#include <thread>
#include <iostream>

const int NUM_VALUES = 1000000;
const int NUM_THREADS = 8;

int main(){
	int * array = new int[NUM_VALUES];
	int * results = new int[NUM_THREADS];

	//Do something here to initialize the array to the values to which we needa add.

	std::thread ** threadArray = new std:thread*[NUM_THREADS];

	for(int i = 0; i < NUM_THREADS; i++){
		results[i] = 0;
		threadArray[i] = new std::thread(sumValues, array, std::ref(results[i]), i*(NUM_VALUES / NUM_THREADS), (i+1)*(NUM_VALUES/NUM_THREADS));
	}

	int finalResult = 0;
	sumValues(results, std::ref(finalResult), 0, NUM_THREADS);

	std::cout << finalResult << " Bitches." << std::endl;

	return 0;
}

void sumValues(int * arr, int & result, int start, int end){
	for(int i = start; i < end; i++){
		result += arr[i];
	}
}