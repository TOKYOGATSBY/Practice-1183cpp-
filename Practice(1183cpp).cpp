#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

bool matches(char a, char b) {
    return (a == '(' && b == ')') || (a == '[' && b == ']');
}

int main() {
    string s;
    getline(cin, s);

    int n = (int)s.size();
    if (n == 0) {
        cout << endl;
        return 0;
    }

    static string dp[205][205];

    for (int i = 0; i < n; i++) {
        if (s[i] == '(' || s[i] == ')') {
            dp[i][i] = "()";
        }
        else {
            dp[i][i] = "[]";
        }
    }

    for (int length = 2; length <= n; length++) {
        for (int i = 0; i + length - 1 < n; i++) {
            int j = i + length - 1;

            string best(2 * n, 'z');

            for (int k = i; k < j; k++) {
                string candidate = dp[i][k] + dp[k + 1][j];
                if (candidate.size() < best.size() ||
                    (candidate.size() == best.size() && candidate < best)) {
                    best = candidate;
                }
            }

            if (matches(s[i], s[j])) {
                string inside;
                if (i + 1 <= j - 1) {
                    inside = dp[i + 1][j - 1];
                }
                string candidate = s[i] + inside + s[j];
                if (candidate.size() < best.size() ||
                    (candidate.size() == best.size() && candidate < best)) {
                    best = candidate;
                }
            }

            dp[i][j] = best;
        }
    }

    cout << dp[0][n - 1] << endl;

    return 0;
}
