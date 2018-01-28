## Synopsis

Implementation of an `Array` template class which can be instantiated with an any number of dimensions. The implementation does not use heap memory.

## Usage

- Initialization
	A 4x3x5 array of integers can be initialized as follows:
	```c++
	Array<int,4,3,5> array;
	```

- Assignment
	We can assign a new value in the above array as follows:
	```c++
	array[0][1][2]=45;
	```

- Iteration
	We can iterate over the array in two ways i.e. First dimension major(row major in case of a 2D array) and Last dimension major(column major in case of a 2D array). We can get iterator pointing to the first element in the array by using `fmbegin()`(FirstDimensionMajorIterator) or `lmbegin()`(LastDimensionMajorIterator) and use to increment operator to move to the next element.
	```c++
	for(auto it=array.fmbegin();it!=fmend();++it)
	{
		//code
	}
	for(auto it=array.lmbegin();it!=lmend();++it)
	{
		//code
	}
	```