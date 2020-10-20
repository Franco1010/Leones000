ld distancePointCircle(const Point & c, ld r, const Point & p){
	//Point p, circle with center c and radius r
	return max((ld)0, (p - c).length() - r);
}

Point projectionPointCircle(const Point & c, ld r, const Point & p){
	//Point p (outside the circle), circle with center c and radius r
	return c + (p - c).unit() * r;
}

pair<Point, Point> pointsOfTangency(const Point & c, ld r, const Point & p){
	//Point p (outside the circle), circle with center c and radius r
	Point v = (p - c).unit() * r;
	ld d2 = (p - c).norm(), d = sqrt(d2);
	Point v1 = v * (r / d), v2 = v.perp() * (sqrt(d2 - r*r) / d);
	return {c + v1 - v2, c + v1 + v2};
}

vector<Point> intersectLineCircle(const Point & a, const Point & v, const Point & c, ld r){
	//line a+tv, circle with center c and radius r
	ld h2 = r*r - v.cross(c - a) * v.cross(c - a) / v.norm();
	Point p = a + v * v.dot(c - a) / v.norm();
	if(eq(h2, 0)) return {p}; //line tangent to circle
	else if(le(h2, 0)) return {}; //no intersection
	else{
		Point u = v.unit() * sqrt(h2);
		return {p - u, p + u}; //two points of intersection (chord)
	}
}

vector<Point> intersectSegmentCircle(const Point & a, const Point & b, const Point & c, ld r){
	//segment ab, circle with center c and radius r
	vector<Point> P = intersectLineCircle(a, b - a, c, r), ans;
	for(const Point & p : P)
		if(pointInSegment(a, b, p)) ans.push_back(p);
	return ans;
}

pair<Point, ld> getCircle(const Point & m, const Point & n, const Point & p){
	//find circle that passes through points p, q, r
	Point c = intersectLines((n + m) / 2, (n - m).perp(), (p + n) / 2, (p - n).perp());
	ld r = (c - m).length();
	return {c, r};
}

vector<Point> intersectionCircles(const Point & c1, ld r1, const Point & c2, ld r2){
	//circle 1 with center c1 and radius r1
	//circle 2 with center c2 and radius r2
	Point d = c2 - c1;
	ld d2 = d.norm();
	if(eq(d2, 0)) return {}; //concentric circles
	ld pd = (d2 + r1*r1 - r2*r2) / 2;
	ld h2 = r1*r1 - pd*pd/d2;
	Point p = c1 + d*pd/d2;
	if(eq(h2, 0)) return {p}; //circles touch at one Point
	else if(le(h2, 0)) return {}; //circles don't intersect
	else{
		Point u = d.perp() * sqrt(h2/d2);
		return {p - u, p + u};
	}
}

int circleInsideCircle(const Point & c1, ld r1, const Point & c2, ld r2){
	//test if circle 2 is inside circle 1
	//returns "-1" if 2 touches internally 1, "1" if 2 is inside 1, "0" if they overlap
	ld l = r1 - r2 - (c1 - c2).length();
	return (ge(l, 0) ? 1 : (eq(l, 0) ? -1 : 0));
}

int circleOutsideCircle(const Point & c1, ld r1, const Point & c2, ld r2){
	//test if circle 2 is outside circle 1
	//returns "-1" if they touch externally, "1" if 2 is outside 1, "0" if they overlap
	ld l = (c1 - c2).length() - (r1 + r2);
	return (ge(l, 0) ? 1 : (eq(l, 0) ? -1 : 0));
}

int pointInCircle(const Point & c, ld r, const Point & p){
	//test if Point p is inside the circle with center c and radius r
	//returns "0" if it's outside, "-1" if it's in the perimeter, "1" if it's inside
	ld l = (p - c).length() - r;
	return (le(l, 0) ? 1 : (eq(l, 0) ? -1 : 0));
}

vector<vector<Point>> tangents(const Point & c1, ld r1, const Point & c2, ld r2, bool inner){
	//returns a vector of segments or a single Point
	if(inner) r2 = -r2;
	Point d = c2 - c1;
	ld dr = r1 - r2, d2 = d.norm(), h2 = d2 - dr*dr;
	if(eq(d2, 0) || le(h2, 0)) return {};
	Point v = d*dr/d2;
	if(eq(h2, 0)) return {{c1 + v*r1}};
	else{
		Point u = d.perp()*sqrt(h2)/d2;
		return {{c1 + (v - u)*r1, c2 + (v - u)*r2}, {c1 + (v + u)*r1, c2 + (v + u)*r2}};
	}
}

ld signed_angle(const Point & a, const Point & b){
	return sgn(a.cross(b)) * acosl(a.dot(b) / (a.length() * b.length()));
}

ld intersectPolygonCircle(const vector<Point> & P, const Point & c, ld r){
	//Gets the area of the intersection of the polygon with the circle
	int n = P.size();
	ld ans = 0;
	Forn(0, n){
		Point p = P[i], q = P[(i+1)%n];
		bool p_inside = (pointInCircle(c, r, p) != 0);
		bool q_inside = (pointInCircle(c, r, q) != 0);
		if(p_inside && q_inside){
			ans += (p - c).cross(q - c);
		}else if(p_inside && !q_inside){
			Point s1 = intersectSegmentCircle(p, q, c, r)[0];
			Point s2 = intersectSegmentCircle(c, q, c, r)[0];
			ans += (p - c).cross(s1 - c) + r*r * signed_angle(s1 - c, s2 - c);
		}else if(!p_inside && q_inside){
			Point s1 = intersectSegmentCircle(c, p, c, r)[0];
			Point s2 = intersectSegmentCircle(p, q, c, r)[0];
			ans += (s2 - c).cross(q - c) + r*r * signed_angle(s1 - c, s2 - c);
		}else{
			auto info = intersectSegmentCircle(p, q, c, r);
			if(info.size() <= 1){
				ans += r*r * signed_angle(p - c, q - c);
			}else{
				Point s2 = info[0], s3 = info[1];
				Point s1 = intersectSegmentCircle(c, p, c, r)[0];
				Point s4 = intersectSegmentCircle(c, q, c, r)[0];
				ans += (s2 - c).cross(s3 - c) + r*r * (signed_angle(s1 - c, s2 - c) + signed_angle(s3 - c, s4 - c));
			}
		}
	}
	return abs(ans)/2;
}

pair<Point, ld> mec2(vector<Point> & S, const Point & a, const Point & b, int n){
	ld hi = inf, lo = -hi;
	Forn(0, n){
		ld si = (b - a).cross(S[i] - a);
		if(eq(si, 0)) continue;
		Point m = getCircle(a, b, S[i]).first;
		ld cr = (b - a).cross(m - a);
		if(le(si, 0)) hi = min(hi, cr);
		else lo = max(lo, cr);
	}
	ld v = (ge(lo, 0) ? lo : le(hi, 0) ? hi : 0);
	Point c = (a + b) / 2 + (b - a).perp() * v / (b - a).norm();
	return {c, (a - c).norm()};
}

pair<Point, ld> mec(vector<Point> & S, const Point & a, int n){
	random_shuffle(S.begin(), S.begin() + n);
	Point b = S[0], c = (a + b) / 2;
	ld r = (a - c).norm();
	For1(i, n - 1){
		if(ge((S[i] - c).norm(), r)){
			tie(c, r) = (n == S.size() ? mec(S, S[i], i) : mec2(S, a, S[i], i));
		}
	}
	return {c, r};
}

pair<Point, ld> smallestEnclosingCircle(vector<Point> S){
	assert(!S.empty());
	auto r = mec(S, S[0], S.size());
	return {r.first, sqrt(r.second)};
}

bool comp1(const Point & a, const Point & b){
	return le(a.y, b.y);
}
pair<Point, Point> closestPairOfPoints(vector<Point> P){
	sort(P.begin(), P.end(), comp1);
	set<Point> S;
	ld ans = inf;
	Point p, q;
	int pos = 0;
  Forn(i, P.size()){
		while(pos < i && geq(P[i].y - P[pos].y, ans)) S.erase(P[pos++]);
		auto lower = S.lower_bound({P[i].x - ans - eps, -inf});
		auto upper = S.upper_bound({P[i].x + ans + eps, -inf});
		for(auto it = lower; it != upper; ++it){
			ld d = (P[i] - *it).length();
			if(le(d, ans)){
				ans = d;
				p = P[i];
				q = *it;
			}
		}
		S.insert(P[i]);
	}
	return {p, q};
}

struct vantage_point_tree{
	struct node{
		Point p;
		ld th;
		node *l, *r;
	}*root;
	vector<pair<ld, Point>> aux;
	vantage_point_tree(vector<Point> &ps){
    Forn(i, ps.size()) aux.push_back({ 0, ps[i] });
		root = build(0, ps.size());
	}

	node *build(int l, int r){
		if(l == r) return 0;
		swap(aux[l], aux[l + rand() % (r - l)]);
		Point p = aux[l++].second;
		if(l == r) return new node({ p });
		for(int i = l; i < r; ++i)
			aux[i].first = (p - aux[i].second).dot(p - aux[i].second);
		int m = (l + r) / 2;
		nth_element(aux.begin() + l, aux.begin() + m, aux.begin() + r);
		return new node({ p, sqrt(aux[m].first), build(l, m), build(m, r) });
	}

	priority_queue<pair<ld, node*>> que;

	void k_nn(node *t, Point p, int k){
		if(!t)
			return;
		ld d = (p - t->p).length();
		if(que.size() < k)
			que.push({ d, t });
		else if(ge(que.top().first, d)){
			que.pop();
			que.push({ d, t });
		}
		if(!t->l && !t->r)
			return;
		if(le(d, t->th)){
			k_nn(t->l, p, k);
			if(leq(t->th - d, que.top().first))
				k_nn(t->r, p, k);
		}else{
			k_nn(t->r, p, k);
			if(leq(d - t->th, que.top().first))
				k_nn(t->l, p, k);
		}
	}

	vector<Point> k_nn(Point p, int k){
		k_nn(root, p, k);
		vector<Point> ans;
		for(; !que.empty(); que.pop())
			ans.push_back(que.top().second->p);
		reverse(ans.begin(), ans.end());
		return ans;
	}
};

vector<Point> minkowskiSum(vector<Point> A, vector<Point> B){
	int na = (int)A.size(), nb = (int)B.size();
	if(A.empty() || B.empty()) return {};
	rotate(A.begin(), min_element(A.begin(), A.end()), A.end());
	rotate(B.begin(), min_element(B.begin(), B.end()), B.end());
	int pa = 0, pb = 0;
	vector<Point> M;
	while(pa < na && pb < nb){
		M.push_back(A[pa] + B[pb]);
		ld x = (A[(pa + 1) % na] - A[pa]).cross(B[(pb + 1) % nb] - B[pb]);
		if(leq(x, 0)) pb++;
		if(geq(x, 0)) pa++;
	}
	while(pa < na) M.push_back(A[pa++] + B[0]);
	while(pb < nb) M.push_back(B[pb++] + A[0]);

	return M;
}
