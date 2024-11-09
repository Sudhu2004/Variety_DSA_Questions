// Question Asked during Booking Holding Hackerrank OA
// Given a number of strings in a vector, find the number of distinct subsequences
// formed such that each indices are unique wrt to their character in the string
// so that they form the target t
// Ex:
// Input:
// arr = valya lyglb vldoh
// target = val
// Output: 4
#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> memo;

int f(int i, int j, int k, vector<string>& words, string& target) {
    if(j == target.size()) return 1;
    if(i == words.size() || k == words[i].size()) return 0;

    // Memoization key
    string key = to_string(i) + "," + to_string(j) + "," + to_string(k);
    if(memo.find(key) != memo.end()) return memo[key];

    int count = 0;
    if(words[i][k] == target[j]) {
        count += f(i, j + 1, k + 1, words, target);
        count += f(i + 1, j + 1, 0, words, target);
    } else {
        count += f(i, j, k + 1, words, target);
        count += f(i + 1, j, 0, words, target);
    }

    memo[key] = count;
    return count;
}

int getAns(vector<string>& words, string& target) {
    
    return f(0, 0, 0, words, target);
}

int main() {
    string line;
    string target;

    // Read words as a single line and split into vector
    getline(cin, line);
    vector<string> words;
    istringstream seq(line);
    string word;
    while(seq >> word) {
        words.push_back(word);
    }

    // Read the target string
    getline(cin, target);

    cout << getAns(words, target) << endl;
    return 0;
}
