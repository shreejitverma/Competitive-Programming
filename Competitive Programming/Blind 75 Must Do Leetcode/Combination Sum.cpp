/*
https://leetcode.com/problems/combination-sum/
39. Combination Sum
Medium

7761

186

Add to List

Share
Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.

It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

 

Example 1:

Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.
Example 2:

Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]
Example 3:

Input: candidates = [2], target = 1
Output: []
Example 4:

Input: candidates = [1], target = 1
Output: [[1]]
Example 5:

Input: candidates = [1], target = 2
Output: [[1,1]]
 

Constraints:

1 <= candidates.length <= 30
1 <= candidates[i] <= 200
All elements of candidates are distinct.
1 <= target <= 500
*/

//Runtime: 12 ms, faster than 81.07% of C++ online submissions for Combination Sum.
//Memory Usage: 8.8 MB, less than 100.00% of C++ online submissions for Combination Sum.

class Solution
{
public:
    int tgt;

    void backtrack(vector<vector<int> > &combs, vector<int> &comb, vector<int> &candidates, int start)
    {
        int cursum = accumulate(comb.begin(), comb.end(), 0);
        // cout << "cursum: " << cursum << endl;
        if (cursum > tgt)
        {
        }
        else if (cursum == tgt)
        {
            combs.push_back(comb);
        }
        else
        {
            //we may reuse the last element
            for (int i = max(0, start - 1); i < candidates.size(); i++)
            {
                comb.push_back(candidates[i]);
                // cout << i << endl;
                backtrack(combs, comb, candidates, i + 1);
                comb.pop_back();
            }
        }
    };

    vector<vector<int> > combinationSum(vector<int> &candidates, int target)
    {
        vector<vector<int> > combs;
        vector<int> comb;
        tgt = target;

        backtrack(combs, comb, candidates, 0);

        return combs;
    }
};