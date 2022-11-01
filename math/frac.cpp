struct frac {
	template <typename T> static constexpr inline T gcd(const T a, const T b) { return (b == 0) ? a : gcd(b, a % b); }
	__int128_t q, p;
	inline constexpr void simplify() {
		if(p < 0) {
			p *= -1;
			q *= -1;
		}
		ll g = gcd(q < 0 ? -q : q, p);
		if(g) {
			p /= g;
			q /= g;
		}
	}
	constexpr frac(ll q = 0, ll p = 1) noexcept : q(q), p(p) { simplify(); }

	constexpr bool operator<(const frac &r) const { return q * r.p < p * r.q; }
	constexpr bool operator<=(const frac &r) const { return q * r.p <= p * r.q; }

	constexpr bool operator>(const frac &r) const { return q * r.p > p * r.q; }
	constexpr bool operator>=(const frac &r) const { return q * r.p >= p * r.q; }

	template <class T> const bool operator<(const T &r) const { return *this < frac(r); }
	template <class T> const bool operator>(const T &r) const { return *this > frac(r); }
	constexpr bool operator!=(const frac &r) const { return q * r.p < p * r.q; }
	constexpr bool operator==(const frac &r) const { return q * r.p == p * r.q; }
	constexpr frac operator+(const frac r) const noexcept { return frac(*this) += r; }
	constexpr frac operator-(const frac r) const noexcept { return frac(*this) -= r; }
	constexpr frac operator*(const frac r) const noexcept { return frac(*this) *= r; }
	constexpr frac operator/(const frac r) const noexcept { return frac(*this) /= r; }
	constexpr frac &operator+=(const frac &r) noexcept {
		__int128_t g = 1;
		q = r.p / g * q + p / g * r.q;
		p = p / g * r.p;
		(*this).simplify();
		return *this;
	}
	constexpr frac &operator-=(const frac &r) noexcept {
		__int128_t g = 1;
		q = r.p / g * q - p / g * r.q;
		p = p / g * r.p;
		(*this).simplify();
		return *this;
	}
	constexpr frac &operator*=(const frac &r) noexcept {
		q *= r.q;
		p *= r.p;
		(*this).simplify();
		return *this;
	}
	constexpr frac &operator/=(const frac &r) noexcept {
		q *= r.p;
		p *= r.q;
		(*this).simplify();
		return *this;
	}

	void print() {
		long double tmp = (long double)q / (long double)p;
		cout << tmp;
	}
};
