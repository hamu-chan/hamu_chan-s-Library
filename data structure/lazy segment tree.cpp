template <typename S, S(*op)(S,S), S(*e)(), typename F, S(*mapp)(F,S), F(*comp)(F,F), F(*id)()> struct lazysegtree {
  int N;
  vector<S> val;
  vector<F> lazy;
  lazysegtree (int N) : N(N), val(2*N, e()), lazy(2*N, id()) {}
  void eval (int p) {
    for (int i = bit_width((unsigned)p)-1; i>0; i--) {
      int n = p>>i;
      val[n] = mapp(lazy[n], val[n]);
      lazy[n<<1] = comp(lazy[n], lazy[n<<1]);
      lazy[n<<1|1] = comp(lazy[n], lazy[n<<1|1]);
      lazy[n] = id();
    }
  }
  void reca (int p) {while (p>>=1) val[p] = op(mapp(lazy[p<<1], val[p<<1]), mapp(lazy[p<<1|1], val[p<<1|1]));}
  void set (int p, S x) {
    p += N;
    eval(p);
    val[p] = x, lazy[p] = id();
    reca(p);
  }
  S get (int p) {
    p += N;
    eval(p);
    return mapp(lazy[p], val[p]);
  }
  void apply (int l, int r, F f) {
    l += N, r += N;
    int l_ = l/(l&-l), r_ = r/(r&-r);
    eval(l), eval(r-1);
    for (; l<r; l>>=1, r>>=1) {
      if (l&1) lazy[l] = comp(f, lazy[l]), l++;
      if (r&1) r--, lazy[r] = comp(f, lazy[r]);
    }
    reca(l_), reca(r_);
  }
  S prod (int l, int r) {
    l += N, r += N;
    eval(l), eval(r-1);
    S ansl = e(), ansr = e();
    for (; l<r; l>>=1, r>>=1) {
      if (l&1) ansl = op(ansl, mapp(lazy[l], val[l])), l++;
      if (r&1) r--, ansr = op(mapp(lazy[r], val[r]), ansr);
    }
    return op(ansl, ansr);
  }
};
