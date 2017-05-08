#ifndef QUEUE_VECTOR
#define QUEUE_VECTOR

#include "../vector/vector.h"
template <typename T> class Queue : public Vector<T> {
public:
   void enqueue ( const T &e ) { insert ( this->size(), e ); }
   T dequeue () { return remove ( 0 );}
   T &front () { return ( *this ) [0]; }
};

#endif /* ifndef QUEUE_VECTOR */
