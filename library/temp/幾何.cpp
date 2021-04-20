#include <bits/stdc++.h>
using namespace std;

#ifdef _DEBUG
#include "_DEBUG.hpp"
#endif
#define int long long
const long long inf = 2e18;
const int mod = 1e9 + 7;

template <typename T>
istream &operator>>(istream &is, vector<T> &v) {
  for (T &in : v) is >> in;
  return is;
}

template <class T>
vector<T> make_vec(size_t a) {
  return vector<T>(a);
}

template <class T, class... Ts>
auto make_vec(size_t a, Ts... ts) {
  return vector<decltype(make_vec<T>(ts...))>(a, make_vec<T>(ts...));
}

template <class T, class V>
typename enable_if<is_class<T>::value == 0>::type fill(T &t, const V &v) {
  t = v;
}

template <class T, class V>
typename enable_if<is_class<T>::value != 0>::type fill(T &t, const V &v) {
  for (auto &e : t) fill(e, v);
}

namespace geometry {
using Real = double;
const Real EPS = 1e-8;
const Real PI = acos(static_cast<Real>(-1));
inline int sign(const Real &r) { return r <= -EPS ? -1 : r >= EPS ? 1 : 0; }
inline bool equals(const Real &a, const Real &b) { return sign(a - b) == 0; }
}  // namespace geometry

namespace geometry {
using Point = complex<Real>;

istream &operator>>(istream &is, Point &p) {
  Real a, b;
  is >> a >> b;
  p = Point(a, b);
  return is;
}

ostream &operator<<(ostream &os, const Point &p) {
  return os << real(p) << " " << imag(p);
}

Point operator*(const Point &p, const Real &d) {
  return Point(real(p) * d, imag(p) * d);
}

// rotate point p counterclockwise by theta rad
Point rotate(Real theta, const Point &p) {
  return Point(cos(theta) * real(p) - sin(theta) * imag(p),
               sin(theta) * real(p) + cos(theta) * imag(p));
}

Real cross(const Point &a, const Point &b) {
  return real(a) * imag(b) - imag(a) * real(b);
}

Real dot(const Point &a, const Point &b) {
  return real(a) * real(b) + imag(a) * imag(b);
}

bool compare_x(const Point &a, const Point &b) {
  return equals(real(a), real(b)) ? imag(a) < imag(b) : real(a) < real(b);
}

bool compare_y(const Point &a, const Point &b) {
  return equals(imag(a), imag(b)) ? real(a) < real(b) : imag(a) < imag(b);
}

using Points = vector<Point>;
}  // namespace geometry

// angle
namespace geometry {
// smaller angle of the a-b-c
Real get_smaller_angle(const Point &a, const Point &b, const Point &c) {
  const Point v(b - a), w(c - b);
  auto alpha = atan2(imag(v), real(v));
  auto beta = atan2(imag(w), real(w));
  if (alpha > beta) swap(alpha, beta);
  Real theta = (beta - alpha);
  return min(theta, 2 * PI - theta);
}
}  // namespace geometry

namespace geometry {  // Line (直線)
struct Line {
  Point a, b;
  Line() = default;
  Line(const Point &a, const Point &b) : a(a), b(b) {}
  Line(const Real &A, const Real &B, const Real &C) {  // Ax+By=C
    if (equals(A, 0)) {
      assert(!equals(B, 0));
      a = Point(0, C / B);
      b = Point(1, C / B);
    } else if (equals(B, 0)) {
      a = Point(C / A, 0);
      b = Point(C / A, 1);
    } else {
      a = Point(0, C / B);
      b = Point(C / A, 0);
    }
  }
  friend ostream &operator<<(ostream &os, const Line &l) {
    return os << l.a << " to " << l.b;
  }
  friend istream &operator>>(istream &is, Line &l) { return is >> l.a >> l.b; }
};

using Lines = vector<Line>;
}  // namespace geometry

namespace geometry {
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C
constexpr int COUNTER_CLOCKWISE = +1;
constexpr int CLOCKWISE = -1;
constexpr int ONLINE_BACK = +2;   // c-a-b
constexpr int ONLINE_FRONT = -2;  // a-b-c
constexpr int ON_SEGMENT = 0;     // a-c-b

// ccw (回転方向)
int ccw(const Point &a, Point b, Point c) {
  b = b - a, c = c - a;
  if (sign(cross(b, c)) == +1) return COUNTER_CLOCKWISE;
  if (sign(cross(b, c)) == -1) return CLOCKWISE;
  if (sign(dot(b, c)) == -1) return ONLINE_BACK;
  if (norm(b) < norm(c)) return ONLINE_FRONT;
  return ON_SEGMENT;
}
}  // namespace geometry

namespace geometry {  // 並行判定
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A
bool is_parallel(const Line &a, const Line &b) {
  return equals(cross(a.b - a.a, b.b - b.a), 0.0);
}
}  // namespace geometry

namespace geometry {  // 直交判定
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A
bool is_orthogonal(const Line &a, const Line &b) {
  return equals(dot(a.a - a.b, b.a - b.b), 0.0);
}
}  // namespace geometry

namespace geometry {  // 点と直線の交点
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A
Point projection(const Line &l, const Point &p) {
  auto t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
  return l.a + (l.a - l.b) * t;
}
}  // namespace geometry

namespace geometry {  // 直線に対して線対称の点
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B
Point reflection(const Line &l, const Point &p) {
  return p + (projection(l, p) - p) * 2;
}
}  // namespace geometry

namespace geometry {  // segment (線分)
struct Segment : Line {
  Segment() = default;
  using Line::Line;
};

using Segments = vector<Segment>;
}  // namespace geometry

namespace geometry {  // 線分交差判定
bool is_intersect(const Segment &s, const Segment &t) {
  return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 &&
         ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}
}  // namespace geometry

namespace geometry {  // 線分が交差する点
Point cross_point(const Line &l, const Line &m) {
  Real A = cross(l.b - l.a, m.b - m.a);
  Real B = cross(l.b - l.a, l.b - m.a);
  if (equals(abs(A), 0) && equals(abs(B), 0)) return m.a;
  return m.a + (m.b - m.a) * B / A;
}
}  // namespace geometry

namespace geometry {
using Polygon = vector<Point>;
using Polygons = vector<Polygon>;
}  // namespace geometry

namespace geometry {
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B
bool is_convex_polygon(const Polygon &p) {
  int n = (int)p.size();
  for (int i = 0; i < n; i++) {
    if (ccw(p[(i + n - 1) % n], p[i], p[(i + 1) % n]) == CLOCKWISE)
      return false;
  }
  return true;
}
}  // namespace geometry

namespace geometry {
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A
Polygon convex_hull(Polygon &p, bool strict = true) {
  int n = (int)p.size(), k = 0;
  if (n <= 2) return p;
  sort(begin(p), end(p), compare_x);
  vector<Point> ch(2 * n);
  auto check = [&](int i) {
    return sign(cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1])) <= -1 + strict;
  };
  for (int i = 0; i < n; ch[k++] = p[i++]) {
    while (k >= 2 && check(i)) --k;
  }
  for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {
    while (k >= t && check(i)) --k;
  }
  ch.resize(k - 1);
  return ch;
}
}  // namespace geometry

namespace geometry {
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A
Real area(const Polygon &p) {
  int n = (int)p.size();
  Real A = 0;
  for (int i = 0; i < n; ++i) {
    A += cross(p[i], p[(i + 1) % n]);
  }
  return A * 0.5;
}
}  // namespace geometry

using namespace geometry;

signed main() {
  int n;
  cin >> n;
  Polygon P(n);
  for (auto &p : P) {
    cin >> p;
  }
  for (auto p : convex_hull(P)) {
    cout << p << endl;
    // printf("%d %d\n", p.real(), p.imag());
  }
  return 0;
}