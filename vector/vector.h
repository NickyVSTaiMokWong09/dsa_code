#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>
#include <algorithm>
#include <cstdio>

using namespace std;
typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T> class Vector {
protected:
   Rank _size; int _capacity; T *_elem; //规模，容量，数据区
   void copyFrom ( T const *A, Rank lo, Rank hi );
   void expand (); // 扩容
   void shrink (); // 缩容
public:
   // constructor
   Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 )
   { _elem = new T[_capacity  = c]; for ( _size=0; _size<s; _elem[_size++]= v ); }
   Vector ( T const *A, Rank n ) { copyFrom ( A, 0, n ); } // 数组整体赋值
   Vector ( T const *A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } // 数组区间赋值
   explicit Vector ( Vector<T> const &V ) { copyFrom ( V._elem, 0, V._size ); } // 向量整体赋值
   Vector ( Vector<T> const &V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } // 区间赋值
   Vector<T> &operator= ( Vector<T> const &a );
   T &operator[] ( Rank r ) { return _elem[r]; }
   Rank size() const { return _size; }
   // destructor
   ~Vector () { delete[] _elem; }
   //
   void unsort ( Rank lo, Rank hi );
   Rank find ( T const &e, Rank lo, Rank hi );
   Rank find ( T const &e ) { return find ( e, 0, _size ); }
   Rank insert ( Rank r, T const &e );
   int remove ( Rank lo, Rank hi );
   T remove ( Rank r );
   int deduplicate();
   // 遍历
   void traverse ( void ( * ) ( T & ) ); // function pointer
   template <typename VST> void traverse ( VST & ); // function object
};





























/*******************************************************************************
*                                   basic                                   *
*******************************************************************************/

//模版定义贼坑：函数模版和类模版成员函数的定义通常放在头文件中
//曲线救国，实现声明和定义分离
#include "vector_basic.h"

template <typename T>
void Vector<T>::copyFrom ( T const *A, Rank lo, Rank hi ) {
   _elem = new T[_capacity = ( hi - lo ) * 2]; _size = 0;
   while ( lo < hi ) { _elem[_size++] = A[lo++]; }
}

template <typename T>
Vector<T> &Vector<T>::operator= ( Vector<T> const &V ) {
   if ( _elem ) { delete [] _elem; }
   copyFrom ( V._elem, 0, V._size );
   return *this;
}

template <typename T>
void Vector<T>::expand () {
   if ( _size < _capacity ) { return; }
   if ( _capacity < DEFAULT_CAPACITY ) { _capacity = DEFAULT_CAPACITY; }
   T *oldelem = _elem; _elem = new T[_capacity <<= 1];
   for ( int i = 0; i != _size; ++i ) {
      _elem[i] = oldelem[i];
   }
   delete [] oldelem;
}

template <typename T>
void Vector<T>::shrink () {
   if ( _capacity >> 1 < DEFAULT_CAPACITY ) { return; }
   if ( _size << 2 > _capacity ) { return; }
   T *oldelem = _elem; _elem = new T[_capacity >>= 1];
   for ( int i = 0; i!=_size; ++i ) {
      _elem[i] = oldelem[i];
   }
   delete [] oldelem;
}

template <typename T>
Rank Vector<T>::find ( const T &e, Rank lo, Rank hi ) {
   // 最后一次比较完，还会自减一次,所以会返回-1   hi>lo, hi = hi-1
   while ( ( hi-- > lo ) && ( _elem[hi] != e ) );
   return hi;
}

template <typename T>
Rank Vector<T>::insert ( Rank r, const T &e ) {
   expand();
   // _size = max(Rank) + 1
   for ( int i = _size;  i > r ; --i ) {
      _elem[i] = _elem[i-1];
   }
   _elem[r] = e; ++_size;
   return r;
}

template <typename T>
int Vector<T>::remove ( Rank lo, Rank hi ) {
   if ( hi == lo ) { return 0; }
   while ( hi < _size ) { _elem[lo++] = _elem[hi++]; }
   _size = lo; // 丢弃 [lo,_size=hi)
   shrink();
   return hi-lo;
}

template <typename T>
T Vector<T>::remove ( Rank r ) {
   T e = _elem[r];
   remove ( r, r+1 );
   return e;
}

template <typename T>
int Vector<T>::deduplicate () {
   int oldSize = _size;
   Rank i = 1;
   while ( i < _size )
   { find ( _elem[i], 0, i ) > 0 ? remove ( i ) : ++i; } // remove += shrink + i++
   return oldSize-_size;
}

template <typename T>
void Vector<T>::traverse ( void ( *visit ) ( T & ) ) {
   for ( int i = 0;  i < _size; ++i ) { visit ( _elem[i] ); }
}

template <typename T> template <typename VST>
void Vector<T>::traverse ( VST &vst ) {
   for ( int i = 0; i < _size; ++i ) { vst ( _elem[i] ); }
}
/*******************************************************************************
*                                   basic                                   *
*******************************************************************************/

template <typename T> class Increase
{ public:virtual void operator() ( T &e ) { ++e; } };

template <typename T> void increase ( Vector<T> &V )
{ Increase<T> test; V.traverse ( test ); }

/*******************************************************************************
*                                  algorithm                                  *
*******************************************************************************/

#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;


template <typename T>
void Vector<T>::unsort ( Rank lo, Rank hi ) {
   T *V = _elem + lo;
   for ( Rank i = hi -lo; i != 0; --i ) {
      swap ( V[i-1], V[rand() %i] );
   }
}

/*******************************************************************************
*                                  algorithm                                  *
*******************************************************************************/

#endif /* ifndef VECTOR_H */
