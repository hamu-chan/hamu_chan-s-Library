vector<int> size(N), par(N), depth(N);
auto dfs1 = [&](this auto self, int a, int p) -> void {
  size[a] = 1, par[a] = p;
  if (p == -1) depth[a] = 0;
  else depth[a] = depth[p]+1;
  for (int b : G[a]) if (b != p) {
    self(b, a);
    size[a] += size[b];
  }
};
dfs1(0, -1);
vector<int> tour, head(N);
auto dfs2 = [&](this auto self, int a, int h) -> void {
  tour.push_back(a);
  head[a] = h;
  int m = -1, c = -1;
  for (int b : G[a]) if (size[a] > size[b] && size[b] > m) m = size[b], c = b;
  if (c == -1) return;
  self(c, h);
  for (int b : G[a]) if (size[a] > size[b] && b != c) self(b, b);
};
dfs2(0, 0);
vector<int> idx(N);
for (int i = 0; i<N; i++) idx[tour[i]] = i;
