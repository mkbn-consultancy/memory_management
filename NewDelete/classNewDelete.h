#ifndef __CLASSNEWDELETE_H__
#define __CLASSNEWDELETE_H__

class MemBlock
{
public:
	enum{BLOCK_SIZE=10, MAX_POOL_SIZE=100};
public:
	MemBlock(); 
	~ MemBlock(); 
	void* operator new(size_t);
	void operator delete(void*);
private:
	char c[BLOCK_SIZE]; // To take up space, not used, just to have a size of theh block.
	static unsigned char _pool[];
	static unsigned char _alloc_map[];
};

#endif //__CLASSNEWDELETE_H__