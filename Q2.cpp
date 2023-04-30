/**
 * @file Q2.cpp
 * @author Sai Prasanna Panda(2020A7PS0080H)
 * Harshit Verma 9.93(2020A7PS0041H)
 * @brief DAA Assigment-2 Question 2
 *
 */
#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Epsilon value to avoid division by 0
const double EPS = 1e-8;

/**
 * @brief Get the error for a subarray of points, given the slope and intercept of the fitted line
 * 
 * @param P : vector of points
 * @param a : slope of fitted line
 * @param b : intercept of fitted line
 * @param i : left index of subarray
 * @param j : right index of subarray
 * @return double : error
 */
double get_error(vector<pair<double, double>> &P, double a, double b, int i, int j) {
    double error = 0;
    for (int k = i; k <= j; ++k) {
        error += (P[k - 1].second - a * P[k - 1].first - b) * (P[k - 1].second - a * P[k - 1].first - b);
    }
    return error;
}

/**
 * @brief Get the minimum error for all subarrays of a list of points
 * 
 * @param P : vector of points
 * @param a : 2d vector to store slopes
 * @param b : 2d vector to store intercepts
 * @return vector<vector<double>> : 2d vector containing minimum errors for each subarray
 */
vector<vector<double>> get_min_error(vector<pair<double, double>> &P, vector<vector<double>> &a, vector<vector<double>> &b) {
    // cout << "Errors:\n";
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
            int len = j - i + 1;
            a[i][j] = (len * sum_xy - sum_x * sum_y) / (len * sum_x2 - sum_x * sum_x + EPS);
            b[i][j] = (sum_y - a[i][j] * sum_x) / len;
            e[i][j] = get_error(P, a[i][j], b[i][j], i, j);
            // cout << i << " " << j << " " << e[i][j] << "\n";
        }
    }
    return e;
}


/**
 * @brief Prints segments found by segmented_least_squares()
 * 
 * @param prev : vector containing previous index of each index in vector of points
 * @param P : vector of points
 * @param a : vector of slopes
 * @param b : vector of intercepts
 */
void print_segments(vector<int> &prev, vector<pair<double, double>> &P, vector<vector<double>> &a, vector<vector<double>> &b)
{
    int n = prev.size() - 1;
    vector<pair<int, int>> segments;
    for (int i = n; i > 0; i = prev[i]) {
        segments.push_back({prev[i] + 1, i});
    }
    cout << segments.size() << "\n";
    for (auto &[l, r] : segments) {
        cout << P[l - 1].first << " " << P[r - 1].first << " " << a[l][r] << " " << b[l][r] << "\n";
    }
}

/**
 * @brief Executes segmented least squares line fitting algorithm give a list of points and the penalty for a new line segment
 * 
 * @param P : vector of points
 * @param C : penalty for adding a new line segment
 * @return double : minimum possible error for the given list of points
 */
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
    print_segments(prev, P, a, b);
    return M[n];
}

int main() {
    auto start = high_resolution_clock::now();

    int n;
    cin >> n;
    vector<pair<double, double>> P(n);
    for (auto &[x, y] : P) {
        cin >> x >> y;
    }
    int C;
    cin >> C;

    sort(P.begin(), P.end());

    cout << n << "\n";
    for (auto &[x, y] : P) {
        cout << x << " " << y << "\n";
    }

    cout << segmented_least_squares(P, C) << "\n";

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    // cout << duration.count() << endl;

    return 0;
}