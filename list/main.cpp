#include "list.h"

#include <cstdio>
#include <string>

int main() {
   List<std::string> charlist;
   charlist.insertAsLast ( "world" );
   ListNodePosi ( std::string ) tempnode = charlist.insertAsFirst ( "hello" );

   List<std::string> copylist_1 ( charlist );
   List<std::string> copylist_2 ( tempnode, 2 );
   List<std::string> copylist_3 ( charlist, 0, 2 );
   printf ( " Copylist_1[0]: %s\n", copylist_1.first()->data.c_str() );
   printf ( " Copylist_3[1]: %s\n", copylist_3.last()->data.c_str() );

   List<int> ilist;
   ilist.insertAsLast ( 99 );
   ilist.insertAsLast ( 199 );
   printf ( "%d\n", ilist.first()->data );
	funcobj<int> fo;
	ilist.traverse<funcobj<int> >(fo);
   printf ( "%d\n", ilist.first()->data );
}
