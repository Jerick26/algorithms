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
