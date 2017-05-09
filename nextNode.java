// solution a
public static TreeNode findSuccessor(TreeNode node)
{
  if (node == null)
    return null;
  
  if (node.getRight() != null)
    return findMinimum(node.getRight());
  
  TreeNode y = node.getParent();
  TreeNode x = node;
  while (y != null && x == y.getRight())
  {
    x = y;
    y = y.getParent();
  }
  // Intuition: as we traverse left up the tree we traverse smaller values
  // The first node on the right is the next larger number
  return y;
}

// 
public static TreeNode findPredecessor(TreeNode node)
{
  if (node == null)
    return null;
  if (node.getLeft() != null)
    return findMaximum(node.getLeft());
  TreeNode parent = node.getParent();
  TreeNode y = parent;
  TreeNode x = node;
  while (y != null && x == y.getLeft()) {
    x = y;
    y = y.getParent();
  }
  return y;
}

// solution b
Node nextNode(Node node) {
  if ( node == null ) { return null; }
  if ( node.right != null ) {
    node = node.right;
    while ( node.left != null) {
      node = node.left;
    }
    return node;
  } else {
    if ( node.parent == null) { // for root node parent  == null;
      return null;
    } else if ( node.parent.left == node) { // it is parent's left node.
      return node;
    } else {
      // node is the right child of parent and it has no right child.
      Node currNode = node;
      while ( node.parent != null ){ // current node is not root
        node = node.parent;
        if ( node.val > currNode.val) {
          return node;
        }
      }
      return null;
    }
  }
}
