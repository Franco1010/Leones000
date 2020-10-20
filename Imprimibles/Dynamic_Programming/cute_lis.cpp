//This assumes no duplicates in array.
set<lli> s; // multiset, for duplicate.
fore(i, 0, n){
  s.insert(a[i]);
  auto it = s.upper_bound(a[i]);
  if(it != s.end()) s.erase(it);
}
// Longest Strictly Increasing Subsequence.
multiset<lli> s;
fore(i, 0, n){
  s.insert(a[i]);
  auto it = s.lower_bound(a[i]);
  it++;
  if(it != s.end()) s.erase(it);
}
cout << s.size() << endl;
