#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define unique(cont) cont.erase(unique(all(cont)), cont.end())
#define pb(x) emplace_back(x)

namespace tools {

    template <typename T>
    T gcd(T a, T b) {
        while (b > 0) {
            a %= b;
            std::swap(a, b);
        }
        return a;
    }

    template <typename T>
    T lcm(T a, T b) {
        return a * b / gcd(a, b);
    }

    template <typename T>
    std::istream &operator>>(std::istream &is, std::vector<T> &array) {
        for (auto &i : array) {
            is >> i;
        }
        return is;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &array) {
        for (const auto &i : array) {
            os << i << " ";
        }
        return os;
    }

    template <typename T>
    std::istream &operator>>(std::istream &is,
                             std::vector<std::vector<T> > &matrix) {
        for (auto &i : matrix)
            for (auto &j : i) is >> j;
        return is;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os,
                             const std::vector<std::vector<T> > &matrix) {
        for (const auto &i : matrix) {
            for (const auto &j : i) os << j << " ";
            os << "\n";
        }
        return os;
    }

    template <typename T, typename V>
    std::istream &operator>>(std::istream &is, std::pair<T, V> &p) {
        is >> p.first >> p.second;
        return is;
    }

}  // namespace tools
using namespace tools;

namespace hash_structure {

    class hash_string : public std::string {
    private:
        static const size_t MAXLEN = 200001;
        static const unsigned short P1 = 131, P2 = 139;
        static std::vector<std::pair<unsigned long long, unsigned long long> > initialize_pows(){
            std::vector<std::pair<unsigned long long, unsigned long long> > powers(MAXLEN);
            powers[0] = {1, 1};
            for (int i = 1; i < MAXLEN; i++) {
                powers[i].first = 1LL * powers[i - 1].first * P1;
                powers[i].second = 1LL * powers[i - 1].second * P2;
            }
            return powers;
        }
        static inline std::vector<std::pair<unsigned long long, unsigned long long> > pows = initialize_pows();
        std::vector<std::pair<unsigned long long, unsigned long long> > hash;
    public:
        void calculate_hash() {
            hash.resize(length() + 1);
            hash[length()] = {0, 0};
            for (auto i = rbegin(); i != rend(); i++) {
                size_t ind = distance(i, rend()) - 1;
                hash[ind] = {*i - 'A' + 1 + 1LL * hash[ind + 1].first * P1,
                             *i - 'A' + 1 + 1LL * hash[ind + 1].second * P2};
            }
        }

        const std::pair<unsigned long long, unsigned long long> get_hash(size_t l, size_t r) const {
            // 0-indexed
            return {hash[l].first - hash[r].first * pows[r - l].first,
                    hash[l].second - hash[r].second * pows[r - l].second};
        }

        const std::pair<unsigned long long, unsigned long long> get_hash() const {
            return get_hash(0, length());
        }
    };
}
using namespace hash_structure;

void solve(){
    int n;
    cin >> n;
    cin.get();
    hash_string a, b;
    getline(cin, a);
    reverse_copy(all(a), back_inserter(b));
    a.calculate_hash();
    b.calculate_hash();
    vector<int> result(n);
    for (int i = 0; i < n; i++){
        int ind = n - i - 1;
        int left = 0, right = i + 2;
        while (right - left > 1){
            int mid = (right + left) / 2;
            if (a.get_hash(0, mid) == b.get_hash(ind, ind + mid))
                left = mid;
            else
                right = mid;
        }
        result[i] = left;
    }
    cout << result;

}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
    std::freopen("input.txt", "r", stdin);
    std::freopen("output.txt", "w", stdout);
#endif
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios_base::sync_with_stdio(false);
//    int t;
//    cin >> t;
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}