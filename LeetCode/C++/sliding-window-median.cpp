// Time:  O(nlogk)
// Space: O(k)

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        multiset<double> min_bst(cbegin(nums), cbegin(nums) + k);
        auto mid = next(cbegin(min_bst), k / 2);
        vector<double> result = {((*mid) + *prev(mid, 1 - k % 2)) / 2};
        for (int i = k; i < size(nums); ++i) {
            min_bst.emplace(nums[i]);
            if (nums[i] < *mid) {
                --mid;
            }
            if (nums[i - k] <= *mid) {
                ++mid;
            }
            min_bst.erase(min_bst.lower_bound(nums[i - k]));
            result.emplace_back(((*mid) + *prev(mid, 1 - k % 2)) / 2);
        }
        return result;
    }
};

// Time:  O(nlogk)
// Space: O(k)
class Solution2 {
public:
vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        multiset<int, less<int>> min_bst;
        multiset<int, greater<int>> max_bst;

        vector<double> result;
        for (int i = 0; i < nums.size(); ++i) {
            if (i >= k) {
                if (max_bst.find(nums[i - k]) != max_bst.cend()) {
                    max_bst.erase(max_bst.find(nums[i - k]));
                } else {
                    min_bst.erase(min_bst.find(nums[i - k]));
                }
            }

            if (max_bst.empty() || nums[i] > *max_bst.cbegin()) {
                min_bst.emplace(nums[i]);
                if (min_bst.size() > max_bst.size() + 1) {
                    max_bst.emplace(*min_bst.cbegin());
                    min_bst.erase(min_bst.cbegin());
                }
            } else {
                max_bst.emplace(nums[i]);
                if (max_bst.size() > min_bst.size()) {
                    min_bst.emplace(*max_bst.cbegin());
                    max_bst.erase(max_bst.cbegin());
                }
            }

            if (i >= k - 1) {
                result.emplace_back(min_bst.size() == max_bst.size() ?
                                 *max_bst.cbegin() / 2.0 + *min_bst.cbegin() / 2.0 : *min_bst.cbegin());
            }
        }

        return result;
    }
};
