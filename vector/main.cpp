#include "vector.h"
#include <cstdio>

int main ( int argc, char *argv[] ) {
   Vector<int> a;

   int *b = new int[10];
   Vector<int> c ( b, 10 );
   Vector<int> d ( b, 2, 5 );
   delete[] b;

   Vector<int> bi ( a );
   Vector<int> ci ( a, 0, 2 );

   a.unsort ( 3,5 );

   b[0] = 999;
   b[1] = 888;
   b[2] = 444;
   Vector<int> test_find ( b, 0, 3 );
   printf ( "find1   %d\n", test_find.find ( 222, 0, test_find.size() ) );
   printf ( "find2   %d\n", test_find.find ( 222 ) );

   test_find.insert ( 1,777 );
   printf ( "find3   %d\n", test_find.find ( 444, 0, test_find.size() ) );
   printf ( "find4   %d\n", test_find.find ( 777, 0, test_find.size() ) );

   /****************************************************************************
   *                              test traverse                               *
   ****************************************************************************/
	increase<int> ( test_find );
   printf ( "find4   %d\n", test_find.find ( 778, 0, test_find.size() ) );

   return 0;
}
