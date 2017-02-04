/* Author: Nick Palutsis
   Date: April 3, 2016
   CSE 20212
   Lab 9 */

#ifndef ND_VECTOR_H
#define ND_VECTOR_H

#include <iostream>
using namespace std;


// NDVector class definition
template <typename T>
class NDVector {

	public:

		NDVector( int = 10 ); // default constructor  
		NDVector( const NDVector<T> & ); // copy constructor
		~NDVector(); // destructor

		const NDVector &operator=( const NDVector<T> & ); // assignment operator

		T getVal(int); 
		void setVal(int, T);
		void pushBack(T);
		void popBack();
		int getSize() const;
		T getBack();
		void clear();  
		void print();                            

	private:

		int size; // number of elements allocated
		int arrSize; // number of elements actually used
		T *ptr; // pointer to first element of pointer-based array

}; // end class NDVector

template<typename T>
NDVector<T>::NDVector( int arraySize )  {
	size = ( arraySize > 0 ? arraySize : 10 ); // validate arraySize

	ptr = new T[ size ](); // create space for pointer-based array

} // end NDVector default constructor

template<typename T>
NDVector<T>::NDVector( const NDVector<T> &arrayToCopy )  : size( arrayToCopy.size )  {
	ptr = new T[ size ]; // create space for pointer-based array

	for ( int i = 0; i < size; i++ )
		ptr[ i ] = arrayToCopy.ptr[ i ]; // copy into object

}  // end of copy constructor

template<typename T>
NDVector<T>::~NDVector() {
	delete [] ptr; // release pointer-based array space

} // end destructor

template<typename T>
const NDVector<T> &NDVector<T>::operator=( const NDVector<T> &right ) {

	if ( &right != this ) { // avoid self-assignment
		if ( size != right.size ) {
			delete [] ptr; // release space
			size = right.size; // resize this object
			ptr = new T[ size ]; // create space for array copy
		} // end inner if

		for ( int i = 0; i < size; i++ )	
			ptr[ i ] = right.ptr[ i ]; // copy array into object
	} 

	return (*this); // enables x = y = z, for example

} // end function operator=

template<typename T>	// returns the value of a given element
T NDVector<T>::getVal(int i){
	return (ptr[i]);
}

template<typename T>	// sets the value of an element
void NDVector<T>::setVal(int i, T val){
	ptr[ i ] = val;
}

template<typename T>	// adds value to end of array, doubles size if no room
void NDVector<T>::pushBack( T val ){
	T *temp;
	int tempSize;
	if ( size - 1 <= arrSize ) {
		tempSize = size;
		size = size * 2;
	}
	else
		tempSize = size;
	temp = new T[ size ](); // create space for pointer-based array

	for ( int i = 0; i < tempSize; i++ )
		temp[ i ] = ptr[ i ]; // copy into object
	for ( int j = 0; j < size; j++ ){
		if ( temp[ j ] == NULL ){
			temp[ j ] = val;
			arrSize = j + 1;
			break;
		}
	}
	ptr = temp;
}

template<typename T>	// removes element from end
void NDVector<T>::popBack(){
	ptr[ arrSize ] = NULL;
	--arrSize;
}

template<typename T>	// returns the current size of array
int NDVector<T>::getSize() const {
	return arrSize;
}

template<typename T>	// returns last element
T NDVector<T>::getBack(){
	return ptr[ size - 1 ];
}

template<typename T>	// empties list
void NDVector<T>::clear(){
	for ( int i = 0; i < size; i++ )
		ptr[ i ] = NULL;
	size = 0;
}

template<typename T>	// prints list
void NDVector<T>::print(){
	for ( int i = 0; i < arrSize; i++ )
		cout << ptr[ i ] << " ";
	cout << endl;
}

#endif
