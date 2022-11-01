long long euclid(long long a, long long b, long long& x, long long& y){ // a*(x+k*(b/d))+b*(y-k*(a/d))=d
if(!b){x=1;y=0;return a;}          // (for any k)
long long d=euclid(b,a%b,x,y);
long long t=y;y=x-(a/b)*y;x=t;
return d;
}