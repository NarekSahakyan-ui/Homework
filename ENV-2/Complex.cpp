#include <iostream>
#include <cmath>
#include "Complex.h"

Complex::Complex(double real_, double i_) : real(real_), i(i_) {}

Complex Complex::operator+(const Complex& other) {
	return Complex(real + other.real, i + other.i);
}

Complex Complex::operator-(const Complex& other) {
	return Complex(real - other.real, i - other.i); 
}

Complex Complex::operator*(double num) {
	return Complex(real * num, i * num);
}

double Complex::abs() const {
	return std::sqrt(real * real + i * i);
}

void Complex::display() const {
	std::cout << real << " + " << i << "i" << std::endl;
}
