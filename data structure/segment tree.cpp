template <typename S, S(*op)(S,S), S(*e)()> struct segtree {
  int N;
  vector<S> seg;
  segtree (int N) : N(N), seg(2*N, e()) {}
  void set (int p, S x) {
    p += N;
    seg[p] = x;
    while (p >>= 1) seg[p] = op(seg[p<<1], seg[(p<<1)+1]);
  }
  S get (int p) {return seg[p+N];}
  S prod (int l, int r) {
    S ansl = e(), ansr = e();
    for (l += N, r += N; l<r; l>>=1, r>>=1) {
      if (l&1) ansl = op(ansl, seg[l++]);
      if (r&1) ansr = op(seg[--r], ansr);
    }
    return op(ansl, ansr);
  }
};
