// https://www.geeksforgeeks.org/problems/nth-natural-number/1
#include<iostream>
#include<bits/stdc++.h>
#define ll long long

using namespace std;

ll findNth(ll n) {
    ll ans = 0, base = 1;
    ll digit = 9;
    while(n) {
        ans += base * (n%digit);
        base *= 10;
        n /= digit;
    }

    return ans;
}
ll mapBase9ToNormal(ll rem,ll digit) {
    if (rem >= digit) return rem + 1;  // Skip digit
    return rem;
}

// Function to find the nth natural number that does not contain the digit 5
ll nthNumberWithoutFive(ll n,ll digit) {
    ll result = 0;
    ll place = 1;
    
    // Convert n to a "base-9" number and map to corresponding natural number
    while (n > 0) {
        ll remainder = n % 9;  // Get the last digit in base-9
        result += mapBase9ToNormal(remainder, digit) * place;
        place *= 10;  // Move to the next place (e.g., ones, tens, hundreds, etc.)
        n /= 9;  // Move to the next higher digit
    }
    
    return result;
}
int main() {
    ll n;
    cin >> n;
    ll digit = 1;
    cout << nthNumberWithoutFive(n, digit) << endl;
    return 0;
}