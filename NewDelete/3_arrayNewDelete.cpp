#include <fstream>
#include <iostream>

using namespace std;
//ofstream trace("ArrayNew.out");
ostream& trace = std::cout;

#include "arrayNewDelete.h"

Widget::Widget() { trace << "-*"; }
Widget::~Widget(){ trace << "-~"; }

void* Widget::operator new(size_t sz)
{
	trace << "[Widget] Widget::new: "
		<< sz << " bytes" << endl;
	return malloc(sz);
}

void Widget::operator delete(void* p) 
{
	trace << "\n[Widget] Widget::delete" << endl;
	free(p);
}

void* Widget::operator new[](size_t sz)
{
	trace << "[Widget] Widget::new[]: "
		<< sz << " bytes" << endl;
	return malloc(sz);
}

void Widget::operator delete[](void* p) 
{
	trace << "\n[Widget] Widget::delete[]" << endl;
	free(p);
}

////////////////////////////////////////////////////////////

int main() 
{
	trace<<"\n------------------\n\n";
	trace << "[main] call new Widget:" << endl;
	Widget* w = new Widget;
	// trace<<"\n------------------\n";

	trace << "\n[main] call delete Widget:" << endl;
	delete w;
	// trace<<"\n------------------\n";
	
	trace << "\n[main] call new Widget[25]:" << endl;
	Widget* wa = new Widget[25];
	
	// trace<<"\n------------------\n";
	trace << "\n[main] call delete[] Widget:" << endl;
	delete[] wa;
	trace<<"\n------------------\n";

	return 0;
}