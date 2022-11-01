typedef long double td;
const td eps = 1e-9, inf = numeric_limits<ld>::max(), pi = acos(-1);
// For use with integers, just set eps=0 and everything remains the same
bool geq(td a, td b){return a-b >= -eps;}     //a >= b
bool leq(td a, td b){return b-a >= -eps;}     //a <= b
bool ge(td a, td b){return a-b > eps;}        //a > b
bool le(td a, td b){return b-a > eps;}        //a < b
bool eq(td a, td b){return abs(a-b) <= eps;}  //a == b
bool neq(td a, td b){return abs(a-b) > eps;}  //a != b