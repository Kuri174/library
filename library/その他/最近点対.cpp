#include<bits/stdc++.h>
using namespace std;

struct point{
  double x,y;
  bool operator<( const point &u ) const {
      return x < u.x;
      //if(x != u.x) return x < u.x;
      //  return y < u.y;
  }
};
point a[100000];

bool cmp(point a,point b){ return a.y < b.y;}

double dis(point a,point b){
  return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double merge(int left,int right){
  if(left+1 == right) return dis(a[left],a[right]);
  int mid = (left+right)/2;
  double xm = min(merge(left,mid),merge(mid,right));

  //片方leftもう片方rightに属する、x軸の距離がxmより小さい点対を探す
  vector<point> vec;
  for(int i = left; i <= right; i++){
    if(abs(a[mid].x-a[i].x) <= xm){
      vec.push_back(a[i]);
    }
  }
  //y軸の距離がxmより小さい点対と比べる
  sort(vec.begin(),vec.end(),cmp);
  for(int i = 0; i < vec.size(); i++){
    for(int j = i+1; j < vec.size(); j++){
      if(vec[j].y-vec[i].y > xm) break;
      xm = min(xm,dis(vec[i],vec[j]));
    }
  }
  return xm;
}

signed main(){

  int n; cin >> n;
  for(int i = 0; i < n; i++){
    cin >> a[i].x >> a[i].y;
  }

  sort(a,a+n);
  printf("%.6f\n",(merge(0,n-1)));

  return 0;
}
