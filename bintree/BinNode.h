#ifndef BINTREE_BINNODE_H
#define BINTREE_BINNODE_H

/*******************************************************************************
*                                  二叉树节点模版类                            *
*******************************************************************************/
#define BinNodePosi(T) BinNode<T>*
#define stature(p) ( (p) ? (p)->height : -1 )
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

   // Constructor
   BinNode ()
      : parent ( nullptr ), lc ( nullptr ), rc ( nullptr ),
        height ( 0 ), npl ( 1 ), color ( RB_RED ) { }
   BinNode ( T e, BinNodePosi ( T ) p = nullptr,
             BinNodePosi ( T ) lc = nullptr, BinNodePosi ( T ) rc = nullptr,
             int h = 0, int npl = 1, RBColor c = RB_RED )
      : data ( e ), parent ( p ),
        lc ( lc ), rc ( rc ), height ( h ), npl ( npl ),color ( c ) { }

   // Capacity
   int size ();

   // Modifiers
   BinNodePosi ( T ) insertAsLC ( T const & );
   BinNodePosi ( T ) insertAsRC ( T const & );

   // Lookup
   BinNodePosi ( T ) succ();

   /* 比较器、判等器 */
   bool operator< ( BinNode const &bn ) { return data < bn.data; }
};

/*******************************************************************************
*                               implementation                                *
*******************************************************************************/

template <typename T>
BinNodePosi ( T ) BinNode<T>::insertAsLC ( T const &e ) {
   return lc = new BinNode ( e, this );
}

template <typename T>
BinNodePosi ( T ) BinNode<T>::insertAsRC ( T const &e ) {
   return rc = new BinNode ( e, this );
}

/*******************************************************************************
*                               BinNode 状态与性质判断                               *
*******************************************************************************/

#define IsRoot(x) ( !( (x).parent ))

#endif /* ifndef BINTREE_BINNODE_H */
