#include <bitset>
#include <deque>
#include <iostream>
#include <vector>

using std::cin, std::cout;
using std::vector, std::bitset, std::deque;

int main()
{
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    for (int n, m; cin >> n >> m;) {
        vector<vector<int>> gr(n), rgr(n);
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            --a, --b;
            gr[a].push_back(b);
            rgr[b].push_back(a);
        }
        deque<int> q;
        vector<int> pow(n);
        vector<int> st(n, -1);
        for (int i = 0; i < n; ++i) {
            pow[i] = gr[i].size();
            if (pow[i] == 0) {
                st[i] = 0;
                q.push_back(i);
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            if (st[v] == 0) {
                for (auto to : rgr[v]) {
                    if (st[to] == -1) {
                        st[to] = 1;
                        q.push_back(to);
                    }
                }
            } else {
                for (auto to : rgr[v]) {
                    if (--pow[to] == 0) {
                        st[to] = 0;
                        q.push_front(to);
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (st[i] == 1) {
                cout << "FIRST\n";
            } else if (st[i] == 0) {
                cout << "SECOND\n";
            } else {
                cout << "DRAW\n";
            }
        }
        cout << "\n";
    }
}
