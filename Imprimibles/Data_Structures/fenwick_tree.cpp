template <class T>
struct fenwick{
  #define lsb(x) (x & -x)
  vector<T> fenw;

  fenwick(int nn = 0){ // O(N)
    fenw.resize(nn + 5, {});
  }

  void update(int sx, T v){ // O(logN)
    For(x, sx, size(fenw) - 1, +lsb(x)){
      fenw[x] += v;
    }
  }

  T query(int sx){ // O(logN)
    T v = {};
    Rof(x, sx, 1, -lsb(x)){
      v += fenw[x];
    }
    return v;
  }

  T at(int x){ // O(1)
    T v = fenw[x];
    int y = x - lsb(x);
    for(--x; x != y; x -= lsb(x)){
      v -= fenw[x];
    }
    return v;
  }
};
