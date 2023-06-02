#include <iostream>
#include<stdio.h>
#include <stdlib.h>


void tailRecursion(int n) {
	if (n > 0) {
		printf("%d\n", n);
		tailRecursion(n - 1);
	}
}

void headRecursion(int n) {
	if (n > 0) {
		tailRecursion(n - 1);
		printf("%d\n", n);
	}
}

//another example
int recursionExample(int n) {
	if (n > 0) {
		return recursionExample(n - 1) + n;
	}
	return 0;
}

int recursionWithStaticVariable(int n) {
	static int x = 0;
	if (n > 0) {
		x++;
		return recursionWithStaticVariable(n - 1) + x;
	}
	return 0;
	//In this example is important take into account that
	//x value will be constant and its value will be the last
	//obtained in the last function.
	//In this example x = 5
}


//example factorial of 3
//equal to 3*2*1=6
int factorial(int n) {
	if (n == 0) {
		return 1;
	}
	return factorial(n - 1) * n;
}

int main()
{
	int n = 5;
	//tailRecursion(n);
	//headRecursion(n);

	//printf("%d\n", recursionExample(n));
	//OUTPUT is 15

	//printf("%d\n", recursionWithStaticVariable(n));
	//OUTPUT is 25

	factorial(n);
	printf("%d\n", factorial(n));
	//OUTPUT is 120

	return 0;
}

