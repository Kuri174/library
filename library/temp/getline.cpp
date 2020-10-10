#include <bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
#include "_DEBUG.hpp"
#endif
#define int long long
const int INF = 1LL << 60;

signed main() {
  string str, s;
  getline(cin, str);
  stringstream ss{str};

  vector<string> S;
  while (getline(ss, s, ' ')) {
    S.push_back(s);
  }

  int n;
  cin >> n;
  vector<string> T(n);
  for (int i = 0; i < n; i++) {
    cin >> T[i];
  }

  for (int i = 0; i < S.size(); i++) {
    bool judge = false;
    for (int j = 0; j < n; j++) {
      if (S[i].size() != T[j].size()) continue;
      for (int k = 0; k < S[i].size(); k++) {
        if (T[j][k] != '*' && S[i][k] != T[j][k]) break;
        if (k == (int)S[i].size() - 1) judge = true;
      }
    }
    if (judge) {
      for (int j = 0; j < S[i].size(); j++) {
        cout << '*';
      }
      cout << " ";
    } else {
      cout << S[i] << " ";
    }
  }
  cout << endl;

  return 0;
}