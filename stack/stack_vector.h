#ifndef STACK_VECTOR_H
#define STACK_VECTOR_H

#include "../vector/vector.h"

template <typename T> class Stack : public Vector<T> {
public:
   void push ( T const &e ) { insert ( this->size(), e ); }
   T pop () { return remove ( this->size() - 1 ); }
   T &top () { return ( *this ) [this->size() - 1]; }
};

#endif /* ifndef STACK_VECTOR_H */
