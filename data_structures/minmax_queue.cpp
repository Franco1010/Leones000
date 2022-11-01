struct qiu{
	stack<ii> s1,s2;
	int query(){
		int minimum;
		if (s1.empty() || s2.empty()) minimum = s1.empty() ? s2.top().second : s1.top().second;
		else minimum = min(s1.top().second, s2.top().second);
		return minimum;
	}

	void pop(){
		if (s2.empty())while (!s1.empty()) {
        int element = s1.top().first;
        s1.pop();
        int minimum = s2.empty() ? element : min(element, s2.top().second);
        s2.push({element, minimum});
    	}
		int remove_element = s2.top().first;
		s2.pop();
	}

	void add(int new_element){
		int minimum = s1.empty() ? new_element : min(new_element, s1.top().second);
		s1.push({new_element, minimum});
	}
};

