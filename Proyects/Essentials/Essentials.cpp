#include <iostream>
#include<stdio.h>
#include <stdlib.h>

using namespace std;

void arrayBasics() {

	int A[5];
	A[0] = 12;
	A[1] = 15;

	int B[10] = { 2,4,6,8,10,12 };

	cout << sizeof(A) << endl;
	cout << A[1] << endl;

	printf("%d\n", A[2]);

	for (int i = 0; i < 10; i++) {
		cout << B[i] << endl;
	}
}

struct Rectangle {

	int length;
	int width;
};

void pointerBasicsExample1() {

	int a = 10;
	int *p;
	p = &a;

	cout << a << endl;

	//value of the data the pointer is pointing at
	printf("%d", *p);

	//value of the address the pointer is pointing at
	printf("%d", p);
}

void pointerBasicsExample2() {

	int A[5] = { 3,6,9,12,15 };

	int *p;
	p = A;

	//this is incorrect
	//p=&A;

	//print all values contained on array A
	for (int i = 0; i < 5; i++) {
		cout << p[i] << endl;
	}
}

void referenceBasics() {
	int a = 10;

	//this statement is an alias of a
	int &r = a;

	//prints the same value a have
	cout << a << endl << r << endl;

	//if we now change
	r = 25;

	//prints the same value r has now
	cout << a << endl << r << endl;

	//but what happens now
	int b = 30;
	r = b;

	//value 30 is stored in r, so 30 is stored in A, r means A itself
	cout << a << endl << r << endl;
}

void pointerToStructure() {
	struct Rectangle r = { 10,5 };

	//how r is a structure you can use
	cout << r.length << endl;
	cout << r.width << endl;

	struct Rectangle *p = &r;

	//you cannot do this because p is a pointer
	//*p.length =20;

	//instead you can use this to modify the length of r
	p->length = 20;

	cout << p->length << endl;
	cout << p->width << endl;
}

int sum(int a, int b) {

	return a + b;
}

void functionBasics() {

	int num1 = 10;
	int num2 = 20;

	cout << sum(num1, num2);
}

void printDimension(struct Rectangle r) {

	cout << "Length " << r.length << endl << "Width " << r.width << endl;
}

void printDimensionCustomized(struct Rectangle r) {

	r.length = 30;
	cout << "Length " << r.length << endl << "Width " << r.width << endl;
}

void printDimensionUsingPointerParam(struct Rectangle *r) {

	r->length = 40;
	cout << "Length " << r->length << endl << "Width " << r->width << endl;
}

void structureBasicsExample1() {

	struct Rectangle rectangle = { 4,6 };
	printf("%lu", sizeof(rectangle));
}

void structureBasicsExample2() {

	struct Rectangle r = { 10,5 };

	//when we pass a rectangle structure as a parameter
	//a new structure will be created on memory with both parameters.
	printDimension(r);

	//when we call by value, we get 30,5
	//because inside the function we change the length of r.
	printDimensionCustomized(r);

	//when we call by address, we get the get the same results (40,5) by
	//calling the function or printing the dimensions because is the same object.
	printDimensionUsingPointerParam(&r);
	cout << "Length " << r.length << endl << "Width " << r.width << endl;
}

int main()
{
	//arrayBasics();
	//pointerBasicsExample1();
	//pointerBasicsExample2();
	//referenceBasics();
	//pointerToStructure();
	//functionBasics();
	//structureBasicsExample1();
	structureBasicsExample2();

	return 0;
}









