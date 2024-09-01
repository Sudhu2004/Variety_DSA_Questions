// https://www.codechef.com/CENS2020/problems/CENS20A
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void findSwitch(int n, int m, vector<vector<int>>& matrix, vector<pair<pair<int, int>, pair<int, int>>>& queries) {
    // Create a Different vector because the previous values of 
    // matrix might alter the result
    vector<vector<int>> diff(n, vector<int>(m, 0));

    // Increment cells (x1, y1) & (x2+1, y2+1) 
    // Decrement cells (x1, y2+1) & (x2+1, y1)
   
    for (auto it : queries) {
        int x1 = it.first.first - 1;
        int y1 = it.first.second - 1;
        int x2 = it.second.first - 1;
        int y2 = it.second.second - 1;
        
        diff[x1][y1]++;
        if (y2 + 1 < m) {
            diff[x1][y2 + 1]--;
        }
        if (x2 + 1 < n) {
            diff[x2 + 1][y1]--;
        }
        if (x2 + 1 < n && y2 + 1 < m) {
            diff[x2 + 1][y2 + 1]++;
        }
    }

    // perform prefix sums horizontally for each row
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            diff[i][j] += diff[i][j - 1];
        }
    }

    // perform prefix sums vertically for each row
    for (int j = 0; j < m; ++j) {
        for (int i = 1; i < n; ++i) {
            diff[i][j] += diff[i - 1][j];
        }
    }

    // Add the resultant to the original matrix , if the sum is divisible,
    // then it is OFF else ON
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = (matrix[i][j] + diff[i][j]) % 2;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> matrix(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        string line;
        cin >> line;
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = line[j] - '0';
        }
    }

    int q;
    cin >> q;
    
    vector<pair<pair<int, int>, pair<int, int>>> queries(q);
    for (int i = 0; i < q; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        queries[i] = {{x1, y1}, {x2, y2}};
    }
    
    findSwitch(n, m, matrix, queries);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << matrix[i][j];
        }
        cout << endl;
    }

    return 0;
}
