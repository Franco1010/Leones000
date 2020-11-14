struct Factorize {
    using lll = __int128_t;
    random_device rnd;
    ll modpow(ll a, ll n, ll mod) {
        ll ret = 1;
        while (n > 0) {
            if (n & 1) ret = lll(ret) * lll(a) % lll(mod);
            a = lll(a) * lll(a) % lll(mod);
            n >>= 1;
        }
        return ret;
    }
    ll Rho(ll n) {
        auto f = [&](ll x) { return (lll(x) * lll(x) + lll(1)) % lll(n); };
        while (1) {
            ll x = uniform_int_distribution<ll>(0, n - 1)(rnd);
            ll y = f(x);
            while (1) {
                ll d = gcd(abs(x - y), n);
                if (d == n) break;
                if (1 < d) return d;
                x = f(x);
                y = f(f(y));
            }
        }
    }
    inline bool Miller_Rabin(ll n) {
        if (n == 1) return 0;
        ll d = n - 1, s = 0;
        while (~d & 1) d >>= 1, s++;
        auto check = [&](ll a) {
            ll x = modpow(a, d, n);
            if (x == 1) return 1;
            ll y = n - 1;
            for (int i = 0; i < s; i++) {
                if (x == y) return 1;
                x = lll(x) * lll(x) % lll(n);
            }
            return 0;
        };
        for (ll a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
            if (a >= n) break;
            if (!check(a)) return 0;
        }
        return 1;
    }
    map<ll, int> operator()(ll n) {
        map<ll, int> ret;
        while (~n & 1) {
            n >>= 1;
            ret[2]++;
        }
        queue<ll> q;
        q.push(n);
        while (sz(q)) {
            ll now = q.front();
            q.pop();
            if (now == 1) continue;
            if (Miller_Rabin(now)) {
                ret[now]++;
                continue;
            }
            ll p = Rho(now);
            q.push(p);
            q.push(now / p);
        }
        return ret;
    }
} factorize;
