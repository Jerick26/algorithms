// Second max in BST

Node rightmost = findRightmostNode(root)
if (rightmost.left != null) {
    return findRightmostNode(rightmost.left)
else{
    return rightmost.parent
}
