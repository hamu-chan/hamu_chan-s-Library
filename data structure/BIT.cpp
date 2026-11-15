template <typename S> struct BIT {
  int N;
  vector<S> T;
  BIT (int N) : N(N), T(N+1) {}
  void add (int p, S x) {
    for (p++; p<=N; p+=p&-p) T[p] += x;
  }
  S sum (int p) {
    S ans = 0;
    for (; p>0; p-=p&-p) ans += T[p];
    return ans;
  }
  S sum (int l, int r) {return sum(r)-sum(l);}
};
