#include <iostream>
#include <exception>
#include <string>
#include <set>
#include <map>

class Point {

protected:
	char name;

public:
	Point(char n) : name(n) {
		if (name == 0) throw std::invalid_argument("Point.Point: name with code \"0\" is reserved!");
	}

	std::string print() const {
		return std::string("") + name;
	}

	bool operator==(const Point& p) const {
		return name == p.name;
	}
	bool operator!=(const Point& p) const {
		return name != p.name;
	}
	bool operator<(const Point& p) const {
		return name < p.name;
	}

	static Point getEmpty() {

		Point p('a');
		p.name = 0;
		return p;
	}
};

class Graph {

protected:
	std::map<Point, std::map<Point, int>> data;

	std::string num_str(double num) const  {

		bool minus = (num < 0) ? true : false;
		int num_i = int(abs(num));
		int num_f = int((abs(num) - int(abs(num))) * 100);

		std::string str;
		if (num_f > 0) str = std::string(".") + char(num_f / 10 + 48) + char(num_f % 10 + 48);

		for (int i = num_i; i > 0; i /= 10)
			str = char(i % 10 + 48) + str;

		if (str.empty()) str = "0";
		if (minus) str = "-" + str;

		return str;
	}

public:
	void addPoint(const Point& p) {

		if (!data.count(p)) data[p] = std::map<Point, int>();
	}
	void addEdge(const Point& p1, const Point& p2, int w = 0) {

		if (p1 == p2) throw std::invalid_argument("Graph.addEdge: Edge can connect only two different points");
		addPoint(p1);
		addPoint(p2);
		data[p1][p2] = w;
	}

	void remPoint(const Point& p) {

		if (data.count(p)) data.erase(p);
		for (auto& i : data)
			if (i.second.count(p)) i.second.erase(p);
	}
	void remEdge(const Point& p1, const Point& p2) {

		if (data.count(p1))
			if (data[p1].count(p2))
				data[p1].erase(p2);
	};

	std::set<Point> getPoints() const {
	
		std::set<Point> res;
		for (auto& i : data) res.insert(i.first);
		return res;
	}
	std::set<Point> getChilds(const Point& p) const {

		std::set<Point> res;
		if (data.count(p))
			for (auto& i : data.find(p)->second) res.insert(i.first);
		return res;
	}
	std::set<Point> getParents(const Point& p) const {

		std::set<Point> res;
		if (data.count(p))
			for (auto& i : data)
				for (auto& j : i.second) {
					if (j.first == p) res.insert(i.first);
					break;
				}
		return res;
	}
	int getEdge(const Point& p1, const Point& p2) const {

		if (data.count(p1) && data.find(p1)->second.count(p2))
			return data.find(p1)->second.find(p2)->second;
		return 0;
	}

	void clear() {
		data.clear();
	}
	void reset() {
		for (auto& i : data)
			for (auto& j : i.second)
				j.second = 0;
	}

	std::string print() const {
		std::string res;
		for (auto& i : data)
			for (auto& j : i.second) {

				res += i.first.print() + ' ' + j.first.print() + ' ' + num_str(j.second) + '\n';
			}
		return res;
	}
};

class Algorithm {

protected:
	Graph orig;
	Graph flow;
	std::map<Point, int> height;
	std::map<Point, int> excess;
	Point s;
	Point e;

	void rebuild() {

		height.clear();
		excess.clear();
		flow = orig;

		for (auto& i : flow.getChilds(s)) {

			flow.addEdge(i, s, flow.getEdge(s, i));
			flow.remEdge(s, i);
		}
		
		for (auto& i : flow.getPoints()) {

			excess[i] = 0;
			height[i] = 0;
		}
		height[s] = flow.getPoints().size();

		for (auto& i : flow.getParents(s)) excess[i] = flow.getEdge(i, s);
	}

	bool jump() {

		for (auto& i : excess) {
			if (i.first != s && i.first != e && i.second > 0) {

				if (flow.getChilds(i.first).empty()) continue;
				Point min = *flow.getChilds(i.first).begin();
				for (auto& j : flow.getChilds(i.first)) {
					if (height[i.first] > height[j]) {

						min = Point::getEmpty();
						break;
					}
					if (height[min] > height[j]) min = j;
				}
				if (min == Point::getEmpty()) continue;
				
				height[i.first] = height[min] + 1;
				return true;
			}
		}
		return false;
	}
	bool push() {

		for (auto& i : excess) {
			if (i.first != s && i.first != e && i.second > 0) {

				Point to = Point::getEmpty();
				for (auto& j : flow.getChilds(i.first)) {
					if (flow.getEdge(i.first, j) > 0 && height[i.first] == height[j] + 1) {

						to = j;
						break;
					}
				}
				if (to == Point::getEmpty()) continue;

				if (flow.getEdge(i.first, to) <= excess[i.first]) {

					flow.addEdge(to, i.first, flow.getEdge(i.first, to));
					excess[i.first] -= flow.getEdge(i.first, to);
					excess[to] += flow.getEdge(i.first, to);
					flow.remEdge(i.first, to);
				}
				else {

					flow.addEdge(i.first, to, flow.getEdge(i.first, to) - excess[i.first]);
					flow.addEdge(to, i.first, excess[i.first]);
					excess[to] = excess[i.first];
					excess[i.first] = 0;
				}
				return true;
			}
		}
		return false;
	}

public:
	struct Result {
		int max_flow;
		Graph real_net;
	};

	Algorithm() : s(Point::getEmpty()), e(Point::getEmpty()) {}
	Algorithm(Graph g, Point s, Point e) : orig(g), s(s), e(e) {}

	Result execute() {

		if (!orig.getPoints().count(s) || !orig.getPoints().count(e)) 
			throw std::invalid_argument("Algorithm.execute: start or finish vertex are not in graph");
		
		rebuild();
		while (jump() || push()) {}

		for (auto& i : orig.getPoints()) {
			for (auto& j : orig.getChilds(i)) {

				flow.addEdge(i, j, flow.getEdge(j, i));
				if (flow.getEdge(j, i) > 0) flow.remEdge(j, i);
			}
		}

		return Result{ excess[e], flow };
	}
};

int main() {

	Graph graph;
	graph.addEdge('a', 'b', 5);
	graph.addEdge('a', 'c', 5);
	graph.addEdge('b', 'c', 1);
	graph.addEdge('b', 'd', 5);
	graph.addEdge('c', 'd', 1);

	std::cout << graph.print() << std::endl;

	Algorithm executer(graph, 'a', 'd');
	try {
		
		Algorithm::Result result = executer.execute();
		std::cout << result.max_flow << std::endl << result.real_net.print() << std::endl;
	}
	catch (std::invalid_argument e) {
		
		std::cout << e.what() << std::endl;
	}

	return 0;
}