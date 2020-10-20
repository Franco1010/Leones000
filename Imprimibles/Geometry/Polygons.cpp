ld perimeter(vector<Point> & P){
	int n = P.size();
	ld ans = 0;
	Forn(i, n) ans += (P[i] - P[(i + 1) % n]).length();
	return ans;
}

ld area(vector<Point> & P){
	int n = P.size();
	ld ans = 0;
	Forn(i, n) ans += P[i].cross(P[(i + 1) % n]);
	return abs(ans / 2);
}

vector<Point> convexHull(vector<Point> P){
	sort(P.begin(), P.end());
	vector<Point> L, U;
	Forn(i, P.size()){
		while(L.size() >= 2 && leq((L[L.size() - 2] - P[i]).cross(L[L.size() - 1] - P[i]), 0)){
			L.pop_back();
		}
		L.push_back(P[i]);
	}
	for(int i = P.size() - 1; i >= 0; i--){
		while(U.size() >= 2 && leq((U[U.size() - 2] - P[i]).cross(U[U.size() - 1] - P[i]), 0)){
			U.pop_back();
		}
		U.push_back(P[i]);
	}
	L.pop_back();
	U.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	return L;
}

bool pointInPerimeter(vector<Point> & P, const Point & p){
	int n = P.size();
	Forn(i, n)
		if(pointInSegment(P[i], P[(i + 1) % n], p))
			return true;
	return false;
}

bool crossesRay(const Point & a, const Point & b, const Point & p){
	return ge((geq(b.y, p.y) - geq(a.y, p.y)) * (a - p).cross(b - p), 0);
}

int pointInPolygon(vector<Point> & P, const Point & p){
	if(pointInPerimeter(P, p))
		return -1; //Point in the perimeter
	int n = P.size();
	int rays = 0;
	Forn(0, n)
		rays += crossesRay(P[i], P[(i + 1) % n], p);
	return rays & 1; //0: Point outside, 1: Point inside
}

//Point in convex polygon in log(n)
//first do preprocess: seg=process(P),
//then for each query call pointInConvexPolygon(seg, p - P[0])
vector<Point> process(vector<Point> & P){
	int n = P.size();
	rotate(P.begin(), min_element(P.begin(), P.end()), P.end());
	vector<Point> seg(n - 1);
	Forn(0 , n - 1)
		seg[i] = P[i + 1] - P[0];
	return seg;
}

bool pointInConvexPolygon(const vector<Point> & seg, const Point & p){
	int n = seg.size();
	if(neq(seg[0].cross(p), 0) && sgn(seg[0].cross(p)) != sgn(seg[0].cross(seg[n - 1])))
		return false;
	if(neq(seg[n - 1].cross(p), 0) && sgn(seg[n - 1].cross(p)) != sgn(seg[n - 1].cross(seg[0])))
		return false;
	if(eq(seg[0].cross(p), 0))
		return geq(seg[0].length(), p.length());
	int l = 0, r = n - 1;
	while(r - l > 1){
		int m = l + ((r - l) >> 1);
		if(geq(seg[m].cross(p), 0)) l = m;
		else r = m;
	}
	return eq(abs(seg[l].cross(seg[l + 1])), abs((p - seg[l]).cross(p - seg[l + 1])) + abs(p.cross(seg[l])) + abs(p.cross(seg[l + 1])));
}

bool lineCutsPolygon(const vector<Point> & P, const Point & a, const Point & v){
	//line a+tv, polygon P
	int n = P.size();
	int first = 0;
	Forn(0, n+1){
		int side = sgn(v.cross(P[i%n]-a));
		if(!side) continue;
		if(!first) first = side;
		else if(side != first) return true;
	}
	return false;
}

vector<vector<Point>> cutPolygon(const vector<Point> & P, const Point & a, const Point & v){
	//line a+tv, polygon P
	int n = P.size();
	if(!lineCutsPolygon(P, a, v)) return {P};
	int idx = 0;
	vector<vector<Point>> ans(2);
	Forn(0, n){
		if(intersectLineSegmentInfo(a, v, P[i], P[(i+1)%n])){
			Point p = intersectLines(a, v, P[i], P[(i+1)%n] - P[i]);
			if(P[i] == p) continue;
			ans[idx].push_back(P[i]);
			ans[1-idx].push_back(p);
			ans[idx].push_back(p);
			idx = 1-idx;
		}else{
			ans[idx].push_back(P[i]);
		}
	}
	return ans;
}

Point centroid(vector<Point> & P){
	Point num;
	ld den = 0;
	int n = P.size();
	Forn(0, n){
		ld cross = P[i].cross(P[(i + 1) % n]);
		num += (P[i] + P[(i + 1) % n]) * cross;
		den += cross;
	}
	return num / (3 * den);
}

vector<pair<int, int>> antipodalPairs(vector<Point> & P){
	vector<pair<int, int>> ans;
	int n = P.size(), k = 1;
	auto f = [&](int u, int v, int w){return abs((P[v%n]-P[u%n]).cross(P[w%n]-P[u%n]));};
	while(ge(f(n-1, 0, k+1), f(n-1, 0, k))) ++k;
	for(int i = 0, j = k; i <= k && j < n; ++i){
		ans.emplace_back(i, j);
		while(j < n-1 && ge(f(i, i+1, j+1), f(i, i+1, j)))
			ans.emplace_back(i, ++j);
	}
	return ans;
}

pair<ld, ld> diameterAndWidth(vector<Point> & P){
	int n = P.size(), k = 0;
	auto dot = [&](int a, int b){return (P[(a+1)%n]-P[a]).dot(P[(b+1)%n]-P[b]);};
	auto cross = [&](int a, int b){return (P[(a+1)%n]-P[a]).cross(P[(b+1)%n]-P[b]);};
	ld diameter = 0;
	ld width = inf;
	while(ge(dot(0, k), 0)) k = (k+1) % n;
	Forn(i, n){
		while(ge(cross(i, k), 0)) k = (k+1) % n;
		//pair: (i, k)
		diameter = max(diameter, (P[k] - P[i]).length());
		width = min(width, distancePointLine(P[i], P[(i+1)%n] - P[i], P[k]));
	}
	return make_pair(diameter, width);
}

pair<ld, ld> smallestEnclosingRectangle(vector<Point> & P){
	int n = P.size(), i = 0, j = 0, k = 0, m = 0;
	auto dot = [&](int a, int b){return (P[(a+1)%n]-P[a]).dot(P[(b+1)%n]-P[b]);};
	auto cross = [&](int a, int b){return (P[(a+1)%n]-P[a]).cross(P[(b+1)%n]-P[b]);};
	ld perimeter = inf, area = inf;
	Forn(i, n){
		while(ge(dot(i, j), 0)) j = (j+1) % n;
		if(!i) k = j;
		while(ge(cross(i, k), 0)) k = (k+1) % n;
		if(!i) m = k;
		while(le(dot(i, m), 0)) m = (m+1) % n;
		//pairs: (i, k) , (j, m)
		Point v = P[(i+1)%n] - P[i];
		ld h = distancePointLine(P[i], v, P[k]);
		ld w = distancePointLine(P[j], v.perp(), P[m]);
		perimeter = min(perimeter, 2 * (h + w));
		area = min(area, h * w);
	}
	return make_pair(area, perimeter);
}
