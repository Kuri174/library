/*
#define debug(x) cerr << __LINE__ << " : " << #x << " = " << (x) << endl;
template <typename T1, typename T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &p) {
  out << "{" << p.first << ", " << p.second << "}";
  return out;
}

template <typename T>
ostream &operator<<(ostream &out, const vector<T> &v) {
  out << '{';
  for (const T &item : v) out << item << ", ";
  out << "\b\b}";
  return out;
}
*/

/* ---------------------------------- */

template <class T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v);
template <class T>
std::ostream& operator<<(std::ostream& os, std::set<T> v);
template <class L, class R>
std::ostream& operator<<(std::ostream& os, std::pair<L, R> p);
template <class K, class T>
std::ostream& operator<<(std::ostream& os, std::map<K, T> v);
template <class T>
std::ostream& operator<<(std::ostream& os, std::stack<T> s);
template <class T>
std::ostream& operator<<(std::ostream& os, std::queue<T> q);
template <class T>
std::ostream& operator<<(std::ostream& os, std::deque<T> deq);
template <class T>
std::ostream& operator<<(std::ostream& os, std::priority_queue<T> q);
template <class T>
std::ostream& operator<<(std::ostream& os, std::priority_queue<T, std::vector<T>, std::greater<T>> q);
/*
template <class T>
std::ostream& operator<<(std::ostream& os, Edge<T> e);
*/

template <class T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v) {
    os << "[";
    for (auto vv : v) os << vv << ",";
    return os << "]";
}
template <class T>
std::ostream& operator<<(std::ostream& os, std::set<T> v) {
    os << "{";
    for (auto vv : v) os << vv << ",";
    return os << "}";
}
template <class L, class R>
std::ostream& operator<<(std::ostream& os, std::pair<L, R> p) {
    return os << "(" << p.first << "," << p.second << ")";
}
template <class K, class T>
std::ostream& operator<<(std::ostream& os, std::map<K, T> v) {
    os << "{";
    for (auto vv : v) os << vv << ",";
    return os << "}";
}
template <class T>
std::ostream& operator<<(std::ostream& os, std::stack<T> s) {
    os << "[";
    while (!s.empty()) {
        os << s.top() << ",";
        s.pop();
    }
    return os << "]";
}
template <class T>
std::ostream& operator<<(std::ostream& os, std::queue<T> q) {
    os << "[";
    while (!q.empty()) {
        os << q.front() << ",";
        q.pop();
    }
    return os << "]";
}
template <class T>
std::ostream& operator<<(std::ostream& os, std::deque<T> deq) {
    os << "[";
    while (!deq.empty()) {
        os << deq.front() << ",";
        deq.pop_front();
    }
    return os << "]";
}
template <class T>
std::ostream& operator<<(std::ostream& os, std::priority_queue<T> q) {
    os << "{";
    while (!q.empty()) {
        os << q.top() << ",";
        q.pop();
    }
    return os << "}";
}
template <class T>
std::ostream& operator<<(std::ostream& os, std::priority_queue<T, std::vector<T>, std::greater<T>> q) {
    os << "{";
    while (!q.empty()) {
        os << q.top() << ",";
        q.pop();
    }
    return os << "}";
}
/*
template <class T>
std::ostream& operator<<(std::ostream& os, Edge<T> e) {
    return os << "(" << e.from << "->" << e.to << ":" << e.cost << ")";
}
*/
