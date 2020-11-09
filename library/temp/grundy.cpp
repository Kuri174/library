#include <bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
#include "_DEBUG.hpp"
#endif
#define int long long

signed main() {
  int n;
  cin >> n;

  vector<int> g(200, 0);
  vector<int> a = {2, 3, 5};
  g[2] = 1;
  g[3] = 1;
  g[4] = 2;
  for (int i = 5; i < 200; i++) {
    set<int> st;
    for (int j = 0; j < a.size(); j++) {
      st.insert(g[i - a[j]]);
    }

    for (int j = 0; j < n; j++) {
      if (st.count(j) == 0) {
        g[i] = j;
        break;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    int t;
    cin >> t;
    cout << (g[t] != 0 ? "First" : "Second") << endl;
  }

  return 0;
}
