#include<bits/stdc++.h>
using namespace std;
#ifdef _DEBUG
  #include "_DEBUG.hpp"
#endif
#define int long long
//https://atcoder.jp/contests/abc160/tasks/abc160_f

template< int mod >
struct ModInt {
  int x;
  ModInt() : x(0) {}
  ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
  ModInt &operator+=(const ModInt &p) {
    if((x += p.x) >= mod) x -= mod;
    return *this;
  }
  ModInt &operator-=(const ModInt &p) {
    if((x += mod - p.x) >= mod) x -= mod;
    return *this;
  }
  ModInt &operator*=(const ModInt &p) {
    x = (int) (1LL * x * p.x % mod);
    return *this;
  }
  ModInt &operator/=(const ModInt &p) {
    *this *= p.inverse();
    return *this;
  }
  ModInt operator-() const { return ModInt(-x); }
  ModInt operator++() const { return ModInt(x+1); }
  ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
  ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
  ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
  ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
  bool operator==(const ModInt &p) const { return x == p.x; }
  bool operator!=(const ModInt &p) const { return x != p.x; }
  ModInt inverse() const {
    int a = x, b = mod, u = 1, v = 0, t;
    while(b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return ModInt(u);
  }
  ModInt pow(int64_t n) const {
    ModInt ret(1), mul(x);
    while(n > 0) {
      if(n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
  friend ostream &operator<<(ostream &os, const ModInt &p) {
    return os << p.x;
  }
  friend istream &operator>>(istream &is, ModInt &a) {
    int64_t t;
    is >> t;
    a = ModInt< mod >(t);
    return (is);
  }
};
using mint = ModInt< 1000000007 >;

template< typename T >
struct Combination{
  vector<T> fact; //　fact[i] = iの階乗
  Combination(int n){
    fact.resize(n+1);
    fact[0] = fact[1] = 1;
    for(int i = 2; i <= n; i++){
      fact[i] = fact[i-1] * i;
    }
  }

  T nCr(int n, int r){ // nCr = n!/r!(n-r)!
    if(n < r) return 0;
    return fact[n] / (fact[r]*fact[n-r]);
  }
};

signed main(){

  int n; cin >> n;
  vector<vector<int>> G(n);
  for(int i = 0; i < n-1; i++){
    int a, b; cin >> a >> b;
    a--, b--;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  Combination<mint> c(2e6);
  vector<mint> num(n, 0), dp(n, 1);
  auto dfs1 = [&](auto&& dfs1, int u, int p)->void{
    for(int v : G[u]){
      if(v == p) continue;
      dfs1(dfs1, v, u);
      num[u] += num[v];
      //dp[u] = dp[u] * dp[v] * c.nCr(num[u], num[v]);
    }
    ++num[u];
  };
  dfs1(dfs1, 0, -1);

  // vector<mint> ans(n);
  // auto dfs2 = [&](auto&& dfs2, int u, int p, int res)->void{
  //   ans[u] = dp[u] * res * c.nCr(n-1, (int)n-num[u]);
  //   for(int v : G[u]){
  //     if(v == p) continue;
  //     //res = ans[u] / dp[v] / c.nCr(n-1, num[v]);
  //     dfs2(dfs2, v, u, res);
  //   }
  // };
  // dfs2(dfs2, 0, -1, 1);

  // for(mint p : ans){
  //   cout << p << endl;
  // }

  return 0;
}
