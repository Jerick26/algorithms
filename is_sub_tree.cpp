
class Node {
  int val;
  Node *left, *right;
  Node(int val) : this->val(val), left(NULL), right(NULL)
  {}
};

bool areIdentical(Node* r1, Node* r2) {
  if (r1 == NULL && r2 == NULL)
    return true;
  if (r1 == NULL || r2 == NULL)
    return false;
  return (r1->data == r2->data
          && areIdentical(r1->left, r2->left)
          && areIdentical(r1->right, r2->right));
}

bool isSubtree(Node* s, Node* t) {
  if (t == NULL)
    return true;
  if (s == NULL)
    return false;
  if (areIdentical(s, t))
    return true;
  return (isSubtree(s.left, t)
          || isSubtree(s.right, t));
}
