class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        multiset <int> st;
        vector <int> res;
        int n = nums.size();

        for (int i = 0, j = 0; j < n; j += 1) {
            st.insert (nums[j]);
            while (j - i + 1 > k) {
                st.erase (st.find (nums[i++]));
            }
            if (j - i + 1 == k) {
                int mx = (*prev(st.end()));
                int mn = (*begin(st));
                res.push_back(mx);
            }
        }
        return res;
    }
};