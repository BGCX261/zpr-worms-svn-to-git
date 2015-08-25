#include <iostream>
#include <assert.h>

using namespace std;

template < class typ >
class P
{
private:
	int* count;
	typ* ptr;

public:
	PtrWrapper(void)
	{
		count = new int;
		*count = 0;
		ptr = NULL;
	}

	PtrWrapper(const typ& arg)
	{
		ptr = new typ(arg);
		count = new int;
		*count = 1;
	}

	PtrWrapper(typ* arg)
	{
		ptr = arg;
		count = new int;
		*count = 1;
	}

	PtrWrapper<typ>& operator=(const PtrWrapper& p)
	{
		if(this != &p)	//jak sam na siebie wskaze zeby nie zliczal
		{				// np a = a;
			if(*count >= 1) dropRef();
			ptr = p.ptr;
			count = p.count;
			(*count)++;
		}
		return *this;
	}

	typ& operator*()
	{
		return *ptr;
	}

	typ* operator->()
	{
		return ptr;
	}

	int getCount()
	{
		return *count;
	}

	~PtrWrapper()
	{
		dropRef();
	}

private:
	void dropRef()
	{
		(*count)--;
		if(*count == 0)
		{
			if(ptr) delete ptr;
			delete count;
		}
	}
};

int main(){
	PtrWrapper<int> a = 1, b, c(2);

	assert(a.getCount() == 1);
	assert(*a ==  1);

	assert(c.getCount() == 1);
	assert(*c == 2);

	a = b;

	assert(a.getCount() == 1);
	//assert(a == NULL);

	a = b = c;

	assert(a.getCount() == 3);
	assert(b.getCount() == 3);
	assert(c.getCount() == 3);
	
	assert(*a == 2);
	assert(*b == 2);
	assert(*c == 2);

	{
		PtrWrapper<int> q;
		q = a;
		assert(a.getCount() == 4);
	}

	assert(a.getCount() == 3);

	double* db = new double(33.3);
	PtrWrapper<double> q(db), w, e;
	w = q;
	
	assert(q.getCount() == 2);
	assert(*q == 33.3);
	assert(*w == 33.3);

}