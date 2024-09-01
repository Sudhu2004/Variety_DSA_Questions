// https://codeforces.com/problemset/problem/1359/C

#include<iostream>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

bool works(double cups,double c,double h, double t) {
    double totalTemp = h*(cups + 1) + c*cups;
    double totalCups = 2*cups + 1.0;
    double avgTemp = totalTemp/totalCups;

    return avgTemp >= t;
}

int getAns(double c,double h, double t) {
    
    int low = 0, high = 1e6;
    int miniCups = 0;
    while(low <= high) {
        double mid = (low + high)/2;
        if(works(mid,c, h, t)) {
            miniCups = mid;
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    if(miniCups == 1e6) {
        return 2;
    }

    else {

        double barrel1Temp = h*(miniCups + 1) + c * miniCups;
        double barrel1Cups = 2*miniCups + 1.0;
        double barrel1 = barrel1Temp/barrel1Cups;

        double barrel2Temp = h*(miniCups + 2) + c * (miniCups + 1);
        double barrel2Cups = 2*miniCups + 3.0;
        double barrel2 = barrel2Temp/barrel2Cups;

        double totalBarrel = barrel1 + barrel2;
        double avg_temp = (h + c) / 2;

        double miniTemp = min({abs(barrel1 - t), abs(barrel2 - t)
            ,abs(avg_temp - t)});
 
        if(miniTemp == abs(barrel1 - t)) {
            return barrel1Cups;
        }
        if(miniTemp == abs(barrel2 - t)) {
            return barrel2Cups;
        }

        if(miniTemp == abs(avg_temp - t))
            return 2;
    }
    
    return 0;
}


int withMath(long long c,long long h, double t) {
    
    
    if(t == h) return 1;

    if(2*t <= (h + c)) return 2;

    long long x = (t - c) / (2.0 * t - h - c);
    long long y = x + 1;

    long double firstTemp  = (x * h + (x - 1) * c) / (2.0 * x - 1.0);
    long double secondTemp = (y * h + (y - 1) * c) / (2.0 * y - 1.0);

    long double diff1 = abs(firstTemp - t);
    long double diff2 = abs(secondTemp - t); // Corrected this part

    if(diff1 <= diff2) {
        return int(2*x - 1);
    }

    return int(2*y - 1);
}
int main() {
    int t;
    cin >> t;

    while(t--) {
        // // Using Binary Search
        // double c, h, t;
        // cin >> h >> c >> t;
        // cout << getAns(c, h, t) << endl;

        // with Math
        long long c, h, t;
        cin >> h >> c >> t;
        cout << withMath(c, h, t) << endl;
    }
    return 0;
}