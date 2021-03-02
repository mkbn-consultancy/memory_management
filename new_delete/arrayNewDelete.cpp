#include <fstream>
#include <iostream>

//using namespace std;
//ofstream trace("ArrayNew.out");
std::ostream& trace = std::cout;

#include "arrayNewDelete.h"

Widget::Widget() { trace << "inside Widget constructor\n"; }
Widget::~Widget(){ trace << "inside Widget destructor\n"; }

void* Widget::operator new(size_t sz) //throw (std::bad_alloc)
{
	trace << "\ninside Widget::new: allocating "
		<< sz << " bytes" << std::endl;
	return ::new char[sz];
}

void Widget::operator delete(void* p) 
{
	trace << "\ninside Widget::delete only freeing the memory" << std::endl;
	//::delete static_cast<Widget*>(p);
	free(p);
}

void* Widget::operator new[](size_t sz) //throw (std::bad_alloc)
{
	trace << "\ninside Widget::new[]: allocating "
		<< sz << " bytes" << std::endl;
	return ::new char[sz];
}

void Widget::operator delete[](void* p) 
{
	trace << "\ninside Widget::delete[] only freeing the memory" << std::endl;
	//::delete [] static_cast<Widget*>(p);
	free(p);
}

////////////////////////////////////////////////////////////

int main() 
{
	trace <<"\n------------------\n";
	trace << ">> creating a new Widget..." << std::endl;
	trace << "command: Widget* w = new Widget;\n";
	Widget* w = new Widget;
	trace <<"\n------------------\n";

	trace << ">> deleting the Widget..." << std::endl;
	trace << "command: delete w;\n\n";
	delete w;
	trace<<"\n------------------\n";
	
	trace << ">> creating an array Widget[3]..." << std::endl;
	trace <<"command: new Widget[3];\n";
	Widget* wa = new Widget[3];
	
	trace<<"\n------------------\n";
	trace << ">> deleting the Widget array..." << std::endl;
	trace<<"command: delete[] wa;\n\n";
	delete []wa;

	trace<<"\n------------------\n";

	return 0;
}