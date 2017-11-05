#pragma once
template <class T>
class MArray
{
	int len;
public:
	T *data;
	MArray()
	{
		data = NULL;
		len = 0;
	}
	MArray(const MArray& other)
	{
		//deep copy......
		len = other.len;
		data = new T[len];
		for ( int i = 0; i < len; i ++ )
		{
			data[i] = other.data[i];
		}
	}
	MArray & operator=(const MArray & rhs)
	{
		len = rhs.len;
		data = new T[len];
		for (int i = 0; i < len; i++)
		{
			data[i] = rhs.data[i];
		}
	}
	~MArray()
	{
		delete[] data;
	}
	T& operator [](int index);
	void push(T d);

	void clear()
	{
		delete[] data;
	}

	int size() { return len; }
};
template <class T>
T& MArray<T>::operator [](int index)
{
	if (index<0 || index>(len - 1))
	{
		//cout << "Bad subscript!" << endl;
		exit(1);
	}
	return data[index];
}
template <class T>
void MArray<T>::push(T d)
{
	T *pdata = data;
	data = new T[len + 1];
	if (pdata != NULL)
	{
		for (int i = 0; i < len; i++)
		{
			data[i] = pdata[i];
		}
		delete[] pdata;
	}
	data[len] = d;
	len++;
}