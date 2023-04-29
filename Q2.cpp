#include <bits/stdc++.h>

using namespace std;

double get_error(vector<pair<double, double>> &P, double a, double b, int i, int j) {
    double error = 0;
    for (int k = i; k <= j; ++k) {
        error += (P[k - 1].second - a * P[k - 1].first - b) * (P[k - 1].second - a * P[k - 1].first - b);
    }
    return error;
}

vector<vector<double>> get_min_error(vector<pair<double, double>> &P, vector<vector<double>> &a, vector<vector<double>> &b) {
    int n = P.size();
    vector<vector<double>> e(n + 1, vector<double> (n + 1));
    for (int i = 1; i <= n; ++i) {
        double sum_xy = 0;
        double sum_x = 0;
        double sum_y = 0;
        double sum_x2 = 0;
        for (int j = i; j <= n; ++j) {
            sum_xy += P[j - 1].first * P[j - 1].second;
            sum_x += P[j - 1].first;
            sum_y += P[j - 1].second;
            sum_x2 += P[j - 1].first * P[j - 1].first;
            a[i][j] = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
            b[i][j] = (sum_y - a[i][j] * sum_x) / n;
            e[i][j] = get_error(P, a[i][j], b[i][j], i, j);
        }
    }
    return e;
}

void print_segments(vector<int> &prev, vector<vector<double>> &a, vector<vector<double>> &b) {
    int n = prev.size() - 1;
    vector<pair<double, double>> segments;
    for (int i = n; i > 0; i = prev[i]) {
        segments.push_back({a[prev[i] + 1][i], b[prev[i] + 1][i]});
    }
    cout << segments.size() << "\n";
    for (auto &[a, b] : segments) {
        cout << a << " " << b << "\n";
    }
}

double segmented_least_squares(vector<pair<double, double>> &P, int C) {
    int n = P.size();
    vector<vector<double>> a(n + 1, vector<double> (n + 1));
    vector<vector<double>> b(n + 1, vector<double> (n + 1));
    auto e = get_min_error(P, a, b);
    vector<double> M(n + 1, numeric_limits<double>::max());
    M[0] = 0;
    vector<int> prev(n + 1);
    for (int j = 1; j <= n; ++j) {
        for (int i = 1; i <= j; ++i) {
            if (e[i][j] + C + M[i - 1] < M[j]) {
                M[j] = e[i][j] + C + M[i - 1];
                prev[j] = i - 1;
            }
        }
    }
    print_segments(prev, a, b);
    return M[n];
}

int main() {
    int n;
    cin >> n;
    vector<pair<double, double>> P(n);
    for (auto &[x, y] : P) {
        cin >> x >> y;
    }
    int C;
    cin >> C;

    sort(P.begin(), P.end());
    cout << segmented_least_squares(P, C) << "\n";

    return 0;
}