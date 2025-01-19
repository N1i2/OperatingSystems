#include <iostream>
#include<string>
#include <chrono>
#include <cmath>

bool isPrime(int num) {
	if (num < 2) {
		return false;
	}
	for (int i = 2; i <= std::sqrt(num); ++i) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "error not arg\n";
		return 1;
	}

	int duration = std::stoi(argv[1]);
	auto start = std::chrono::steady_clock::now(); 

	int primeCount = 0; 
	int number = 2;     

	while (true) {
		if (isPrime(number)) {
			++primeCount;
			std::cout << primeCount << ") " << number << std::endl;
		}
		++number;

		auto end = std::chrono::steady_clock::now();
		auto passTime = std::chrono::duration_cast<std::chrono::seconds>(end - start);

		if (passTime.count() >= duration) {
			break;
		}
	}

	std::cout << "\nResult: " << primeCount << std::endl;

	while(true) {

	}
	return 0;
}
