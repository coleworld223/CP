
// Find Last Character
// You are given an alphanumeric string S and an integer K. Consider a new string in which S is appended K-1 times. Now, in this new string, the following operations are performed:-

// Every alternate character starting from the first character is removed.
// Every alternate character starting from the last character is removed.
// The above two operations are repeated until one character remains. Your task is to find and return a string representing the last remaining character after performing all the operations.

// Note: Here, alphanumeric refers to the string that may contain alphabets (a-z and A-Z), numerals (0-9), and certain special characters such as '$', '#', '&', and '*'

// Input Specification:

// input1: A string S, representing the alphanumeric string.
// input2: An integer value K.

// Output Specification:

// Return a string representing the last remaining character after performing all the operations mentioned.

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

int reduce(int start, int end, int gaps, int turn) {
    if (start == end) return start;
    if (turn == 0) {
        int f = start + gaps;
        int l = (((end - start) / gaps) % 2 == 1 ? end : end - gaps);
        return reduce(f, l, 2 * gaps, 1 - turn);
    }
    else {
        int l = end - gaps;
        int f = (((end - start) / gaps) % 2 == 1 ? start : start + gaps);
        return reduce(f, l, 2 * gaps, 1 - turn);
    }
    return -1;
}

string solve(string s, int k) {
    int n = s.size();
    int l = (n * k);
    int ans = reduce(1, l, 1, 0);
    ans--;
    ans %= n;
    string res;
    res.push_back(s[ans]);
    return res;
}

int main() {
    string s;
    cin >> s;
    int k;
    cin >> k;

    cout << solve(s, k) << '\n';
}
