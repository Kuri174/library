#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <thread>
#include <chrono>
using namespace std;

pair<int, int> get_game() {
  cout << "game" << endl;
  int game_id, remaining_time;
  cin >> game_id >> remaining_time;
  return {game_id, remaining_time};
}

vector<vector<int>> get_stage(int game_id) {
  cout << "stage " << game_id << endl;
  int n;
  cin >> n;
  if (n != 20) throw 1;
  vector<vector<int>> a(20, vector<int>(20));
  for (auto& b : a) for (auto& x : b) cin >> x;
  return a;
}

pair<bool, pair<vector<vector<int>>, vector<vector<int>>>> get_areas(int game_id) {
  cout << "areas " << game_id << endl;
  string status;
  cin >> status;
  if (status == "ok") {
    vector<vector<int>> a1(20, vector<int>(20));
    vector<vector<int>> a2(20, vector<int>(20));
    for (auto& b : a1) for (auto& x : b) cin >> x;
    for (auto& b : a2) for (auto& x : b) cin >> x;
    return {true, {a1, a2}};
  } else if (status == "too_many_request") {
    return {false, {{}, {}}};
  } else {
    throw 1;
  }
}

bool claim(int game_id, int r, int c, int m) {
  cout << "claim " << game_id << " " << r << "-" << c << "-" << m << endl;
  string status;
  cin >> status;
  if (status == "ok") {
    return true;
  } else if (status == "game_finished") {
    return false;
  } else {
    throw 1;
  }
}

struct CalcScore {
  const vector<vector<int>>& stage;
  const vector<vector<int>>& num_claim;
  const vector<vector<int>>& my_claim;
  vector<vector<bool>> visited;
  CalcScore(const vector<vector<int>>& stage, const vector<vector<int>>& num_claim, const vector<vector<int>>& my_claim)
    : stage(stage), num_claim(num_claim), my_claim(my_claim), visited(20, vector<bool>(20)) {}
  pair<double, int> f(int r, int c) {
    if (r < 0 || r >= 20 || c < 0 || c >= 20 || my_claim[r][c] == 0 || visited[r][c]) {
      return {1e+300, 0};
    }
    visited[r][c] = true;
    double r1 = (double)stage[r][c] / num_claim[r][c];
    int r2 = 1;
    for (auto p : {f(r+1, c), f(r-1, c), f(r, c+1), f(r, c-1)}) {
      r1 = min(r1, p.first);
      r2 += p.second;
    }
    return {r1, r2};
  }
  double calc() {
    double score = 0;
    for (int i = 0; i < 20; ++ i) {
      for (int j = 0; j < 20; ++ j) {
        auto p = f(i, j);
        score += p.first * p.second;
      }
    }
    return score;
  }
};

using P = pair<int, int>;

int main() {
  random_device rd;
  mt19937 mt(rd());

  for (;;) {
    auto game = get_game();
    auto game_id = game.first;
    auto stage = get_stage(game_id);
    
    vector<P> domp;
    int cnt = 0;


    for (;;) {
      auto areas = get_areas(game_id);
      if (!areas.first) {
        cerr << "too_many_request" << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
        continue;
      }
      const auto& num_claim = areas.second.first;
      const auto& my_claim = areas.second.second;

      auto score = CalcScore(stage, num_claim, my_claim).calc();
      cerr << "game_id: " << game_id << "  score: " << score << endl;

      vector<pair<int,int>> candidate;
      for (int i = 0; i < 20; ++ i) {
        for (int j = 0; j < 20; ++ j) {
          if (my_claim[i][j] == 0) {
            candidate.push_back({i, j});
          }
        }
      }
      if (candidate.empty()) throw 1;

      //auto rc = candidate[uniform_int_distribution<int>(0, candidate.size()-1)(mt)];
      sort(candidate.begin(), candidate.end());
      int y = 10, x = 10;
      double Max = 10;
      if(!domp.empty()){
        sort(domp.begin(), domp.end());
        domp.erase(unique(domp.begin(),domp.end()),domp.end());
      }
      if(cnt > 50){
        for(int i = 0; i < 20-2; i++){
          for(int j = 0; j < 20-2; j++){
            bool judge = true;
            double res = 0;
            for(int k = 0; k < 2; k++){
              for(int l = 0; l < 2; l++){
                res += 1.0 * stage[i+k][j+l] / max(1, num_claim[i+k][j+l]);
                for(auto p : domp){
                  if(p.first == i+k && p.second == j+l) judge = false;
                }
              }
            }
            if(!judge) continue;
            if(Max < res && *lower_bound(candidate.begin(), candidate.end(), P(i, j)) == P(i, j)){
              Max = res;
              y = i;
              x = j;
            }
          }
        }
        if(y == 10){
          for(int i = 0; i < 20; i++){
            for(int j = 0; j < 20; j++){
              bool judge = true;
              for(auto p : domp){
                if(p.first == i && p.second == j) judge = false;
              }
              if(!judge) continue;
              double res = 1.0 * stage[i][j] / max(1, num_claim[i][j]);
            //double res = 1.0 * stage[i][j];
              if(Max < res && *lower_bound(candidate.begin(), candidate.end(), P(i, j)) == P(i, j)){
                Max = res;
                y = i;
                x = j;
              }
            }
          }
          if(y-1 >= 0) domp.push_back({y-1, x});
          if(y+1 < 20) domp.push_back({y+1, x});
          if(x-1 >= 0) domp.push_back({y, x-1});
          if(x+1 < 20) domp.push_back({y, x+1});
          cnt++;
          if (!claim(game_id, y, x, 1)) {
            break;
          }
          continue;
        }
        for(int k = 0; k < 2; k++){
          if(y-1 >= 0) domp.push_back({y-1, x+k});
        }
        for(int k = 0; k < 2; k++){
          if(y+2 < 20) domp.push_back({y+2, x+k});
        }
        for(int k = 0; k < 2; k++){
          if(x-1 >= 0) domp.push_back({y+k, x-1});
        }
        for(int k = 0; k < 2; k++){
          if(x+2 < 20) domp.push_back({y+k, x+2});
        }
        cnt += 2*2;
        y = max(y, 0), x = max(x, 0);
        if (!claim(game_id, y, x, 2)) {
          break;
        }
        if(y + x == 0) cnt = 0;
      }else{
        for(int i = 0; i < 20; i++){
          for(int j = 0; j < 20; j++){
            bool judge = true;
            for(auto p : domp){
              if(p.first == i && p.second == j) judge = false;
            }
            if(!judge) continue;
            double res = 1.0 * stage[i][j] / max(1, num_claim[i][j]);
            //double res = 1.0 * stage[i][j];
            if(Max < res && *lower_bound(candidate.begin(), candidate.end(), P(i, j)) == P(i, j)){
              Max = res;
              y = i;
              x = j;
            }
          }
        }
        if(y-1 >= 0) domp.push_back({y-1, x});
        if(y+1 < 20) domp.push_back({y+1, x});
        if(x-1 >= 0) domp.push_back({y, x-1});
        if(x+1 < 20) domp.push_back({y, x+1});
        cnt++;
        if (!claim(game_id, y, x, 1)) {
          break;
        }
      }
    }
    while (get_game().first == game_id) {
      this_thread::sleep_for(chrono::milliseconds(500));
    }
  }
}
