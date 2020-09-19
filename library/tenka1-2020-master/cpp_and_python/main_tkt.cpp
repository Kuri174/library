#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>
#include <bitset>
#include <complex>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <cassert>
#include <functional>

#include <ctime>
#include <sys/time.h>
#include <unistd.h>

#include "./debug.hpp"

typedef long long ll;
using namespace std;

enum {
  STATUS_OK,
  STATUS_TL,
  STATUS_FINISH,
  STATUS_CLAIMED,
  STATUS_ERROR,
};

/**** DEBUG ****/

#define LAPTIME 500 * 1000 //usec

/* Run */
// ./a.out >> out*.txt

/*接続設定*/
const string url_game = "https://contest.gbc-2020.tenka1.klab.jp/api/game";
const string url_stage = "https://contest.gbc-2020.tenka1.klab.jp/api/stage/<stage>";
const string url_claim = "https://contest.gbc-2020.tenka1.klab.jp/api/claim/<token>/<stage>/<index>";
const string url_areas = "https://contest.gbc-2020.tenka1.klab.jp/api/areas/<token>/<stage>";
const string url_ranking = "https://contest.gbc-2020.tenka1.klab.jp/api/ranking/<token>/<stage>";
const string token = "96f67572bd822e21e2ff4e0778f7311d";

/* グローバル変数 */

/* URL置換 */

string writeToken(string url) {
  string key = "<token>";
  std::string::size_type pos = url.find(key);
  if (pos != std::string::npos) {
    url.replace(pos, key.size(), token);
  }

  return url;
}

string writeStage(string url, int stage) {
  string key = "<stage>";
  string stage_str = to_string(stage);

  std::string::size_type pos = url.find(key);
  if (pos != std::string::npos) {
    url.replace(pos, key.size(), stage_str);
  }

  return url;
}

string writeIndex(string url, int row, int col, int size) {
  string key = "<index>";

  string index_str = to_string(row) + "-" + to_string(col) + "-" + to_string(size);

  std::string::size_type pos = url.find(key);
  if (pos != std::string::npos) {
    url.replace(pos, key.size(), index_str);
  }

  return url;
}

/*間隔計測*/

static long long base_sec;
long long stime = 0, stime_i = 0;

void set_base_sec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  base_sec = tv.tv_sec;
}

ll lap_usec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec - base_sec) * 1000000 + tv.tv_usec;
}

/*時刻取得*/
string get_time() {
  string n_time;
  char chr[20];
  time_t timer = time(NULL);
  tm *t_st;

  t_st = localtime(&timer);
  sprintf(chr, "%02d:%02d:%02d", t_st->tm_hour, t_st->tm_min, t_st->tm_sec);

  return string(chr);
}

/*HTTPリクエスト*/
string query(string url, bool console = true) {
  while (lap_usec() - stime < LAPTIME)
    ;

  //アタック
  FILE *f = popen(("curl -s \"" + url + "\"").c_str(), "r");

  if (f == NULL) {
    perror("error!");
  }

  char buf[1024];
  string res;
  while (!feof(f)) {
    if (fgets(buf, 1024, f) == NULL)
      break;
    res += (string)(buf);
  }

  stime = lap_usec();

  pclose(f);

  if (console)
    cerr << url << " : " << res << "\t" << stime << endl; //コンソール

  cout << get_time() << "\t" << url << " : " << res << endl; //ログ記録

  return res;
}

/* --------------------------------作業スペース-------------------------------- */

struct GameInfo {
  int id, T;
};

GameInfo getGameInfo() {
  try {
    string url = url_game;
    auto res = query(url);

    stringstream ss;
    ss << res;

    GameInfo info;
    ss >> info.id >> info.T;
    return info;
  } catch (...) {
    cerr << "Error: getGameInfo" << endl;
  }

  GameInfo info;
  info.id = -1;
  return info;
}

struct StageInfo {
  int N;
  int V[20][20];
};

StageInfo getStageInfo(const GameInfo &game) {
  try {
    string url = url_stage;
    url = writeStage(url, game.id);
    auto res = query(url);

    stringstream ss;
    ss << res;

    StageInfo info;
    ss >> info.N;

    debug(info.N);

    for (int i = 0; i < info.N; i++)
      for (int j = 0; j < info.N; j++)
        ss >> info.V[i][j];

    return info;
  } catch (...) {
    cerr << "Error: getStageInfo" << endl;
  }

  StageInfo info;
  info.N = -1;

  return info;
}

struct AreasInfo {
  bool invalid;
  int A[20][20], B[20][20];
};

AreasInfo getAreasInfo(const GameInfo &game, const StageInfo &stage) {
  AreasInfo info;
  info.invalid = false;

  try {
    string url = url_areas;
    url = writeToken(url);
    url = writeStage(url, game.id);
    auto res = query(url, false);

    stringstream ss;
    ss << res;

    string status;

    ss >> status;

    assert(status == "ok");

    for (int i = 0; i < stage.N; i++)
      for (int j = 0; j < stage.N; j++)
        ss >> info.A[i][j];

    for (int i = 0; i < stage.N; i++)
      for (int j = 0; j < stage.N; j++)
        ss >> info.B[i][j];

  } catch (...) {
    cerr << "Error: getEdgesInfo " << endl;
    info.invalid = true;
  }

  return info;
}

int claimArea(const GameInfo &game, int row, int col, int size) {
  try {
    string url = url_claim;
    url = writeToken(url);
    url = writeStage(url, game.id);
    url = writeIndex(url, row, col, size);
    auto res = query(url);

    debug(res);
    if (res.substr(0, 2) == "ok")
      return STATUS_OK;

    if (res.substr(0, 15) == "already_claimed")
      return STATUS_CLAIMED;

    if (res.substr(0, 16) == "claim_time_limit")
      return STATUS_TL;

    if (res.substr(0, 13) == "game_finished")
      return STATUS_FINISH;

    return STATUS_ERROR;
  } catch (...) {
    cerr << "Error: claimEdge " << row << ", " << col << ", " << size << endl;
  }

  return STATUS_ERROR;
}

/*メイン関数*/
int main() {
  int to, from, num;
  // memo_read(); //読取
  set_base_sec();

  char att[51] = "";

  int prev_game = -1; //Error発生時にデータを再読み込みしないように

  while (1) {
    GameInfo info;
    StageInfo stage;
    do {
      do {
        info = getGameInfo();
      } while (info.id == prev_game || info.id < 0);

      debug(info.id);

      stage = getStageInfo(info);
      debug(stage.N);

    } while (stage.N <= 0);

    prev_game = info.id;

    int groups[20][20] = {}, groupIdx = 1;
    int cant[20][20] = {};

    const ll startedAt = lap_usec() - (60 * 1000 - info.T) * 1000;

    AreasInfo area = getAreasInfo(info, stage);
    ll lastArea = lap_usec();

    while (1) {
      if (lap_usec() - lastArea > 2000 * 1000) {
        area = getAreasInfo(info, stage);
        lastArea = lap_usec();
      }

      pair<pair<pair<int, int>, pair<int, int>>, int> p = {{{-1, -1}, {-1, -1}}, -1};

      int rest_msec = 60 * 1000 - (lap_usec() - startedAt) / 1000;

      for (int size = 4; size >= 1; size--) {
        for (int row = 0; row < stage.N - size + 1; row++) {
          for (int col = 0; col < stage.N - size + 1; col++) {
            int minV = 100000000;
            int maxV = 0;
            int sumCant = 0, counter = 0;

            for (int y = row; y < row + size; y++) {
              for (int x = col; x < col + size; x++) {
                int v = stage.V[y][x] / (area.A[y][x] + 1);
                minV = min(minV, v);
                maxV = max(maxV, v);
                counter += !groups[y][x];
                if (cant[y][x] == -2 || sumCant == 0)
                  sumCant = cant[y][x];
                else if (cant[y][x] && sumCant)
                  sumCant = -2;
              }
            }

            // if (sumCant == -2) continue;
            if (counter == 0) continue;

            // if (rest_msec > 20 && sumCant != 0) continue;
            if (rest_msec > 15 * 1000 && counter != size * size) continue;
            if (rest_msec > 7 * 1000 && size * size - counter >= 4) continue;

            if (p.first.first.first >= rest_msec / 2200 + 10) break;

            if (rest_msec / 1000 > 20) {
              p = max(p, {{{minV * counter / (size + 1) / (size + 1), size}, {row, col}}, sumCant});
            }
          }

          // if (p.first.first.first >= rest_msec / 2200 + 10) break;
        }

        int minV = p.first.first.first;
        int size = p.first.first.second;
        int row = p.first.second.first;
        int col = p.first.second.second;
        int group = p.second;


        const int status = claimArea(info, row, col, size);

        if (status == STATUS_OK || status == STATUS_CLAIMED) {
          for (int y = row; y < row + size; y++) {
            for (int x = col; x < col + size; x++) {
              int g = group ? group : groupIdx;
              groups[y][x] = g;

              cant[y][x] = cant[y][x] == 0 || cant[y][x] == g ? g : -2;
              if (y > 0) cant[y - 1][x] = true;
              if (x > 0) cant[y][x - 1] = true;
              if (y + 1 < stage.N) cant[y + 1][x] = true;
              if (x + 1 < stage.N) cant[y][x + 1] = true;
            }
          }

          if (!group) groupIdx++;

          continue;
        }

        if (status == STATUS_TL)
          continue;

        if (status == STATUS_ERROR) {
          prev_game = -1;
          break;
        }

        if (status == STATUS_FINISH) {
          fprintf(stderr, "--- %d ---\n\n", info.id);

          for (int i = 0; i < stage.N; i++) {
            for (int j = 0; j < stage.N; j++) {
              int v = area.A[i][j] == 0 ? -1 : stage.V[i][j] / area.A[i][j];
              fprintf(stderr, "%2d%c", v, " \n"[stage.N == j + 1]);
            }
          }

          fprintf(stderr, "\n");

          for (int i = 0; i < stage.N; i++) {
            for (int j = 0; j < stage.N; j++) {
              fprintf(stderr, "%2d%c", (int)groups[i][j], " \n"[stage.N == j + 1]);
            }
          }

          fprintf(stderr, "\n");

          for (int i = 0; i < stage.N; i++) {
            for (int j = 0; j < stage.N; j++) {
              int v = area.A[i][j] == 0 ? -1 : stage.V[i][j] / area.A[i][j];
              fprintf(stderr, "%2d%c", groups[i][j] ? v : 0, " \n"[stage.N == j + 1]);
            }
          }

          fprintf(stderr, "\n");

          for (int i = 0; i < stage.N; i++) {
            for (int j = 0; j < stage.N; j++) {
              int v = area.A[i][j] == 0 ? -1 : stage.V[i][j] / area.A[i][j];
              fprintf(stderr, "%2d%c", !groups[i][j] ? v : 0, " \n"[stage.N == j + 1]);
            }
          }

          fprintf(stderr, "\n");

          break;
        }
      }
    }

    return 0;
  }
