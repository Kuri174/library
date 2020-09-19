#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 4;
const int dx[4] = {0,1,0,-1},dy[4] = {1,0,-1,0};

int mat[N][N];
int lim;

int getMD(){
  int sum = 0;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if(mat[i][j] == N*N-1) continue;
      sum += abs(mat[i][j]/N-i) + abs(mat[i][j]%N-j);
    }
  }
  return sum;
}

bool IDAstar(int depth,int prev,int py,int px){
  int MD = getMD();
  if(MD == 0) return true;
  if(depth + MD > lim) return false;

  for(int k = 0; k < 4; k++){
    int ny = py + dy[k];
    int nx = px + dx[k];
    if(ny < 0 || N <= ny || nx < 0 || N <= nx) continue;
    if(abs(k - prev) == 2) continue;
    swap(mat[ny][nx],mat[py][px]);
    if(IDAstar(depth+1,k,ny,nx)) return true;
    swap(mat[ny][nx],mat[py][px]);
  }
  return false;
}

signed main(){

  int py,px;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      cin >> mat[i][j];
      if(mat[i][j] == 0){
        mat[i][j] = N*N;
        py = i;
        px = j;
      }
      mat[i][j]--;
    }
  }

  for(lim = 0; lim < 100; lim++){
    if(IDAstar(0,100,py,px)){
      cout << lim << endl;
      return 0;
    }
  }

  return 0;
}
