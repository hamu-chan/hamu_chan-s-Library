struct UnionFind {
  vector<int> P;
  UnionFind (int N) : P(N) {for (int i = 0; i<N; i++) P[i] = i;}
  int root (int x) {if (P[x] == x) return x; return P[x] = root(P[x]);}
  void unite (int x, int y) {P[root(x)] = root(y);}
  bool same (int x, int y) {return root(x) == root(y);}
};
