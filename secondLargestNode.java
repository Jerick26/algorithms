// Second max in BST

Node rightmost = findRightmostNode(root)
if (rightmost.left != null) {
    return findRightmostNode(rightmost.left)
else{
    return rightmost.parent
}

public static int findSecondLargestValueInBST(Node root)
{
  int secondMax;
  Node pre = root;
  Node cur = root;
  while (cur.Right != null) {
    pre = cur;
    cur = cur.Right;
  }
  if (cur.Left != null) {
    cur = cur.Left;
    while (cur.Right != null)
      cur = cur.Right;
    secondMax = cur.Value;
  } else {
    if (cur == root && pre == root)
      secondMax = int.MinValue;
    else
      secondMax = pre.Value;
  }
  return secondMax;
}
