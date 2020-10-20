lli mex(unordered_set<lli> &st){
  lli x = 0;
  while(st.count(x)) x++;
  return x;
}
lli grundy(int n){
  if( n == 0 ) return 0;
  unordered_set<lli> st;
  fore(i, 0, 3) st.insert(grundy(n - i));
  return mex(st);
}
