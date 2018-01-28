
#include <iostream>
#include <stddef.h>

struct OutOfRange
{
	
};

template <typename T, size_t H,size_t... Dims>
class Array
{
public:
	Array<T,Dims...> array[H];

	typedef T ValueType;
	Array<T,Dims...> &operator[](const size_t index)
	{
		if(index>=H)
			throw OutOfRange();
		return array[index];
	}

	const Array<T,Dims...> &operator[](const size_t index) const
	{
		if(index>=H)
			throw OutOfRange();
		return array[index];
	}

	Array(){}

	Array(const Array &a)
	{
		for(size_t i=0;i<H;i++)
		{
			array[i]=a.array[i];
		}
	}

	template <typename U> 
	Array(const Array<U, H, Dims...> &a)
	{
		for(size_t i=0;i<H;i++)
		{
			array[i]=a.array[i];
		}
	}

	Array &operator=(const Array &a)
	{
		for(size_t i=0;i<H;i++)
		{
			array[i]=a.array[i];
		}
		return *this;
	}

	template <typename U> 
	Array &operator=(const Array<U, H, Dims...> &a)
	{
		for(size_t i=0;i<H;i++)
		{
			array[i]=a.array[i];
		}
		return *this;
	}

	class FirstDimensionMajorIterator
	{
	public:
		Array<T,H,Dims...> *array;
		Array<T,Dims...> *ptr;
		size_t currentIndex;
		size_t size;
		bool last;
		typename Array<T,Dims...>::FirstDimensionMajorIterator nextDimIt;
		FirstDimensionMajorIterator():array(nullptr),ptr(nullptr),currentIndex(0),size(H),last(false){}

		void moveAhead()
		{
			nextDimIt.array=&(array->array[currentIndex]);
			nextDimIt.last=false;
			nextDimIt.currentIndex=0;
			nextDimIt.moveAhead();
		}

		FirstDimensionMajorIterator &operator++()
		{
			nextDimIt++;
			if(nextDimIt.last)
			{
				currentIndex++;
				if(currentIndex>=size)
				{
					last=true;
				}
				else
				moveAhead();
			}
			return *this;
		}

		FirstDimensionMajorIterator operator++(int)
		{
			FirstDimensionMajorIterator tmp=*this;
			++(*this);
			return tmp;
		}

		T &operator*() const
		{
			return *nextDimIt;
		}

		friend bool operator==(const FirstDimensionMajorIterator &t1, const FirstDimensionMajorIterator &t2)
		{
			if(t1.array!=t2.array)
				return false;
			else if(t1.currentIndex!=t2.currentIndex)
				return false;
			return (t1.nextDimIt==t2.nextDimIt);
		}

		friend bool operator!=(const FirstDimensionMajorIterator &t1, const FirstDimensionMajorIterator &t2)
		{
			return !(t1==t2);
		}
	};

	class LastDimensionMajorIterator
	{
	public:
		Array<T,H,Dims...> *array;
		Array<T,Dims...> *ptr;
		size_t currentIndex;
		size_t size;
		bool last;
		typename Array<T,Dims...>::LastDimensionMajorIterator nextDimIt;
		LastDimensionMajorIterator():array(nullptr),ptr(nullptr),currentIndex(0),size(H),last(false){}

		void moveAhead()
		{
			if(!last){
			nextDimIt.array=&(array->array[currentIndex]);
			nextDimIt.moveAhead();
			}
		}

		LastDimensionMajorIterator &operator++()
		{
			currentIndex++;
			if(currentIndex>=size)
			{
				nextDimIt++;
				last=nextDimIt.last;
				if(!last)
				currentIndex=0;
			}
			moveAhead();
			return *this;
		}

		LastDimensionMajorIterator operator++(int)
		{
			LastDimensionMajorIterator tmp=*this;
			++(*this);
			return tmp;
		}

		T &operator*() const
		{
			return *nextDimIt;
		}

		friend bool operator==(const LastDimensionMajorIterator &t1, const LastDimensionMajorIterator &t2)
		{
			if(t1.array!=t2.array)
				return false;
			else if(t1.currentIndex!=t2.currentIndex)
				return false;
			return (t1.nextDimIt==t2.nextDimIt);
		}

		friend bool operator!=(const LastDimensionMajorIterator &t1, const LastDimensionMajorIterator &t2)
		{
			return !(t1==t2);
		}
	};

	FirstDimensionMajorIterator fmbegin()
	{
		FirstDimensionMajorIterator tmp;
		tmp.array=this;
		tmp.currentIndex=0;
		tmp.nextDimIt=array[0].fmbegin();
		tmp.ptr=&(array[0]);
		return tmp;
	}

	FirstDimensionMajorIterator fmend()
	{
		FirstDimensionMajorIterator tmp;
		tmp.array=this;
		tmp.currentIndex=H;
		tmp.nextDimIt=array[H-1].fmend();
		tmp.last=true;
		return tmp;
	}

	LastDimensionMajorIterator lmbegin()
	{
		LastDimensionMajorIterator tmp;
		tmp.array=this;
		tmp.currentIndex=0;
		tmp.nextDimIt=array[0].lmbegin();
		tmp.ptr=&(array[0]);
		return tmp;
	}

	LastDimensionMajorIterator lmend()
	{
		LastDimensionMajorIterator tmp;
		tmp.array=this;
		tmp.currentIndex=H;
		tmp.nextDimIt=array[H-1].lmend();
		tmp.last=true;
		return tmp;
	}
};

template <typename T, size_t N>
class Array<T,N>
{
public:
	T array[N];
	typedef T ValueType;
	Array(){}

	Array(const Array &a)
	{
		for(size_t i=0;i<N;i++)
		{
			array[i]=a.array[i];
		}
	}

	Array &operator=(const Array &a)
	{
		for(size_t i=0;i<N;i++)
		{
			array[i]=a.array[i];
		}
		return *this;
	}

	template <typename U> 
	Array(const Array<U,N> &a)
	{
		for(size_t i=0;i<N;i++)
		{
			array[i]=a.array[i];
		}
	}

	template <typename U> 
	Array &operator=(const Array<U, N> &a)
	{
		for(size_t i=0;i<N;i++)
		{
			array[i]=a.array[i];
		}
		return *this;
	}

	T &operator[](const size_t index)
	{
		if(index>=N)
			throw OutOfRange();
		return array[index];
	}

	const T &operator[](const size_t index) const
	{
		if(index>=N)
			throw OutOfRange();
		return array[index];
	}

	class FirstDimensionMajorIterator
	{
	public:
		Array<T,N> *array;
		T *ptr;
		size_t currentIndex;
		size_t size;
		bool last;
		FirstDimensionMajorIterator():array(nullptr),ptr(nullptr),currentIndex(0),size(N),last(false){}

		void moveAhead()
		{
			ptr=&(array->array[currentIndex]);
		}

		FirstDimensionMajorIterator operator++()
		{
			currentIndex++;
			if(currentIndex>=size)
			{
				last=true;
			}
			else
			moveAhead();
			return *this;
		}

		FirstDimensionMajorIterator operator++(int)
		{
			FirstDimensionMajorIterator tmp=*this;
			++(*this);
			return tmp;
		}

		T &operator*() const
		{
			return *ptr;
		}

		friend bool operator==(const FirstDimensionMajorIterator &t1, const FirstDimensionMajorIterator &t2)
		{
			return (t1.array==t2.array)&&(t1.currentIndex==t2.currentIndex);
		}

		friend bool operator!=(const FirstDimensionMajorIterator &t1, const FirstDimensionMajorIterator &t2)
		{
			return !((t1.array==t2.array)&&(t1.currentIndex==t2.currentIndex));
		}
		
	};

	class LastDimensionMajorIterator
	{
	public:
		Array<T,N> *array;
		T *ptr;
		size_t currentIndex;
		size_t size;
		bool last;
		LastDimensionMajorIterator():array(nullptr),ptr(nullptr),currentIndex(0),size(N),last(false){}

		void moveAhead()
		{
			ptr=&(array->array[currentIndex]);
		}

		LastDimensionMajorIterator &operator++()
		{
			currentIndex++;
			if(currentIndex>=size)
			{
				last=true;
			}
			else
				moveAhead();
			return *this;
		}

		LastDimensionMajorIterator operator++(int)
		{
			LastDimensionMajorIterator tmp=*this;
			++(*this);
			return tmp;
		}

		T &operator*() const
		{
			return *ptr;
		}

		friend bool operator==(const LastDimensionMajorIterator &t1, const LastDimensionMajorIterator &t2)
		{
			return (t1.array==t2.array)&&(t1.currentIndex==t2.currentIndex);
		}

		friend bool operator!=(const LastDimensionMajorIterator &t1, const LastDimensionMajorIterator &t2)
		{
			return !((t1.array==t2.array)&&(t1.currentIndex==t2.currentIndex));
		}
	};

	FirstDimensionMajorIterator fmbegin()
	{
		FirstDimensionMajorIterator tmp;
		tmp.array=this;
		tmp.currentIndex=0;
		tmp.ptr=&(array[0]);
		return tmp;
	}

	FirstDimensionMajorIterator fmend()
	{
		FirstDimensionMajorIterator tmp;
		tmp.array=this;
		tmp.currentIndex=N;
		tmp.last=true;
		return tmp;
	}

	LastDimensionMajorIterator lmbegin()
	{
		LastDimensionMajorIterator tmp;
		tmp.array=this;
		tmp.currentIndex=0;
		tmp.ptr=&(array[0]);
		return tmp;
	}

	LastDimensionMajorIterator lmend()
	{
		LastDimensionMajorIterator tmp;
		tmp.array=this;
		tmp.currentIndex=N;
		tmp.last=true;
		return tmp;
	}

};