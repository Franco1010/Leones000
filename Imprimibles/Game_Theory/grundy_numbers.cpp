int mex(unordered_set<int> &st){
  int x = 0;
  while( st.find(x) != st.end() ) x++;
  return x;
}

int grundy(int n){
  if( n == 0 ) return 0;
  unordered_set<int> st;
  For1(i, 3){
    st.insert(grundy(n - i));
  }
  return mex(st);
}
