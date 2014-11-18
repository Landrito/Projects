#include <thread>
#include <iostream>

const int NUM_VALUES = 1000000;
const int NUM_THREADS = 8;
const int MAX_VALUE = 15 * NUM_VALUES / 1000;

void sumValues(int * arr, int & result, int start, int end);
void assignValue(int * arr, int start, int end);

int main(){
	int * array = new int[NUM_VALUES];
	int * results = new int[NUM_THREADS];

	//ASSIGN THE VALUES
	std::thread ** threadArray = new std::thread*[NUM_THREADS];
	for(int i = 0; i < NUM_THREADS; i++){
		threadArray[i] = new std::thread(assignValue, array, i*(NUM_VALUES / NUM_THREADS), (i+1)*(NUM_VALUES/NUM_THREADS));
	}

	for(int i = 0; i < NUM_THREADS; i++){
		threadArray[i]->join();
	}

	//CALCULATE THE VALUES
	for(int i = 0; i < NUM_THREADS; i++){
		results[i] = 0;
		threadArray[i] = new std::thread(sumValues, array, std::ref(results[i]), i*(NUM_VALUES / NUM_THREADS), (i+1)*(NUM_VALUES/NUM_THREADS));
	}

	for(int i = 0; i < NUM_THREADS; i++){
		threadArray[i]->join();
	}

	int finalResult = 0;
	sumValues(results, std::ref(finalResult), 0, NUM_THREADS);

	std::cout << finalResult << " Bitches." << std::endl;

	return 0;
}

void sumValues(int * arr, int & result, int start, int end){
	for(int i = start; i < end; i++){
		bool prime = true;
		for(int j = 2; j <= MAX_VALUE && prime; i++){
			if(arr[i] == 1){
				prime = false;
			} else if(arr[i] % j == 0){
				prime = false;
			}
		}
		if(prime){
			result += arr[i];
		}
	}
}

void assignValue(int * arr, int start, int end){
	for( int i = start; i < end; i++){
		arr[i] = 15 * i / 1000;
	}
}