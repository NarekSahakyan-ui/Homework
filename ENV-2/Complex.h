#pragma once

class Complex {
private:
	double real;
	double i;

public:
	Complex(double real_ = 0, double i = 0);

	Complex operator+(const Complex& other);
	Complex operator-(const Complex& other);
	Complex operator*(double num);

	double abs() const;
	void display() const;
};
