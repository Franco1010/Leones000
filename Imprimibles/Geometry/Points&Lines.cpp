ld eps = 1e-9, inf = numeric_limits<ld>::max();
bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b

struct Point{
	ld x, y;
	Point(): x(0), y(0){}
	Point(ld x, ld y): x(x), y(y){}

	Point operator+(const Point & p) const{return Point(x + p.x, y + p.y);}
	Point operator-(const Point & p) const{return Point(x - p.x, y - p.y);}
	Point operator*(const ld & k) const{return Point(x * k, y * k);}
	Point operator/(const ld & k) const{return Point(x / k, y / k);}

	Point operator+=(const Point & p){*this = *this + p; return *this;}
	Point operator-=(const Point & p){*this = *this - p; return *this;}
	Point operator*=(const ld & p){*this = *this * p; return *this;}
	Point operator/=(const ld & p){*this = *this / p; return *this;}

	Point rotate(const ld & angle) const{
		return Point(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
	}
	Point perp() const{return Point(-y, x);}

	ld dot(const Point & p) const{return x * p.x + y * p.y;}
	ld cross(const Point & p) const{return x * p.y - y * p.x;}
	ld norm() const{return x * x + y * y;}
	long double length() const{return sqrtl(x * x + y * y);}

	Point unit() const{return (*this) / length();}

	bool operator==(const Point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator!=(const Point & p) const{return !(*this == p);}
	bool operator<(const Point & p) const{
		if(eq(x, p.x)) return le(y, p.y);
		return le(x, p.x);
	}
	bool operator>(const Point & p) const{
		if(eq(x, p.x)) return ge(y, p.y);
		return ge(x, p.x);
	}
};

istream &operator>>(istream &is, Point & p){return is >> p.x >> p.y;}

ostream &operator<<(ostream &os, const Point & p) { return os << "(" << p.x << ", " << p.y << ")";}

int sgn(ld x){
	if(ge(x, 0)) return 1;
	if(le(x, 0)) return -1;
	return 0;
}

bool pointInLine(const Point & a, const Point & v, const Point & p){
	//line a+tv, Point p
	return eq((p - a).cross(v), 0);
}

bool pointInSegment(const Point & a, const Point & b, const Point & p){
	//segment ab, Point p
	return pointInLine(a, b - a, p) && leq((a - p).dot(b - p), 0);
}

int intersectLinesInfo(const Point & a1, const Point & v1, const Point & a2, const Point & v2){
	//lines a1+tv1 and a2+tv2
	ld det = v1.cross(v2);
	if(eq(det, 0)){
		if(eq((a2 - a1).cross(v1), 0)){
			return -1; //infinity points
		}else{
			return 0; //no points
		}
	}else{
		return 1; //single Point
	}
}

Point intersectLines(const Point & a1, const Point & v1, const Point & a2, const Point & v2){
	//lines a1+tv1, a2+tv2
	//assuming that they intersect
	ld det = v1.cross(v2);
	return a1 + v1 * ((a2 - a1).cross(v2) / det);
}

int intersectLineSegmentInfo(const Point & a, const Point & v, const Point & c, const Point & d){
	//line a+tv, segment cd
	Point v2 = d - c;
	ld det = v.cross(v2);
	if(eq(det, 0)){
		if(eq((c - a).cross(v), 0)){
			return -1; //infinity points
		}else{
			return 0; //no Point
		}
	}else{
		return sgn(v.cross(c - a)) != sgn(v.cross(d - a)); //1: single Point, 0: no Point
	}
}

int intersectSegmentsInfo(const Point & a, const Point & b, const Point & c, const Point & d){
	//segment ab, segment cd
	Point v1 = b - a, v2 = d - c;
	int t = sgn(v1.cross(c - a)), u = sgn(v1.cross(d - a));
	if(t == u){
		if(t == 0){
			if(pointInSegment(a, b, c) || pointInSegment(a, b, d) || pointInSegment(c, d, a) || pointInSegment(c, d, b)){
				return -1; //infinity points
			}else{
				return 0; //no Point
			}
		}else{
			return 0; //no Point
		}
	}else{
		return sgn(v2.cross(a - c)) != sgn(v2.cross(b - c)); //1: single Point, 0: no Point
	}
}

ld distancePointLine(const Point & a, const Point & v, const Point & p){
	//line: a + tv, Point p
	return abs(v.cross(p - a)) / v.length();
}
