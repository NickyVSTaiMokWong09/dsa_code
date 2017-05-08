#ifndef QUEUE_LIST
#define QUEUE_LIST

#include "../list/list.h"

template <typename T> class queue : public List<T> {
public:
   void enqueue ( const T &e ) { insertAsLast ( e );}
   T dequeue () { return remove ( this->first() );}
   T &front () { return this->first()->data; }
};

#endif /* ifndef QUEUE_LIST */
