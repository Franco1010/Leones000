lli gcd(lli a, lli b){
  return b ? gcd(b, a % b) : a;
}

lli lcm(lli a, lli b){
  return a / gcd(a, b) * b;
}

lli gcd(lli a, lli b, lli & x, lli & y) { // ax + by = gcd(a, b)
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  lli x1, y1;
  lli d = gcd(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}
