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
   bool empty() { return _size <= 0; }
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
   int disordered () const; // 判断向量是否已经排序
   // 遍历
   void traverse ( void ( * ) ( T & ) ); // function pointer
   template <typename VST> void traverse ( VST & ); // function object
   // 有序向量
   int uniquify (); // 剔除有序向量重复元素
   Rank search ( T const &e, Rank lo, Rank hi ) const;
   // 算法
   static Rank binSearch ( T *A, T const &e, Rank lo, Rank hi );
   void sort ( Rank lo, Rank hi );
   void bubbleSort ( Rank lo, Rank hi );
   bool bubble ( Rank lo, Rank hi );
   void merge ( Rank lo, Rank mi, Rank hi );
   void mergeSort ( Rank lo,Rank hi );
};





























/*******************************************************************************
*                                   basic                                   *
*******************************************************************************/

//模版定义贼坑：函数模版和类模版成员函数的定义通常放在头文件中
//曲线救国，实现声明和定义分离
//#include "vector_basic.h"

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
      // remove = remove + shrink + i++
   { find ( _elem[i], 0, i ) > 0 ? remove ( i ) : ++i; }
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

template <typename T>
int Vector<T>::disordered ( ) const { //返回向量中逆序相邻元素对的总数
   int n = 0;
   for ( int i = 1; i != _size; ++i ) {
      if ( _elem[i-1] > _elem[i] ) { ++n; }
   }
   return n; // n = 0 ordered
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
//template <typename T>
//int Vector<T>::uniquify () { // 剔除有序向量重复元素算法 低效版
//int oldSize = _size;
//for ( int i = 1; i != _size; )  { _elem[i-1] = _elem[i] ? remove ( i ) : ++i; }
//return oldSize - _size;
//}

template <typename T>
int Vector<T>::uniquify () { // 剔除有序向量重复元素 高效版本
   Rank lo = 0, hi = 0;
   while ( ++hi != _size )
      if ( _elem[lo] != _elem[hi] ) { _elem[++lo] = _elem[hi]; }
   _size = ++lo;
   shrink ();
   return hi-lo;
}


template <typename T>
Rank Vector<T>::search ( T const &e, Rank lo, Rank hi ) const {
   return binSearch ( _elem, e, lo, hi );
}

//template <typename T>
//Rank Vector<T>::binSearch ( T *A, const T &e, Rank lo, Rank hi ) { // O(logn)
//while ( lo < hi ) { // 三个分支
//Rank mid = ( lo + hi ) >> 1;
//if ( e < A[mid] ) { hi = mid; } // [ lo, mid )
//else if ( e > A[mid] ) { lo = mid + 1; } // ( mid, hi )
//else { return mid; } // [ mid ]
//}
//return -1;
//}

//template <typename T>
//Rank Vector<T>::binSearch ( T *A, const T &e, Rank lo, Rank hi ) {
//while ( hi - lo > 1 ) { // end point  hi == lo + 1 最后查找区间 [ lo, hi )
//Rank mid = ( lo + hi ) >> 1;
//e < A[mid] ? hi = mid // [ lo , mid )
//: lo = mid; // [ mid ,hi )
//}
//return A[lo] == e ? lo:-1;
//}

//// 命中多个元素，返回秩最大者，查找失败时，返回失败位置
//template <typename T>
//Rank Vector<T>::binSearch ( T *A, const T &e, Rank lo, Rank hi ) {
//while ( hi > lo ) { // end point hi = lo  [ lo,lo )
//Rank mid = ( lo+hi ) >> 1;
//e < A[mid] ? hi = mid : lo = mid + 1;
//}
//return --lo; // lo为大于e的最小秩，lo-1则是不大于e的最大秩
//}


template <typename T>
void Vector<T>::sort ( Rank lo, Rank hi ) {
   switch ( rand () % 5 ) {
   case 1 : bubbleSort ( lo,hi ); break;
      //case 2 : selectionSort ( lo,hi ); break;
      //case 3 : mergeSort ( lo,hi ); break;
      //case 4 : heapSort ( lo,hi ); break;
      //default : quickSort ( lo,hi ); break;
   }
}

template <typename T>
void Vector<T>::bubbleSort ( Rank lo, Rank hi ) {
   while ( !bubble ( lo,hi-- ) ) { return; }
}

template <typename T>
bool Vector<T>::bubble ( Rank lo, Rank hi ) {
   bool sorted = true;
   while ( ++lo < hi )
      if ( _elem[lo-1] > _elem[lo] ) {
         swap ( _elem[lo-1], _elem[lo] );
         sorted = false;
      }
   return sorted;
}

template <typename T>
void Vector<T>::mergeSort ( Rank lo, Rank hi ) {
   if ( hi - lo < 2 ) { return; } // 递归基 分到每个单元只有一个元素
   Rank mid = ( hi + lo ) >> 1;
   mergeSort ( lo, mid ); mergeSort ( mid, hi );
   merge ( lo, mid, hi );
}

template <typename T>
void Vector<T>::merge ( Rank lo, Rank mi, Rank hi ) {
   T *final_elem = _elem + lo;	 // final_elem 指向 合并后的数组

   int previous_length = mi - lo; // 前驱数组的长度
   // 开辟一个新的内存空间，用以存储前驱数组(防止覆盖）
   T *previous_elem = new T[previous_length];
   for ( int i = 0; i != previous_length; ++i )
   { previous_elem[i] = final_elem[i]; }

   int successor_length = hi - mi;  // 后继数组的长度
   // 使指针指向后继数组的首元素
   T *successor_elem = _elem + mi;

   for ( Rank i = 0, j = 0, k = 0; j < previous_length || k < successor_length; ) {
      // 短路求值特性
      if ( ( k >= successor_length  || previous_elem[j] <= successor_elem[k] )
            && j < previous_length )
      { final_elem[i++] = previous_elem[j++]; }
      if ( ( j >= previous_length || successor_elem[k] <= previous_elem[j] )
            && k < successor_length )
      { final_elem[i++] = successor_elem[k++]; }
   }
   delete[] previous_elem;
}

#endif /* ifndef VECTOR_H */
