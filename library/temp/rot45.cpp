#include<bits/stdc++.h>
using namespace std;
#ifdef LOCAL_DEBUG
  #include "LOCAL_DEBUG.hpp"
#endif
#define int long long

const int INF = 1 << 30;

void rot45(int &x,int &y){
  int tmp = x + y;
  x = x - y;
  y = tmp;
}
void rot45inv(int &x,int &y){
  int tmp = (y - x) / 2;
  x = (x + y) / 2;
  y = tmp;
}

signed main(){

  int n; cin >> n;
  vector<int> x(n),y(n);
  for(int i = 0; i < n; i++){
    cin >> x[i] >> y[i];
  }

  int minx = INF,maxx = -INF, miny = INF,maxy = -INF;
  for(int i = 0; i < n; i++){
    rot45(x[i],y[i]);
    minx = min(minx, x[i]);
    maxx = max(maxx, x[i]);
    miny = min(miny, y[i]);
    maxy = max(maxy, y[i]);
    rot45inv(x[i], y[i]);
  }

  int d = max(maxx - minx, maxy - miny);
  int rx = minx + d/2, ry = miny + d/2;
  for(int _x : {rx-1, rx, rx+1}){
    for(int _y : {ry-1, ry, ry+1}){
      int px = _x, py = _y;
      rot45inv(px, py);
      int k = abs(x[0] - px) + abs(y[0] - py);
      bool judge = true;
      for(int i = 0; i < n; i++){
        if(abs(x[i] - px) + abs(y[i] - py) != k){
          judge = false;
          break;
        }
      }
      if(judge){
        cout << px << " " << py << endl;
        return 0;
      }
    }
  }

  return 0;
}
