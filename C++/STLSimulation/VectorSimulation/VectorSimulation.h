#pragma once

template <typename T>
class vec
{
	T* arr{ nullptr };
	size_t sz{ 0 };

public:
	vec();
	void push(int data);
	T operator[](int index)
	{
		return *(arr + index);
	}
};

template<typename T>
inline vec<T>::vec()
{
    
}

template<typename T>
inline void vec<T>::push(int data)
{
	++sz;
	T *temp = new T[sz];
	for (unsigned int i = 0; i < sz - 1; i++)
	{
		*(temp + i) = *(arr + i);
	}
	*(temp + sz - 1) = data;
	delete []arr;
	arr = temp;
}
