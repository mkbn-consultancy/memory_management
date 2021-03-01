#include <fstream>
using namespace std;
ofstream trace("ArrayNew.out");

#include "arrayNewDelete.h"

Widget::Widget() { trace << "*"; }
Widget::~Widget(){ trace << "~"; }

void* Widget::operator new(size_t sz) throw (std::bad_alloc)
{
	trace << "\nWidget::new: "
		<< sz << " bytes" << endl;
	return ::new char[sz];
}

void Widget::operator delete(void* p) 
{
	trace << "\nWidget::delete" << endl;
	::delete []p;
}

void* Widget::operator new[](size_t sz) throw (std::bad_alloc)
{
	trace << "\nWidget::new[]: "
		<< sz << " bytes" << endl;
	return ::new char[sz];
}

void Widget::operator delete[](void* p) 
{
	trace << "\nWidget::delete[]" << endl;
	::delete []p;
}

////////////////////////////////////////////////////////////

int main_array() 
{
	trace << "new Widget" << endl;
	Widget* w = new Widget;
	trace<<"\n------------------\n";

	trace << "\ndelete Widget" << endl;
	delete w;
	trace<<"\n------------------\n";
	
	trace << "\nnew Widget[25]" << endl;
	Widget* wa = new Widget[25];
	
	trace<<"\n------------------\n";
	trace << "\ndelete []Widget" << endl;
	delete []wa;

	return 0;
}