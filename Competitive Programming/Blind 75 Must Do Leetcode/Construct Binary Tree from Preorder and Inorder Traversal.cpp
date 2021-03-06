/*
https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
105. Construct Binary Tree from Preorder and Inorder Traversal
Medium

6751

171

Add to List

Share
Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.

 

Example 1:


Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]
Example 2:

Input: preorder = [-1], inorder = [-1]
Output: [-1]
 

Constraints:

1 <= preorder.length <= 3000
inorder.length == preorder.length
-3000 <= preorder[i], inorder[i] <= 3000
preorder and inorder consist of unique values.
Each value of inorder also appears in preorder.
preorder is guaranteed to be the preorder traversal of the tree.
inorder is guaranteed to be the inorder traversal of the tree.
*/

//recursion
//Runtime: 76 ms, faster than 12.67% of C++ online submissions for Construct Binary Tree from Preorder and Inorder Traversal.
//Memory Usage: 75.4 MB, less than 5.21% of C++ online submissions for Construct Binary Tree from Preorder and Inorder Traversal.
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        if (preorder.empty())
            return nullptr;

        TreeNode *root = new TreeNode(preorder[0]);

        int split = find(inorder.begin(), inorder.end(), preorder[0]) - inorder.begin();

        vector<int> linorder(inorder.begin(), inorder.begin() + split);
        vector<int> lpreorder(preorder.begin() + 1, preorder.begin() + 1 + linorder.size());
        root->left = buildTree(lpreorder, linorder);

        vector<int> rpreorder(preorder.begin() + 1 + linorder.size(), preorder.end());
        vector<int> rinorder(inorder.begin() + split + 1, inorder.end());
        root->right = buildTree(rpreorder, rinorder);

        return root;
    }
};

//recursion
//use index as argument to avoid copy the whole vector
//use hashmap to record "split" values
//https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/discuss/34538/My-Accepted-Java-Solution
//Runtime: 24 ms, faster than 77.75% of C++ online submissions for Construct Binary Tree from Preorder and Inorder Traversal.
//Memory Usage: 26.9 MB, less than 5.10% of C++ online submissions for Construct Binary Tree from Preorder and Inorder Traversal.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
public:
    unordered_map<int, int> inorder_indices;

    TreeNode *buildTree(vector<int> &preorder, int prestart, int preend,
                        vector<int> &inorder, int instart, int inend)
    {
        //[prestart, preend], [inorder, inend] are inclusive
        if (prestart > preend)
            return nullptr;

        TreeNode *root = new TreeNode(preorder[prestart]);

        // int split = find(inorder.begin()+instart,
        //     inorder.begin()+inend+1, root->val)-inorder.begin();
        int split = inorder_indices[root->val];
        int left_size = split - instart;

        root->left = buildTree(preorder, prestart + 1, prestart + 1 + left_size - 1,
                               inorder, instart, split - 1);

        root->right = buildTree(preorder, prestart + left_size + 1, preend,
                                inorder, split + 1, inend);

        return root;
    }

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        int n = preorder.size();

        for (int i = 0; i < n; ++i)
        {
            inorder_indices[inorder[i]] = i;
        }

        return buildTree(preorder, 0, n - 1, inorder, 0, n - 1);
    }
};