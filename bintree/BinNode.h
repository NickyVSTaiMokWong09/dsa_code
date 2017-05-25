#ifndef BINTREE_BINNODE_H
#define BINTREE_BINNODE_H

/*******************************************************************************
*                                  二叉树节点模版类                            *
*******************************************************************************/
#define BinNodePosi(T) BinNode<T>*
typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T> class BinNode {
public:
   /* 数据区
    * npl 和 color 在树的其他形式里使用
    * data, parent(父节点), lc = leftChild(左子), rc, heigth(高度)，通用、基本参数*/
   T data;
   BinNodePosi ( T ) parent; BinNodePosi ( T ) lc; BinNodePosi ( T ) rc;
   int height;
   int npl; 		// Null Path Length
   RBColor color; // 颜色（红黑树)

   /* 构造函数
    * TODO 优化构造函数(委托构造)
    * */
   BinNode () :
      parent ( nullptr ), lc ( nullptr ), rc ( nullptr ), height ( 0 ),
      npl ( 1 ), color ( RB_RED ) { }
   BinNode ( T e, BinNodePosi ( T ) p = nullptr,
             BinNodePosi ( T ) lc = nullptr, BinNodePosi ( T ) rc = nullptr,
             int h = 0, int npl = 1, RBColor c = RB_RED ) :
      data ( e ), parent ( p ), lc ( lc ), rc ( rc ), height ( h ),
      npl ( npl ),color ( c ) { }

   /* 操作接口区 */
   int size ();
   BinNodePosi ( T ) insertAsLC ( T const & );
   BinNodePosi ( T ) insertAsRC ( T const & );
   BinNodePosi ( T ) succ();

   /* 比较器、判等器 */
   bool operator< ( BinNode const &bn ) { return data<bn.data; }
   // 检查操作接口
   bool IsRoot ( BinNode const &bn );
};

/*******************************************************************************
*                               implementation                                *
*******************************************************************************/

template <typename T>
inline bool BinNode<T>::IsRoot ( BinNode const &bn ) {
   return bn.parent == nullptr ? true : false;
}

template <typename T>
BinNodePosi ( T ) BinNode<T>::insertAsLC ( T const &e ) {
   return lc = new BinNode ( e, this );
}

template <typename T>
BinNodePosi ( T ) BinNode<T>::insertAsRC ( T const &e ) {
   return rc = new BinNode ( e, this );
}

#endif /* ifndef BINTREE_BINNODE_H */
