#ifndef __ARRAYNEWDELETE_H__
#define __ARRAYNEWDELETE_H__

class Widget 
{
public:
	Widget();
	~Widget();

	void* operator new(size_t sz) throw();
	void operator delete(void* p);

	void* operator new[](size_t sz) throw();
	void operator delete[](void* p);

private:
	static const int sz = 10;
	int i[sz];
};

#endif //__ARRAYNEWDELETE_H__