// в этой задаче требуется реализовать структуру данных, которая сможет менять
// вес точки на плоскости и считать сумму в префиксном прямоугольнике

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

struct Point {
  long long x;
  long long y;
  long long weight = 0;
};

const long long cInf = 1e9;
namespace Detail {
long long F(long long x) { return x & (x + 1); }
long long G(long long x) { return x | (x + 1); }
}  // namespace Detail
using namespace Detail;

class FenwickFenwick;

class Fenwick {
 public:
  long long GetPrefixSum(size_t r) const;
  void Update(const Point& point, long long weight);
  Fenwick() : tree_(0), points_(0) {}
  Fenwick(const std::vector<Point>& vec);

 private:
  friend FenwickFenwick;
  std::vector<long long> tree_;
  std::vector<Point> points_;
  static bool Comp(const Point& first, const Point& second);
};

Fenwick::Fenwick(const std::vector<Point>& vec)
    : tree_(vec.size()), points_(vec) {
  std::sort(points_.begin(), points_.end(), Comp);
  std::vector<long long> weights;
  for (size_t i = 0; i < points_.size(); ++i) {
    weights.push_back(points_[i].weight);
  }
  for (size_t i = 0; i < weights.size(); ++i) {
    tree_[i] = 0;
    for (size_t j = F(i); j < i + 1; ++j) {
      tree_[i] += weights[j];
    }
  }
}

long long Fenwick::GetPrefixSum(size_t r) const {
  long long sum = 0;
  for (long long i = r; i >= 0; i = F(i) - 1) {
    sum += tree_[i];
  }
  return sum;
}

void Fenwick::Update(const Point& point, long long weight) {
  size_t pos = std::lower_bound(points_.begin(), points_.end(), point, Comp) -
               points_.begin();
  long long delta = weight - points_[pos].weight;
  points_[pos].weight += delta;
  for (size_t i = pos; i < tree_.size(); i = G(i)) {
    tree_[i] += delta;
  }
}

bool Fenwick::Comp(const Point& first, const Point& second) {
  return first.y != second.y ? first.y < second.y : first.x < second.x;
}

class FenwickFenwick {
 public:
  FenwickFenwick(const std::vector<Point>& vec);
  long long GetRectangleSum(const Point& point) const;
  void Update(const Point& point, long long value);

 private:
  std::vector<Fenwick> trees_;
  std::vector<Point> points_;
  static bool Comp(const Point& first, const Point& second);
};

FenwickFenwick::FenwickFenwick(const std::vector<Point>& vec)
    : trees_(vec.size()), points_(vec) {
  std::sort(points_.begin(), points_.end(), Comp);
  for (size_t i = 0; i < points_.size(); ++i) {
    std::vector<Point> subvec;
    for (size_t j = F(i); j < i + 1; ++j) {
      subvec.push_back(points_[j]);
    }
    trees_[i] = Fenwick(subvec);
  }
}

long long FenwickFenwick::GetRectangleSum(const Point& point) const {
  size_t i = std::upper_bound(points_.begin(), points_.end(),
                              Point{point.x, cInf}, Comp) -
             points_.begin();
  if (i == 0) {
    return 0;
  }
  --i;
  long long sum = 0;
  for (long long k = i; k >= 0; k = F(k) - 1) {
    size_t j =
        std::upper_bound(trees_[k].points_.begin(), trees_[k].points_.end(),
                         Point{cInf, point.y}, Fenwick::Comp) -
        trees_[k].points_.begin();
    if (j == 0) {
      continue;
    }
    --j;
    sum += trees_[k].GetPrefixSum(j);
  }
  return sum;
}

void FenwickFenwick::Update(const Point& point, long long value) {
  size_t i = std::lower_bound(points_.begin(), points_.end(), point, Comp) -
             points_.begin();
  for (size_t j = i; j < trees_.size(); j = G(j)) {
    trees_[j].Update(point, value);
  }
}

bool FenwickFenwick::Comp(const Point& first, const Point& second) {
  return first.x != second.x ? first.x < second.x : first.y < second.y;
}

void ProcessTheQuery(FenwickFenwick& fft, std::vector<Point>& points) {
  std::string tmp;
  std::cin >> tmp;
  if (tmp == "get") {
    long long a;
    long long b;
    std::cin >> a >> b;
    std::cout << fft.GetRectangleSum(Point{a, b}) << '\n';
  } else {
    long long i;
    long long v;
    std::cin >> i >> v;
    --i;
    fft.Update(points[i], v);
  }
}

int main() {
  long long n;
  std::vector<Point> points;
  std::cin >> n;
  for (long long i = 0; i < n; ++i) {
    long long x;
    long long y;
    long long w;
    std::cin >> x >> y >> w;
    points.push_back({x, y, w});
  }
  long long q;
  std::cin >> q;
  FenwickFenwick fft(points);
  for (long long i = 0; i < q; ++i) {
    ProcessTheQuery(fft, points);
  }
}