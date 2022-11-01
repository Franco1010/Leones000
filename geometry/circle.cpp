struct circle {
	pt o;double r;
	circle(pt o, double r):o(o),r(r){}
	circle(pt x, pt y, pt z){o=bisector(x,y)^bisector(x,z);r=(o-x).norm();}
	bool has(pt p){return (o-p).norm()<=r+EPS;}
	vector<pt> operator^(circle c){ // ccw
		vector<pt> s;
		double d=(o-c.o).norm();
		if(d>r+c.r+EPS||d+min(r,c.r)+EPS<max(r,c.r))return s;
		double x=(d*d-c.r*c.r+r*r)/(2*d);
		double y=sqrt(r*r-x*x);
		pt v=(c.o-o)/d;
		s.push_back(o+v*x-v.rot(ccw90)*y);
		if(y>EPS)s.push_back(o+v*x+v.rot(ccw90)*y);
		return s;
	}
	vector<pt> operator^(ln l){
		vector<pt> s;
		pt p=l.proj(o);
		double d=(p-o).norm();
		if(d-EPS>r)return s;
		if(abs(d-r)<=EPS){s.push_back(p);return s;}
		d=sqrt(r*r-d*d);
		s.push_back(p+l.pq.unit()*d);
		s.push_back(p-l.pq.unit()*d);
		return s;
	}
	vector<pt> tang(pt p){
		double d=sqrt((p-o).norm2()-r*r);
		return *this^circle(p,d);
	}
	bool in(circle c){ // non strict
		double d=(o-c.o).norm();
		return d+r<=c.r+EPS;
	}
	double intertriangle(pt a, pt b){ // area of intersection with oab
		if(abs((o-a)%(o-b))<=EPS)return 0.;
		vector<pt> q={a},w=*this^ln(a,b);
		if(w.size()==2)for(auto p:w)if((a-p)*(b-p)<-EPS)q.push_back(p);
		q.push_back(b);
		if(q.size()==4&&(q[0]-q[1])*(q[2]-q[1])>EPS)swap(q[1],q[2]);
		double s=0;
		for(int i = 0; i < (int)q.size() - 1; ++i) {
			if(!has(q[i])||!has(q[i+1]))s+=r*r*(q[i]-o).angle(q[i+1]-o)/2;
			else s+=abs((q[i]-o)%(q[i+1]-o)/2);
		}
		return s;
	}
};