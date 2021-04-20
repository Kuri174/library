#include <bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
#include "_DEBUG.hpp"
#endif
#define int long long
const int INF = 1LL << 60;

signed main() {
  int n;
  cin >> n;
  vector<int> a(n), rev(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i]--;
    rev[a[i]] = i;
  }

  int cnt = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] == i) continue;
    swap(a[i], a[rev[i]]);
    swap(rev[a[i]], rev[a[rev[i]]]);
    cnt++;
  }

  if ((n - cnt) % 2 == 0) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }

  return 0;
}