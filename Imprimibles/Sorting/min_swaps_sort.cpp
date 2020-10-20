
// Calculate the minimum cant of swaps required to sort an array

int minSwaps(vi arr)
{
  int n= sz(arr);
  pair<int, int> arrPos[n];
  for (int i = 0; i < n; i++){
    arrPos[i].first = arr[i];
    arrPos[i].second = i;
  }
  sort(arrPos, arrPos + n);
  vector<bool> vis(n, false);
  int ans = 0;
  for (int i = 0; i < n; i++){
    if (vis[i] || arrPos[i].second == i) continue;
    int cycle_size = 0;
    int j = i;
    while (!vis[j]){
      vis[j] = 1;
      j = arrPos[j].second;
      cycle_size++;
    }
    if(cycle_size > 0) ans += (cycle_size - 1);
  }
  return ans;
}
