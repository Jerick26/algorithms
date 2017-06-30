/**
 *  Return the Least Common Ancestor (LCA) of Nodes with values a and b
 *  in Binary Search Tree
 */
Node* commonAncestor(Node* root, int a, int b)
{
    // case when LCA doesn't exist
    if(root == NULL || root->data == a || root->data == b)
        return NULL; 
    if( (root->data > a && root->data < b) || (root->data > b && root->data < a) )
        return root;
    // LCA will be on the LEFT sub-tree
    if(root->data > a && root->data > b)
        return commonAncestor(root->lptr, a, b);
    // LCA will be on the RIGHT sub-tree
    if(root->data < a && root->data < b)
        return commonAncestor(root->rptr, a, b);
}

/**
 * Method 1:
 * in Binary Tree
 *
 */
 // Finds the path from root node to given root of the tree, Stores the
// path in a vector path[], returns true if path exists otherwise false
bool findPath(Node *root, vector<int> &path, int k)
{
    // base case
    if (root == NULL) return false;

    // Store this node in path vector. The node will be removed if
    // not in path from root to k
    path.push_back(root->key);

    // See if the k is same as root's key
    if (root->key == k)
        return true;

    // Check if k is found in left or right sub-tree
    if ( (root->left && findPath(root->left, path, k)) ||
         (root->right && findPath(root->right, path, k)) )
        return true;

    // If not present in subtree rooted with root, remove root from
    // path[] and return false
    path.pop_back();
    return false;
}

// Returns LCA if node n1, n2 are present in the given binary tree,
// otherwise return -1
int findLCA(Node *root, int n1, int n2)
{
    // to store paths to n1 and n2 from the root
    vector<int> path1, path2;

    // Find paths from root to n1 and root to n1. If either n1 or n2
    // is not present, return -1
    if ( !findPath(root, path1, n1) || !findPath(root, path2, n2))
          return -1;

    /* Compare the paths to get the first different value */
    int i;
    for (i = 0; i < path1.size() && i < path2.size() ; i++)
        if (path1[i] != path2[i])
            break;
    return path1[i-1];
}

/**
 * Method 2.
 *
 */
public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
    if (root == null) {
       return null;
    }

    // If the root is one of a or b, then it is the LCA
    if (root == p || root == q) {
        return root;
    }

    TreeNode left = lowestCommonAncestor(root.left, p, q);
    TreeNode right = lowestCommonAncestor(root.right, p, q);

    // If both nodes lie in left or right then their LCA is in left or right,
    // Otherwise root is their LCA
    if (left != null && right != null) {
        return root;
    }

    return (left != null) ? left : right;
}
