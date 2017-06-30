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
 * In any binary tree
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
