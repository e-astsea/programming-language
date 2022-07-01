#include<iostream>
#include<algorithm>
#include<time.h>
using namespace std;

int main() {
	int N;
	clock_t start, end;
	
	while (1) {
		cout << ">> Input the number of numbers to process:";
		cin >> N;
		if (N >= 2 && N <= 30) {
			break;
		}
		if (cin.fail()) {
			cout << "재입력 하세요.\n";
			cin.clear();
			cin.ignore(256, '\n'); 
			return main();
		}
		cout << "재입력 하세요.\n";
	}

	int arr[30];
	cout << ">> Input the numbers to be processed:\n";	

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		if (arr[i] > 100000) {
			cout << "재입력 하세요.\n";
			cin.clear();
			cin.ignore(256, '\n'); 
			return main();
		}
		if (cin.fail()) {
			cout << "재입력 하세요.\n";
			cin.clear();
			cin.ignore(256, '\n');
			return main();
		}

	}
	start = clock();
	
	int temp=0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}






	int result = 0;
	int flag = 0;
	for (int i = 1; i<=arr[0]; i++) {
		for (int j = 0; j < N; j++) {
			if (arr[j] % i != 0) {
				break;
			}
			if (j == N - 1) {
				result = i;
			}
		}

	}
	cout <<"GCD of input numbers is "<< result <<"\n";

	
	int x = 0, y = 1;
	for(int a=0; a<N-1; a++) {
		int prime = 0;
		if (arr[x] == arr[y]) {
			x++;
			y++;
			a++;
		}
		for (int i = arr[x]; i <= arr[y]; i++) {
	
			for (int j = 2; j <= i; j++) {
				if (i == 2) {
					prime++;
				}
				if ((i % j != 0 && j==(i-1))) {
					prime++;
				}
				else if (i % j != 0) {
					continue;
				}
				else
					break;
			}
		}
		cout << "Number of prime numbers between "<<arr[x]<<","<<arr[y]<<":"<<prime << "\n";
		x++;
		y++;
	}
	end = clock();
	double duration = (double)(end - start)/CLOCKS_PER_SEC;
	cout <<"Total execution time using C++ is " << duration <<"seconds!";
}









