#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using std::vector, std::string;

int const P = 37, MOD = 1E9 + 7;
vector<int64_t> powers(51);
void powers_() {
    powers[0] = 1;
    for (int i = 1; i < 50; ++i) {
        powers[i] = (powers[i - 1] * P) % MOD;
    }
}

vector<int64_t> hash(string const &s) {
    vector<int64_t> hash_(s.size() + 1);
    hash_[s.size()] = 1;
    for (int i = (int)s.size() - 1; i >= 0; --i) {
        hash_[i] = (hash_[i + 1] * P % MOD + s[i] - 'a' + 1) % MOD;
    }
    return hash_;
}

int64_t get_hash(int l, int r, vector<int64_t> const &hash) {
    return (hash[l] + MOD - hash[r] * powers[r - l] % MOD) % MOD;
}

std::unordered_map<int64_t, int> count;

int main(int argc, char ** argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#ifdef __APPLE__
    std::freopen("/users/dmitrii/documents/code/code/input.txt", "r", stdin);
    std::freopen("/users/dmitrii/documents/code/code/output.txt", "w", stdout);
#endif
    powers_();
    int n, m;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        string t;
        std::cin >> t;
        vector<int64_t> hash_ = hash(t);
        for (int j = 0; j < t.size(); ++j) {
            if (get_hash(0, j, hash_) == get_hash((int)t.size() - j - 1, (int)t.size() - 1, hash_)) {
                ++count[get_hash(0, j, hash_)];
            }
        }
    }
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        string s;
        std::cin >> s;
        vector<int64_t> hash_ = hash(s);
        std::cout << count[get_hash(0, (int)s.size() - 1, hash_)] << "\n";
    }
}