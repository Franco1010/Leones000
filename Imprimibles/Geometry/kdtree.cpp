bool onx(pt a, pt b){return a.x<b.x;}
bool ony(pt a, pt b){return a.y<b.y;}

struct Node {
	pt pp;
	long long x0=INF, x1=-INF, y0=INF, y1=-INF;
	Node *first=0, *second=0;
	long long distance(pt p){
		long long x=min(max(x0,(long long)p.x),x1);
		long long y=min(max(y0,(long long)p.y),y1);
		return (pt(x,y)-p).norm2();
	}
	Node(vector<pt>&& vp):pp(vp[0]){
		for(pt p:vp){
			x0=min(x0,(long long)p.x); x1=max(x1,(long long)p.x);
			y0=min(y0,(long long)p.y); y1=max(y1,(long long)p.y);
		}
		if(vp.size() > 1){
			sort(vp.begin(), vp.end(),x1-x0>=y1-y0?onx:ony);
			int m=(int)(vp.size())/2;
			first=new Node({vp.begin(),vp.begin()+m});
			second=new Node({vp.begin()+m,vp.end()});
		}
	}
};
struct KDTree {
	Node* root;
	KDTree(const vector<pt>& vp):root(new Node({vp.begin(), vp.end()})) {}
	pair<long long,pt> search(pt p, Node *node){
		if(!node->first){
			//avoid query point as answer
			//if(p==node->pp) {INF,pt()};
			return {(p-node->pp).norm2(),node->pp};
		}
		Node *f=node->first, *s=node->second;
		long long bf=f->distance(p), bs=s->distance(p);
		if(bf>bs)swap(bf,bs),swap(f,s);
		auto best=search(p,f);
		if(bs<best.first) best=min(best,search(p,s));
		return best;
	}
	pair<long long,pt> nearest(pt p){return search(p,root);}
};