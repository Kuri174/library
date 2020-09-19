#include<bits/stdc++.h>
using namespace std;

int a[200010];

int partition(int p, int r){
  for(int i = p; i < r; i++){
    if(a[i] <= a[r]) swap(a[p++], a[i]);
  }
  swap(a[p], a[r]);
  return p;
}

void quicksort(int p, int r){
  if(p >= r) return;
  int q = partition(p, r);
  quicksort(p, q-1);
  quicksort(q+1, r);
}

signed main(){

  int n; cin >> n;
  for(int i = 0; i < n; i++) cin >> a[i];

  quicksort(0, n-1);
  for(int i = 0; i < n; i++){
    if(i) cout << " ";
    cout << a[i];
  }
  cout << endl;

  return 0;
}
