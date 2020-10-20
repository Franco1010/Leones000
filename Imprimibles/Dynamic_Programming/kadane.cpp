template <class T>
void kadane(){
  T mx = a[0], sum = a[0];
  For1(i, n - 1){
    sum = max(a[i], sum + a[i]);
    mx = max(mx, sum);
  }
  return mx;
}
