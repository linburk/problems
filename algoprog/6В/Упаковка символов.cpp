#include "iostream"
#include "string"
#include "vector"
#include "algorithm"

auto _debug = [](auto&&... args) {
    ((std::cout << args << " "), ...);
    std::cout << "\n";
};
#ifdef __APPLE__
#define debug(...) _debug(__VA_ARGS__)
#else
#define debug(...) 0
#endif


using std::vector, std::string;

int main(int argc, char ** argv) {
#ifdef __APPLE__
    std::freopen("/users/dmitrii/documents/code/code/input.txt", "r", stdin);
    std::freopen("/users/dmitrii/documents/code/code/output.txt", "w", stdout);
#endif
    string s;
    std::cin >> s;
    int n = (int)s.size();
    vector<vector<string> > dp(n + 1, vector<string>(n + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            dp[i][j] = s.substr(i, j - i + 1);
        }
    }
    for (int k = 5; k < n; ++k) {
        for (int l = 0; l < n - k; ++l) {
            int r = l + k;
            for (int m = l; m < r; ++m) {
                if (dp[l][m].length() + dp[m + 1][r].length() < dp[l][r].length()) {
                    dp[l][r] = dp[l][m] + dp[m + 1][r];
                }
            }
            string t = dp[l][r];
            for (int p = 1; p <= t.size() / 2; ++p) {
                for (int can = true, x = 2; x * p - 1 <= t.size(); ++x) {
                    for (int check = 1; check < x; ++check) {
                        if (t.substr(0, p) != t.substr(check * p, p)) {
                            can = false;
                            break;
                        }
                    }
                    if (!can) break;
                    if (dp[l][r].length() > 2 + std::to_string(x).length() + p + t.size() - x * p) {
                        dp[l][r] = std::to_string(x) + '(' + t.substr(0, p) + ')' + t.substr(x * p, t.size() - x * p);
                    }
                }
            }
            for (int p = 1; p <= (r - l + 1) / 2; ++p) {
                for (int can = true, x = 2; l + x * p - 1 <= r; ++x) {
                    for (int check = 1; check < x; ++check) {
                        if (s.substr(l, p) != s.substr(l + check * p, p)) {
                            can = false;
                            break;
                        }
                    }
                    if (!can) break;
                    if (dp[l][r].length() > 2 + std::to_string(x).length() + p + dp[l + x * p][r].size()) {
                        dp[l][r] = std::to_string(x) + '(' + s.substr(l, p) + ')' + dp[l + x * p][r];
                    }
                }
            }
        }
    }
    std::cout << dp[0][n - 1];
}