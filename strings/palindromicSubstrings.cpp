// Oracle QA Question: Unfinished
#include <bits/stdc++.h>

using namespace std;

// Function to check if a string is a palindrome
bool isPalin(const string& str) {
    int left = 0, right = str.size() - 1;
    while (left < right) {
        if (str[left] != str[right]) return false;
        left++;
        right--;
    }
    return true;
}

// Comparator to sort in descending order
bool static comp(int val1, int val2) {
    return val1 > val2;
}

int getAns(vector<string>& arr, int n) {
    int cnt = 0;  // Count of palindromes
    unordered_map<int, int> freq;  // Frequency of characters across non-palindromic strings
    vector<int> reqSizes;  // Stores the sizes of non-palindromic strings

    // Step 1: Identify palindromes and calculate frequencies of characters for non-palindromes
    for (auto& s : arr) {
        if (isPalin(s)) {
            cnt++;  // Already a palindrome
        } else {
            // Count character frequencies for non-palindromic strings
            for (char ch : s) {
                freq[ch - 'a']++;
            }
            reqSizes.push_back(s.size());
        }
    }

    int oddStrs = 0;  // Number of non-palindromic strings with odd lengths
    int m = reqSizes.size();  // Number of non-palindromic strings
    sort(reqSizes.begin(), reqSizes.end(), comp);  // Sort sizes in descending order

    for (auto size : reqSizes) {
        if (size % 2 != 0) oddStrs++;
    }

    // Step 2: Handle case when there are no odd-length strings
    if (oddStrs == 0) {
        int oddChrs = 0;
        // Count characters with odd frequencies
        for (auto it : freq) {
            if (it.second % 2 != 0) oddChrs++;
        }

        // If no odd frequency characters, all non-palindromes can be turned into palindromes
        if (oddChrs == 0) return m + cnt;

        // Try to balance the odd frequency characters by reducing them with string sizes
        int i = 0;
        for (i = 0; i < m; i++) {
            oddChrs -= reqSizes[i];
            if (oddChrs <= 0) break;
        }
        return cnt + (m - (i + 1));
    } else {
        // Step 3: Handle odd-length strings
        int oddChrs = 0;
        // Count characters with odd frequencies
        for (auto it : freq) {
            if (it.second % 2 != 0) oddChrs++;
        }

        // Allow one odd frequency character per odd-length string
        int minOddChars = min(oddStrs, oddChrs);
        oddChrs -= minOddChars;

        // Now try to balance the remaining odd frequency characters with the sizes of even-length strings
        int i = 0;
        for (i = 0; i < m && oddChrs > 0; i++) {
            if (reqSizes[i] % 2 == 0) {  // Only consider even-sized strings for balancing
                oddChrs -= reqSizes[i];
            }
        }

        // The result is the count of palindromes plus the remaining non-palindromes
        return cnt + (m - (i + 1));
    }

    return cnt;  // Return the total count of palindromes
}

int main() {
    int n;
    cin >> n;
    vector<string> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << getAns(arr, n) << endl;

    return 0;
}
