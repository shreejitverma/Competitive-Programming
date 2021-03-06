/*
https://leetcode.com/problems/spiral-matrix/
54. Spiral Matrix
Medium

5348

737

Add to List

Share
Given an m x n matrix, return all elements of the matrix in spiral order.

 

Example 1:


Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]
Example 2:


Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 10
-100 <= matrix[i][j] <= 100
*/

//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Spiral Matrix.
//Memory Usage: 7.2 MB, less than 11.22% of C++ online submissions for Spiral Matrix.
//time: O(m*n), space: O(1)
class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int> > &matrix)
    {
        int m = matrix.size();
        if (m == 0)
            return {};
        int n = matrix[0].size();
        if (n == 0)
            return {};

        /*
        right: {0, 1}
        down : {1, 0}
        left : {0,-1}
        up   : {-1,0}
        */
        vector<int> dirs = {0, 1, 0, -1, 0};
        /*
        right, down, left, top
        */
        vector<int> limits = {n - 1, m - 1, 0, 0};
        int dir = 0;
        vector<int> ans;
        int r = 0, c = 0;
        int k = m * n;

        while (k-- > 0)
        {
            // cout << r << ", " << c << endl;

            ans.push_back(matrix[r][c]);

            if (r + dirs[dir] < limits[3] ||
                r + dirs[dir] > limits[1] ||
                c + dirs[dir + 1] < limits[2] ||
                c + dirs[dir + 1] > limits[0])
            {
                //need to change direction
                limits[(dir + 4 - 1) % 4] += ((dir + 4 - 1) % 4 < 2) ? -1 : 1;
                // cout << "limits[" << (dir+4-1)%4 << "]: " << limits[(dir+4-1)%4] << endl;
                dir = (dir + 1) % 4;
                // cout << "dir: " << dir << endl;
            }

            r += dirs[dir];
            c += dirs[dir + 1];
        }

        return ans;
    }
};

//Approach 2: Layer-by-Layer
//cleaner
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Spiral Matrix.
//Memory Usage: 7.2 MB, less than 11.22% of C++ online submissions for Spiral Matrix.
//time: O(m*n), space: O(1)
class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int> > &matrix)
    {
        int m = matrix.size();
        if (m == 0)
            return {};
        int n = matrix[0].size();
        if (n == 0)
            return {};

        int r1 = 0, r2 = m - 1, c1 = 0, c2 = n - 1;
        vector<int> ans;

        while (r1 <= r2 && c1 <= c2)
        {
            //iterate through one layer
            for (int c = c1; c <= c2; ++c)
                ans.push_back(matrix[r1][c]);
            for (int r = r1 + 1; r <= r2; ++r)
                ans.push_back(matrix[r][c2]);
            if (r1 < r2 && c1 < c2)
            {
                //if this layer is not one row or one column
                for (int c = c2 - 1; c >= c1; --c)
                    ans.push_back(matrix[r2][c]);
                for (int r = r2 - 1; r >= r1 + 1; --r)
                    ans.push_back(matrix[r][c1]);
            }

            ++r1;
            --r2;
            ++c1;
            --c2;
        }

        return ans;
    }
};