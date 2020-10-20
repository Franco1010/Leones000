struct query{
  int l, r, i;
};

vector<query> queries;

void mo(){
  int block = sqrt(n);
  sort(all(queries), [&](query a, query b){
    if( a.l / block == b.l / block ){
      return a.r < b.r;
    }
    return a.l / block < b.l / block;
  });
  int l = queries[0].l, r = l - 1;
  for(query &qq: queries){ // O((N + Q) * sqrt(N))
    while( r < qq.r ){
      add(++r);
    }
    while( r > qq.r ){
      rem(r--);
    }
    while( l < qq.l ){
      rem(l++);
    }
    while( l > qq.l ){
      add(--l);
    }
    ans[qq.i] = solve();
  }
}
