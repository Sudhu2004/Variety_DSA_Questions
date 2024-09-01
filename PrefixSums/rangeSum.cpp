// https://www.hackerrank.com/contests/ab-yeh-kar-ke-dikhao/challenges/kj-and-street-lights/problem

#include<iostream>
#include<vector>

using namespace std;

int findBlackSpots(int end, vector<pair<int,int>>& lights) {

    vector<int> arr(end+1, 0);

    for(auto it: lights) {
        int x = it.first;
        int r = it.second;
        
        if(x-r < 0) arr[0]++;
        else arr[x-r]++;

        if(x+r+1 <= end) arr[x+r+1]--;
    }

    for(int i=1 ;i<=end; i++) {
        arr[i] += arr[i-1];
    }

    for(int i=0 ;i<=end ;i++) {
        if(arr[i] > 1) arr[i] = 0;
    }

    int tempLength = 0, ans = 0;
    // cout << "ARR: " << endl;
    for(int i=0 ;i<= end; i++) {
        // cout << arr[i] << " ";
        if(arr[i] == 0) {
            tempLength++;
            ans = max(ans, tempLength);
        }
        else {
            tempLength = 0;
        }
    }
    // cout << endl;

    return ans;
}
int main() {

    int end, q;
    cin >> q >> end;
    vector<pair<int,int>> lights;

    for(int i=0 ;i<q ;i++) {
        int a, b;
        cin >> a >> b;
        lights.push_back({a, b});
    }

    cout << findBlackSpots(end, lights) << endl;;
    return 0;
}