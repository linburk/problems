#include <iostream>
#include <vector>

using i64 = long long;

int main()
{
   int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n), r_a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        r_a[n - i - 1] = a[i];
    }
    std::vector<i64> pow(n + 1);
    std::vector<i64> hash(n + 1);
    std::vector<i64> r_hash(n + 1);
    int p = 1E5 + 13;
    int mod = 1E9 + 7;
    pow[0] = 1;
    hash[0] = r_hash[0] = 1;
    for (int i = 0; i < n; ++i) {
        pow[i + 1] = (pow[i] * p) % mod;
        hash[i + 1] = (hash[i] * p % mod + a[i]) % mod;
        r_hash[i + 1] = (r_hash[i] * p % mod + r_a[i]) % mod;
    } 
    auto substr = [&mod, &pow] (std::vector<i64> &hash, int i, int len) {
        return (hash[i + len] - hash[i] * pow[len] % mod + mod) % mod;
    };
    for (int i = n / 2; i >= 0; --i)
        if (!i || substr(r_hash, n - i, i) == substr(hash, i, i))
            std::cout << n - i << ' ';
    return 0;
}
