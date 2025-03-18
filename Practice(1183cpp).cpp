#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

bool matches(char a, char b) {
    return (a == '(' && b == ')') || (a == '[' && b == ']');
} //проверка символов на образование пары скобок

int main() {
    string s;
    getline(cin, s);

    int n = (int)s.size();
    if (n == 0) {
        cout << "\n";
        return 0;
    }

    // dp[i][j] - кратчайшая правильная скобочная последовательность,
    // в которой s[i..j] входит как подпоследовательность
    static string dp[205][205];

    // Инициализация для подотрезков длины 1
    for (int i = 0; i < n; i++) {
        if (s[i] == '(' || s[i] == ')') {
            dp[i][i] = "()";
        }
        else {
            dp[i][i] = "[]";
        }
    }

    // Перебираем длины подотрезков от 2 до n
    for (int length = 2; length <= n; length++) {
        for (int i = 0; i + length - 1 < n; i++) {
            int j = i + length - 1;

            // Начнём с "большой" строки, чтобы потом минимизировать
            string best(2 * n, 'z');

            // 1) Пробуем разделить подотрезок на два
            for (int k = i; k < j; k++) {
                string candidate = dp[i][k] + dp[k + 1][j];
                if (candidate.size() < best.size() ||
                    (candidate.size() == best.size() && candidate < best)) {
                    best = candidate;
                }
            }

            // 2) Если s[i] и s[j] можно "сопоставить"
            if (matches(s[i], s[j])) {
                // Внутренняя часть (i+1..j-1)
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

    // Выводим результат для всего отрезка [0..n-1]
    cout << dp[0][n - 1] << "\n";
    return 0;
}
