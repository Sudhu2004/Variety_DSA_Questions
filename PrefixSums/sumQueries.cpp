// https://cses.fi/problemset/task/1646
#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for(int i=0 ;i<n ;i++) cin >> arr[i];

    for(int i=1 ;i<n ;i++) {
        arr[i] += arr[i-1];
    }

    for(int i=0 ;i<q ;i++) {
        int a , b;
        cin >> a >> b;
        a -= 1;
        b -= 1;
        int psum1 = 0, psum2 = 0;

        psum2 = arr[b];
        if(a-1 >= 0) {
            psum1 = arr[a-1];
        }
        int ans = psum2 - psum1;
        cout << ans << endl;
    }

    return 0;
}