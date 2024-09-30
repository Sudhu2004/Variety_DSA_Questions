#include<bits/stdc++.h>
#define ll long long
#define cel(n, k) ((n - 1)/k + 1);
using namespace std;

const ll MOD = 9 + 1e9;

bool check(ll x,ll n, ll m, ll k) {
    ll dist = k - 1;
    ll used = x + cel(x, dist); // to make blocks of k-1 with cont 1s
    ll need = m - x; // remaining correct answers required
    ll rem = n - used; // unused space yet to fill out

    // if there is space to fill out the needed then true is returned
    // else false;
    return rem >= need; 
}

ll exp(ll b, ll p) {
    ll ans = 1;

    while(p) {
        if(p&1) {
            ans =(ans * b)%MOD;a
        }
        b = (b * b) % MOD;
        p /= 2; 
    }

    return (ans-2+MOD)%MOD;
}
int main() {
    ll n, m, k;
    cin >> n >> m >> k;

    ll low = 0, high = m;

    while(low < high) {
        ll mid = (low + high + 1) /2LL;

        if(check(mid, n, m, k)) {
            low = mid;
        }
        else {
            high = mid - 1;
        }
    }
    // cout << low << endl;
    ll cont = m - low;
    // cout << cont << endl;

    ll ans = (k * exp(2, cont/k + 1) + low + cont%k)%MOD;
    cout << ans << endl;
    return 0;
}