#ifndef ARRAY_HPP_SENTRY
#define ARRAY_HPP_SENTRY

#include <cassert>
#include <iostream>
#include <iomanip>
#include <memory>
#include <cmath>
 
// #define NDEBUG

template <typename T>
class Array {

	T *data;
	int array_length;

public:

	Array() : data(nullptr), array_length(0) {}

	Array(int length) : array_length(length)
	{
		assert(length >= 0 && "Array length is >= 0");
		if (length > 0)
			data = new T[length];
		else
			data = nullptr;
	}

	~Array()
	{
		delete[] data;
	}

	friend std::ostream& operator<<(std::ostream& cout, const Array<T> &ar)
	{
		for (int i = 0; i < ar.array_length; ++i)
			cout << ar.data[i] << std::endl;
		return cout;
	}

	void erase()
	{
		delete[] data;
		data = nullptr;
		array_length = 0;
	}

	T& operator[](int index)
	{
		assert(index >= 0 && index < array_length && "Incorrect index!");
		return data[index];
	}

	/* Destroying all elements */
	void reallocate(int newLength)
	{
		erase();

		if (newLength <= 0)
			return;

		data = new T[newLength];
		array_length = newLength;
	}

	void resize(int newLength)
	{
		if (newLength == array_length)
			return;

		if (newLength <= 0) {
			erase();
			return;
		}

		T *arr = new T[newLength];

		if (array_length > 0) {
			int elementsToCopy = (newLength > array_length) ? array_length : newLength;

			for (int index = 0; index < elementsToCopy ; ++index)
				arr[index] = data[index];
		}

		delete[] data;

		data = arr;
		array_length = newLength;
	}

	std::shared_ptr<Array<T>> copy() const 
	{
		auto newArray = std::make_shared<Array<T>>(array_length);
		for (int i = 0; i < array_length; ++i) 
			newArray->data[i] = data[i];
		return newArray;
	}

	void insertBefore(T value, int index)
	{
		assert(index >= 0 && index <= array_length && "Incorrect index!");

		T *arr = new T[array_length + 1];

		for (int before = 0; before < index; ++before)
			arr[before] = data[before];

		arr[index] = value;

		for (int after = index; after < array_length; ++after)
			arr[after + 1] = data[after];

		delete[] data;
		data = arr;
		++array_length;
	}

	void remove(int index)
	{
		assert(index >= 0 && index < array_length && "Incorrect index");

		if (array_length == 1) {
			erase();
			return;
		}

		T *arr = new T[array_length - 1];

		for (int before = 0; before  < index; ++before)
			arr[before] = data[before];

		for (int after = index + 1; after < array_length; ++after )
			arr[after - 1] = data[after];

		delete[] data;
		data = arr;
		--array_length;
	}

	int count(T obj)
	{
		int n = 0;
		for (int i = 0; i < array_length; ++i) {
			n += obj == data[i];
		}
		return n;
	}

	int find(T obj)
	{
		for (int i = 0; i < array_length; ++i)
			if (obj == data[i])
				return i;
		return -1;
	}

	void insertAtBeginning(T value) { insertBefore(value, 0); }
	void insertAtEnd(T value) { insertBefore(value, array_length); }

	int getLength() const { return array_length; }
};
 
#endif
