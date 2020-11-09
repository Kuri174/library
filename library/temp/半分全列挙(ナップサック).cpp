#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 1LL << 60;

signed main() {
  int N, W;
  cin >> N >> W;
  if (N > 30) return 0;
  vector<int> v(N), w(N);
  for (int i = 0; i < N; i++) {
    cin >> v[i] >> w[i];
  }

  int n2 = N / 2;
  vector<pair<int, int> > ps(1 << n2);
  for (int i = 0; i < 1 << n2; i++) {
    int nv = 0, nw = 0;
    for (int j = 0; j < n2; j++) {
      if (1 & (i >> j)) {
        nv += v[j];
        nw += w[j];
      }
    }
    ps[i] = make_pair(nw, nv);
  }
  sort(ps.begin(), ps.end());

  int m = 1;
  for (int i = 1; i < 1 << n2; i++) {
    if (ps[m - 1].second < ps[i].second) {
      ps[m++] = ps[i];
    }
  }

  int ans = 0;
  for (int i = 0; i < 1 << (N - n2); i++) {
    int nv = 0, nw = 0;
    for (int j = 0; j < (N - n2); j++) {
      if (1 & (i >> j)) {
        nv += v[n2 + j];
        nw += w[n2 + j];
      }
    }
    if (nw <= W) {
      auto p = lower_bound(ps.begin(), ps.begin() + m, make_pair(W - nw, INF));
      ans = max(ans, nv + (p - 1)->second);
    }
  }
  cout << ans << endl;

  return 0;
}
