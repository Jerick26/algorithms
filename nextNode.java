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
