#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define ff first
#define ss second
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl "\n"

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<int>(L, R)(rng)


int32_t main() {
    freopen("test_sin_1000_0.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n = 1000;
    cout << n << "\n";
    int k;
    for (int i = 0; i < n; ++i) {
        int x = uniform_int_distribution<int>(-100000, 100000)(rng);
        double xd = x / 100.0;
        if (i % 50 == 0)
            k = uniform_int_distribution<int>(1, n)(rng);
        cout << xd << " " << k * sin(xd) << "\n";
    }
    cout << 0 << "\n";

    return 0;
}