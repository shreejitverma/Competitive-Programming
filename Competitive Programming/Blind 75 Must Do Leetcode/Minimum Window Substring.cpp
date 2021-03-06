/*
https://leetcode.com/problems/minimum-window-substring/
76. Minimum Window Substring
Hard

8394

497

Add to List

Share
Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.

A substring is a contiguous sequence of characters within the string.

 

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
Example 2:

Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.
Example 3:

Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.
 

Constraints:

m == s.length
n == t.length
1 <= m, n <= 105
s and t consist of uppercase and lowercase English letters.
 

Follow up: Could you find an algorithm that runs in O(m + n) time?
*/

//TLE
//267 / 268 test cases passed.
class Solution
{
public:
    bool isValid(map<char, int> &m1, map<char, int> &m2)
    {
        //m1 is base, return true if m2 >= m1
        for (auto it = m1.begin(); it != m1.end(); it++)
        {
            if (m2.find(it->first) == m2.end() ||
                m1[it->first] > m2[it->first])
            {
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t)
    {
        int l = 0, r = 0;
        int minLen = INT_MAX;
        string minStr;
        map<char, int> tCount, curCount;

        for (int i = 0; i < t.size(); i++)
        {
            tCount[t[i]]++;
        }

        //window is initially [0...0]
        curCount[s[l]]++;
        while (r < s.size())
        {
            // cout << s.substr(l, r-l+1) << endl;
            //move forward r until curCount >= tCount
            if (!isValid(tCount, curCount))
            {
                r++;
                //update curCount
                curCount[s[r]]++;
            }
            else
            {
                // cout << "found" << endl;
                if (r - l + 1 < minLen)
                {
                    minLen = r - l + 1;
                    minStr = s.substr(l, r - l + 1);
                }

                //s[l] is discarded
                curCount[s[l]]--;
                //move forward l
                l++;
            }
        }

        return minStr;
    }
};

//Approach 1: Sliding Window, improve efficiency to determine if a window is valid
//Runtime: 116 ms, faster than 11.76% of C++ online submissions for Minimum Window Substring.
//Memory Usage: 16.7 MB, less than 32.00% of C++ online submissions for Minimum Window Substring.
//time: O(|S|+|T|), space: O(|S|+|T|)
class Solution
{
public:
    string minWindow(string s, string t)
    {
        if (s.size() == 0 || t.size() == 0)
            return "";

        int l = 0, r = 0;
        int minLen = INT_MAX;
        string minStr;
        map<char, int> tCount, curCount;

        for (int i = 0; i < t.size(); i++)
        {
            tCount[t[i]]++;
        }

        //#unique char in t
        int required = tCount.size();
        //#unique char required in s
        int possessed = 0;

        //window is initially [0...0]
        while (r < s.size())
        {
            //meet new char, update our data structure
            curCount[s[r]]++;

            // cout << s.substr(l, r-l+1) << endl;
            if ((tCount.find(s[r]) != tCount.end()) &&
                curCount[s[r]] == tCount[s[r]])
            {
                //we have just collected enough char of s[r]
                possessed++;
            }

            //try contract windows size
            while ((possessed == required) && (l <= r))
            {
                // cout << "found" << endl;
                if (r - l + 1 < minLen)
                {
                    minLen = r - l + 1;
                    minStr = s.substr(l, r - l + 1);
                }

                //s[l] is discarded
                curCount[s[l]]--;
                if (tCount.find(s[l]) != tCount.end() && curCount[s[l]] == tCount[s[l]] - 1)
                {
                    /*
                    the char count of s[l] is just deduced,
                    and not enough to form t
                    */
                    possessed--;
                }
                //move forward l
                l++;
            }

            r++;
        }

        return minStr;
    }
};

//Approach 2: Optimized Sliding Window, further optimized by filter unrelated char from s first
//Runtime: 144 ms, faster than 8.96% of C++ online submissions for Minimum Window Substring.
//Memory Usage: 18.9 MB, less than 20.00% of C++ online submissions for Minimum Window Substring.
//time: O(|S|+|T|), space: O(|S|+|T|)
class Solution
{
public:
    string minWindow(string s, string t)
    {
        if (s.size() == 0 || t.size() == 0)
            return "";

        int l = 0, r = 0;
        int minLen = INT_MAX;
        string minStr;
        map<char, int> tCount, curCount;

        for (int i = 0; i < t.size(); i++)
        {
            tCount[t[i]]++;
        }

        //filteredS contains only the char in t
        vector<pair<int, char> > filteredS;
        for (int i = 0; i < s.size(); i++)
        {
            if (tCount.find(s[i]) != tCount.end())
            {
                filteredS.push_back(make_pair(i, s[i]));
            }
        }

        //#unique char in t
        int required = tCount.size();
        //#unique char required in s
        int possessed = 0;

        //window is initially [0...0]
        //now we iterate through filteredS
        while (r < filteredS.size())
        {
            int end = filteredS[r].first;
            char c = filteredS[r].second;

            //meet new char, update our data structure
            curCount[c]++;

            // cout << s.substr(l, r-l+1) << endl;
            if ((tCount.find(c) != tCount.end()) &&
                curCount[c] == tCount[c])
            {
                //we have just collected enough char of c
                possessed++;
            }

            //try contract windows size
            while ((possessed == required) && (l <= r))
            {
                char c = filteredS[l].second;
                int start = filteredS[l].first;

                // cout << "found" << endl;
                if (end - start + 1 < minLen)
                {
                    //we use l, r to index filteredS
                    //, and use start, end to index s
                    minLen = end - start + 1;
                    minStr = s.substr(start, end - start + 1);
                }

                //s[l] is discarded
                curCount[c]--;
                if (tCount.find(c) != tCount.end() && curCount[c] == tCount[c] - 1)
                {
                    /*
                    the char count of s[l] is just deduced,
                    and not enough to form t
                    */
                    possessed--;
                }
                //move forward l
                l++;
            }

            r++;
        }

        return minStr;
    }
};