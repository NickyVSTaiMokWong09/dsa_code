#ifndef STACK_LIST_H
#define STACK_LIST_H

#include "../list/list.h"

template <typename T> class Stack : public List<T> {
   void push ( const T &e ) { insertAsLast ( e ); }
   T &top () { return this->last()->data;}
   T pop () { return remove ( this->last() ); }
};

#endif /* ifndef STACK_LIST_H */
