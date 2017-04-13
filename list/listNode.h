typedef int Rank;
#define ListNodePosi(T) ListNode<T>*

template <typename T> class ListNode {
public:
   // Data member
   T data; ListNodePosi ( T ) pred; ListNodePosi ( T ) succ;
   // constructor
   ListNode ( T e, ListNodePosi ( T ) p, ListNodePosi ( T ) s )
      : data ( e ), pred ( p ), succ ( s ) {} // default constructor
   ListNode () {} // for header and trailer
   // operation
   ListNodePosi ( T ) insertAsPred ( T const &e );
   ListNodePosi ( T ) insertAsSucc ( T const &e );
};
