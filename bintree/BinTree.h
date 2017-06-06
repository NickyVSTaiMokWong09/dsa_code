#ifndef BINTREE_BINTREE_H
#define BINTREE_BINTREE_H

#include "BinNode.h"

template <typename T> class BinTree {
protected:
   // Data
   int _size; BinNodePosi ( T ) _root;

   // Modifiers
   virtual int updateHeight ( BinNodePosi ( T ) x );
   void updateHeightAbove ( BinNodePosi ( T ) x );
public:
   // Constructor
   BinTree() : _size ( 0 ), _root ( nullptr ) { }

   // Destructor
   ~BinTree() { if ( 0 < _size ) remove ( _root ); }

   // Modifiers
   int remove ( BinNodePosi ( T ) x );
   BinNodePosi ( T ) insertAsRoot ( T const &e );
   BinNodePosi ( T ) insertAsLC ( BinNodePosi ( T ) x, T const &e );
   BinNodePosi ( T ) insertAsRC ( BinNodePosi ( T ) x, T const &e );

   // Capacity
   int size() const { return _size; }
   bool empty() const { return !_root; }

   // Element access
   BinNodePosi ( T ) root() const { return _root; }

   // Operations
   template <typename VST> void traveLevel ( VST &visit );

   // Compare Operator
   bool operator== ( BinTree<T> const &t );
};

/*******************************************************************************
*                               implementation                                *
*******************************************************************************/

// protected Modifiers
// TODO 5.3, 5.4
template <typename T>
int BinTree<T>::updateHeight ( BinNodePosi ( T ) x )
{ return x->height = 1 + max ( stature ( x->lc ), stature ( x->rc ) ); }

template <typename T>
void BinTree<T>::updateHeightAbove ( BinNodePosi ( T ) x )
{ while ( x ) { updateHeight ( x ); x = x->parent; } }

// Public Modifiers
template <typename T>
BinNodePosi ( T ) BinTree<T>::insertAsRoot ( const T &e )
{ _size = 1; _root = new BinNode<T> ( e ); }

template <typename T>
BinNodePosi ( T ) BinTree<T>::insertAsLC ( BinNodePosi ( T ) x, const T &e )
{ _size ++; x->insertAsLC ( e ); updateHeightAbove ( x ); return x->lc; }

template <typename T>
BinNodePosi ( T ) BinTree<T>::insertAsRC ( BinNodePosi ( T ) x, const T &e )
{ _size ++; x->insertAsRC ( e ); updateHeightAbove ( x ); return x->rc; }

#endif /* ifndef BINTREE_BINTREE_H */
