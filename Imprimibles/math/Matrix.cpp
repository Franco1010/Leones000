struct Matrix {
  vector<vector<lli>> mat;
  int n, m;
  Matrix(int _n, int _m, lli v = 0): n(_n), m(_m), mat(_n, vector<lli>(_m, v)) {}
  vector<lli>& operator[](int p) {return mat[p];}
  Matrix operator*(Matrix &b){//this de n x m entonces b de m x t
    int t = b.m;
    Matrix c = Matrix(n, t);
    Forn(i, n) Forn(j, t) Forn(k, m)
      c[i][j] = (c[i][j] + 1ll * mat[i][k] * b[k][j]) % mod;
    return c;
  }
  Matrix operator+(Matrix &b){//this de n x m entonces b de n x m
    Matrix r(b.n, b.m);
    Forn(i, n) Forn(j, m) r[i][j] = mat[i][j] + b[i][j];
    return r;
  }
  double determinant(){//sacado de e maxx ru (Matrix debe tener tipo double)
    double det = 1;
    Matrix r = (*this);
    Forn(i, n){//para cada columna
      int k = i;
      for(int j = i + 1; j < n; ++j){//busco la fila con mayor val abs
        if(abs(r[j][i]) > abs(r[k][i])) k = j;
      }
      if(abs(r[k][i]) < 1e-9) return 0;
      swap(r[k], r[i]);//la swapeo
      if(i != k) det = -det;
      det *= r[i][i];
      for(int j = i + 1; j < n; ++j) r[i][j] /= r[i][i];
      //hago 0 todas las otras filas
      Forn(j, n) if (j!= i && abs(r[j][i]) > 1e-9)
      for(int k = i + 1; k < n; ++k) r[j][k] -= r[i][k] * r[j][i];
    }
    return det;
  }
};

Matrix unit(int n){ //Matrices unitarias son cuadradas
  Matrix r = Matrix(n, n);
  Forn(i, n) r[i][i] = 1;
  return r;
}

Matrix fpow(Matrix x, lli y){//Solo se pueden elevar matrices cuadradas
  Matrix r = unit(x.n);
  while(y > 0){
    if(y & 1) r = r * x;
    x = x * x;
    y >>= 1;
  }
  return r;
}
