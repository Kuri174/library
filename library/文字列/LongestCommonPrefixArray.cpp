#include<bits/stdc++.h>
using namespace std;
#define int long long

template<class T>
struct SparseTable{
  vector<vector<T>> dat;
  vector<int> height;

  SparseTable(){};
  SparseTable(vector<T> v){
    int n = v.size(), h = 0;
    while ((1<<h) < n) h++;
    dat.assign(h, vector<T> (1<<h)); height.assign(n+1, 0);
    for(int i = 2; i <= n; i++) height[i] = height[i>>1] + 1;
    for(int i = 0; i < n; i++) dat[0][i] = v[i];
    for(int i = 1; i < h; i++){
      for(int j = 0; j < n; j++){
        dat[i][j] = min(dat[i-1][j], dat[i-1][min(j+(1<<(i-1)),n-1)]);
      }
    }
  }
  T getval(int a, int b) {
    return min(dat[height[b-a]][a], dat[height[b-a]][b - (1<<height[b-a])]);
  }
};

vector<int> SuffixArray(string s){
  int n = s.size(), k;
  vector<int> sa(n+1), rank(n+1);

  auto comp = [&](int i, int j){
    if(rank[i] != rank[j]) return rank[i] < rank[j];
    return (i+k < n ? rank[i+k] : -1) < (j+k < n ? rank[j+k] : -1);
  };
  for(int i = 0; i <= n; i++){
    sa[i] = i;
    rank[i] = i < n ? s[i] : -1;
  }
  for(k = 1; k <= n; k *= 2){
    sort(sa.begin(),sa.end(),comp);
    auto tmp = rank;
    tmp[sa[0]] = 0;
    for(int i = 1; i <= n; i++){
      tmp[sa[i]] = tmp[sa[i-1]] + comp(sa[i-1], sa[i]);
    }
    rank = tmp;
  }
  return sa;
}

struct LongestCommonPrefixArray{
  vector<int> lcp, rank;
  SparseTable<int> st;
  LongestCommonPrefixArray(string s, vector<int> sa){
    int n = s.size();
    lcp.resize(n+1, 0), rank.resize(n+1);
    for(int i = 0; i <= n; i++){
      rank[sa[i]] = i;
    }
    int h = 0;
    for(int i = 0; i < n; i++){
      int j = sa[rank[i] - 1];
      if(h > 0) h--;
      for(; max(i, j) + h < n; h++){
        if(s[i + h] != s[j + h]) break;
      }
      lcp[rank[i] - 1] = h;
    }
    st = SparseTable<int>(lcp);
  }

  int getlcp(int a, int b){
    return st.getval(min(rank[a], rank[b]), max(rank[a], rank[b]));
  }
};

signed main(){

  string s, t; cin >> s >> t;
  int n = s.size();
  s = s + "~" + t;
  //abaracadabra
  //ecadadabrbcrdar

  auto sa = SuffixArray(s);
  LongestCommonPrefixArray lcp(s, sa);
  int ans = 0;
  for(int i = 0; i < n; i++){
    for(int j = n+1; j < s.size(); j++){
      ans = max(ans, min(j - i, lcp.getlcp(i, j)));
    }
  }
  cout << ans << endl;

  return 0;
}
