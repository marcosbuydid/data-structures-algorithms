#include <iostream>

using namespace std;

/*
* PositionList using dinamic array, a variable maxSize,
* and a variable top.
* Element and numberOfElements operations are made in
* constant order in the worst case.
* Implementation is unbounded.
*/

struct PositionList {
    int* list;
    unsigned int maxSize;
    int index;
};

PositionList* createPositionList() {
	PositionList* ps = new PositionList();
    ps->maxSize = 10;
    ps->list = new int[ps->maxSize];
    ps->index = 0;
    return ps;
}

int main()
{
    return 0;
}

