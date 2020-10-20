template <class T>
struct fenwick2D{
  #define lsb(x) (x & -x)
  vector< vector<T> > fenw;

  fenwick2D(int nn = 0, int mm = 0){ // O(N * M)
    fenw.resize(nn + 5, vector<T>(mm + 5, {}));
  }

  void update(int sx, int sy, T v){  // O(logN * logM)
    For(x, sx, sz(fenw) - 1, +lsb(x)){
      For(y, sy, sz(fenw[0]) - 1, +lsb(y)){
        fenw[x][y] += v;
      }
    }
  }

  T query(int sx, int sy){ // O(logN * logM)
    T v = {};
    Rof(x, sx, 1, -lsb(x)){
      Rof(y, sy, 1, -lsb(y)){
        v += fenw[x][y];
      }
    }
    return v;
  }
};
