a#include <iostream>
using namespace std;

template <class T>
class vector
{
private:
	T* array;
	int count;
	int _size;
public:
	vector( int size = 0 ) : _size(size), count(0)
	{
		cout << "ctor: " << "size = " << size << " count=" << count << endl;
		array = new T[size];
	}
	vector(const vector& rhs) : array(NULL)
	{
		operator=(rhs);
	}

	~vector()
	{
		delete []array;
	}

	int size() const { return _size; }

	T& operator[]( int index )
	{
		if( index < 0 || index >= _size )
			throw "out of range";
		
		return array[index];
	}

	const T& operator[]( int index ) const
	{
		if( index < 0 || index >= _size )
			throw "out of range";

		return array[index];
	}

	const vector& operator=(const vector& rhs);

	void resize( int newsize );

	bool empty() { return count != 0; }

	void push_back( T item );
};

template<class T>
const vector<T>& vector<T>::operator=(const vector<T>& rhs)
{
	if( this != &rhs )
	{
		delete []array;
		_size = rhs._size;
		array = new T[size];
		
		for( int i = 0; i < _size; i++ )
			array[i] = rhs.array[i];
	}
	return *this;
}

template<class T>
void vector<T>::resize( int newsize )
{
	T* oldarray = array;

	int numToCopy = newsize < _size ? newsize : _size;

	array = new T[newsize];
	for( int i = 0; i < numToCopy; i++ )
		array[i] = oldarray[i];

	delete []oldarray;
	_size = newsize;
}

template<class T>
void vector<T>::push_back( T item )
{
	if (count < _size )
		resize(1);
	array[count++] = item;
}

int
main( void )
{
	vector<int> v;

	for( int i = 0; i < 5; i++ )
		//v[i] = i;
		v.push_back(i);
	
	for ( int i = 0; i < v.size(); i++ )
		cout << v[i] << endl;
}
