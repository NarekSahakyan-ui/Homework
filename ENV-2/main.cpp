#include <iostream>
#include <vector>
#include "Complex.h"
#include "Sort.h"

int main() {

std::vector<Complex> numbers;
numbers.emplace_back(1, 2);
numbers.emplace_back(7, 9);
numbers.emplace_back(0, 6);
numbers.emplace_back(7, 0);

Complex num1(1, 2);
Complex num2(2, 3);

num1 = num1 + num2;

int n = 10;

num2 = num1 * n;

for(const auto& num : numbers) {
	num.display();
}

Sort(numbers);

for(const auto& num : numbers) {
	num.display();
}

}
