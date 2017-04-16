#include <cstddef>

typedef int Rank;
#define ListNodePosi(T) ListNode<T>* // 文本宏替换

template <typename T> class ListNode {
public:
   // Data member
   T data; ListNodePosi ( T ) pred; ListNodePosi ( T ) succ; // 数据区，前驱，后继
   // constructor
   ListNode ( T e, ListNodePosi ( T ) p = nullptr, ListNodePosi ( T ) s = nullptr )
      : data ( e ), pred ( p ), succ ( s ) {} // default constructor
   ListNode () {} // for header and trailer
   // operation
   ListNodePosi ( T ) insertAsPred ( T const &e );
   ListNodePosi ( T ) insertAsSucc ( T const &e );
};

/*******************************************************************************
*                               implementation                                *
*******************************************************************************/
template <typename T> ListNodePosi ( T ) ListNode<T>::insertAsPred ( T const &e ) {
   // new 退出作用域之后 还存在
   ListNodePosi ( T ) node = new ListNode ( e, this->pred, this );
   pred->succ = node; pred = node; // 先设置前驱的后继，再设置后继的前驱
   return node;
}

template <typename T> ListNodePosi ( T ) ListNode<T>::insertAsSucc ( T const &e ) {
   ListNodePosi ( T ) node = new ListNode ( e, this, this->succ );
   succ->pred = node; succ = node;
   return node;
}
