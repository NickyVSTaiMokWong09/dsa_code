#include "listNode.h"

template <typename T>  class List {
private:
   int _size; // 规模
   ListNodePosi ( T ) header; ListNodePosi ( T ) trailer; // 头，尾 哨兵

protected:
   void init(); // 创建列表的初始化
   void copyNodes ( ListNodePosi ( T ) p, int n );
   int clear();

public:
   // constructor
   List () { init (); }
   // 复制自p点起的后n项
   List ( ListNodePosi ( T ) p, int n ) { copyNodes ( p, n ); }
   List ( List<T> const &l ) { copyNodes ( l.first(), l._size ); }
   // 复制l中第r项起的n项
   List ( List<T> const &l, int r, int n ) { copyNodes ( l[r], n ); }

   // destructor
   ~List () { clear(); delete header; delete trailer; }

   // operator
   T &operator[] ( Rank r ) const; // call by position

   // 辅助函数
   ListNodePosi ( T ) first () const { return header->succ; } // 返回首元素
   ListNodePosi ( T ) last () const { return trailer->pred; }

   // 无序查找
   // 在p的前n个真前驱中寻找等于e的元素（秩最靠后）
   ListNodePosi ( T ) find ( T &e, int n, ListNodePosi ( T ) p ) const;
   // 在p的后n个真后继中寻找等于e的元素（秩最靠前）
   ListNodePosi ( T ) find ( T &e, ListNodePosi ( T ) p, int n ) const;

   // 插入
   ListNodePosi ( T ) insertAsFirst ( T const &e ); // 作为首节点插入
   ListNodePosi ( T ) insertAsLast ( T const &e );
   // e当作p的后继插入
   ListNodePosi ( T ) insertA ( ListNodePosi ( T ) p, T const &e );
   ListNodePosi ( T ) insertB ( ListNodePosi ( T ) p, T const &e );

   // remove
   T remove ( ListNodePosi ( T ) p );
};



/*******************************************************************************
*                               implementation                                *
*******************************************************************************/
template <typename T> void List<T>::init () { // 插入头尾哨兵
   header = new ListNodePosi ( T );
   trailer = new ListNodePosi ( T );
   header->succ = trailer; header->pred = nullptr;
   trailer->pred = header; trailer->succ = nullptr;
   _size = 0; // 头尾节点不在规模中
}

template <typename T> void List<T>::copyNodes ( ListNodePosi ( T ) p, int n ) {
   init();
   while ( n-- > 0 ) { trailer->insertAsPred ( p->data ); p = p->succ; }
}

template <typename T> int List<T>::clear () {
   int oldSize = _size;
   while ( _size > 0 ) { remove ( header->succ ); } // _size 在 remove中自减
   return oldSize;
}

template <typename T>
T List<T>::remove ( ListNodePosi ( T ) p ) {
   T element = p->data;
   p->pred->succ = p->succ;
   p->succ->pred = p->pred;
   delete p; --_size;
   return element;
}

template <typename T> T &List<T>::operator[] ( Rank r ) const {
   ListNodePosi ( T ) node = first ();
   while ( r-- > 0 ) {
      node = node->succ;
   }
   return node->data;
}

// 如果p越界会发生什么?
template <typename T>
ListNodePosi ( T ) List<T>::find ( T &e, int n, ListNodePosi ( T ) p ) const {
   while ( p != header && n-- > 0 ) // ( header, p)
      if ( e == ( p->pred )->data ) { return p; }
   return nullptr;
}

template <typename T>
ListNodePosi ( T ) List<T>::insertAsFirst ( T const &e ) {
   ++_size;
   return header->insertAsSucc ( e );
}

template <typename T>
ListNodePosi ( T ) List<T>::insertAsLast ( T const &e ) {
   ++_size;
   return trailer->insertAsPred ( e );
}

template <typename T>
ListNodePosi ( T ) List<T>::insertA ( ListNodePosi ( T ) p, const T &e ) {
   ++_size;
   return p->insertAsSucc ( e );
}

template <typename T>
ListNodePosi ( T ) List<T>::insertB ( ListNodePosi ( T ) p, const T &e ) {
   ++_size;
   return p->insertAsPred ( e );
}
