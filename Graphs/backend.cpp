#include <iostream>
#include <vector>
#include <utility>
#include <string>

#define check Check(i, j)
class Graph {
public:
	enum gType { line, rectangle, circle, parabola, rhombus};
	std::string name;
private:
	gType type = line;
	double posX = 0, posY = 0;
	double sizeX = 1, sizeY = 1;
	bool x0y0 = false;
	bool invert = false;
public:
	Graph(std::string name_, gType type_, double posX_ = 0, double posY_ = 0, double sizeX_ = 1, double sizeY_ = 1, bool x0y0_ = false, bool invert_ = false) {
		name = name_;
		type = type_;
		posX = posX_, posY = posY_;
		sizeX = sizeX_, sizeY = sizeY_;
		x0y0 = x0y0_;
		invert = invert_;
	}
	void SetGraphPos(double x = 0, double y = 0) {
		posX = x;
		posY = y;
	}
	void SetGraphSize(double x = 1, double y = 1) {
		sizeX = x;
		sizeY = y;
	}
	void SetGraphX0Y0(bool b) {
		x0y0 = b;
	}
	void SetGraphInvert(bool b) {
		invert = b;
	}
	bool CheckLine(double x, double y) {
		double k = sizeY / sizeX;
		return y < k* x;
	}
	bool CheckRectangle(double x, double y) {
		return abs(x) < sizeX / 2 && abs(y) < sizeY / 2;
	}
	bool CheckCircle(double x, double y) {
		return x * x * (2 / sizeY) * (2 / sizeY) + y * y *(2 / sizeX) * (2 / sizeX) < 1;
	}
	bool CheckParabola(double x, double y) {
		return y < x * x * sizeY * (1 / sizeX) * (1 / sizeX);
	}
	bool CheckrRhombus(double x, double y) {
		//return CheckLine(-x + sizeX, y) && !CheckLine(-x - sizeX, y);
		return CheckLine(x + sizeX / 2, y) && !CheckLine(x - sizeX / 2, y) && CheckLine(-x + sizeX / 2, y) && !CheckLine(-x - sizeX / 2, y);
	}
	bool ApplyX0Y0(double x, double y, bool (Graph::*f)(double, double)) {
		return (*this.*f)(y, x) == ((*this.*f)(0, 0) == x0y0);
	}
	bool Check(double x, double y) {
		double posXt = posX, posYt = posY;
		double sizeXt = sizeX, sizeYt = sizeY;
		if (invert) {
			posX = posYt, posY = posXt;
			sizeX = sizeYt, sizeY = sizeXt;
			std::swap(x, y);
		}
		x -= posY;
		y -= posX;
		


		auto checkFunc = &Graph::CheckLine;
		if (type == line)      checkFunc = &Graph::CheckLine;
		if (type == rectangle) checkFunc = &Graph::CheckRectangle;
		if (type == circle)    checkFunc = &Graph::CheckCircle;
		if (type == parabola)  checkFunc = &Graph::CheckParabola;
		if (type == rhombus)   checkFunc = &Graph::CheckrRhombus;

		bool b = ApplyX0Y0(x, y, checkFunc);

		posX = posXt, posY =  posYt;
		sizeX = sizeXt, sizeY = sizeYt;
		return b;
	}
};
class Checker {
	std::vector<Graph> graphs;
public:
	Graph& addGraph(std::string name, Graph::gType type, double posX = 0, double posY = 0, double sizeX = 1, double sizeY = 1, bool x0y0 = false, bool invert = false) {
		graphs.push_back(Graph(name, type, posX, posY, sizeX, sizeY, x0y0, invert));
		graphs.end();
		return graphs[graphs.size() - 1];
	}

	bool Check(double x, double y) {
		for(Graph i : graphs) {
			if (i.Check(x, y) == false) {
				return false;
			}
		}
		return true;
	}

	bool CheckName(std::string name, double x, double y) {
		for (auto i : graphs) {
			if (i.name == name) return i.Check(x, y);
		}
		return false;
	}
};

int main() {
	Checker ch;
	//ch.addGraph(Graph::line, 0, 0, 2, 1, false);
	//ch.addGraph(Graph::rhombus, 0, 0, 20, 10);
	//ch.addGraph(Graph::parabola, -10, 1, 1, 1, false, true);
	auto p1 = ch.addGraph("p1", Graph::parabola, -5, 1, 1, 1, false, true);
	auto p2 = ch.addGraph("p2", Graph::parabola, -5.5, 0.5, 1, 1, true, false);
	auto c = ch.addGraph("c", Graph::circle, -6, 1, 4, 4, true, false);
	auto r1 = ch.addGraph("r1", Graph::rectangle, -5.5, -1.75, 4, 1.5, false, false);
	auto rh = ch.addGraph("rh", Graph::rhombus, -3.5, -0.5, 10, 5, false, false);
	auto l1 = ch.addGraph("l1", Graph::line, 0, -4.5, 1, 0.25, true, false);
	auto l2 = ch.addGraph("l2", Graph::line, 0, 2, 1, -0.666, true, false);

	for (double i = 6; i > -6; i -= 0.25 / 2) {
		for (double j = -8; j < 4; j += 0.125 / 2) {
			if (i == 0) {
				std::cout << '-';
			} else if (j == 0) {
				std::cout << '|';
			} else if (std::round(i) == i && std::round(j) == j) {
				std::cout << '.';
			}
			else {
				bool b = false;
				if (p1.check && !p2.check && l2.check) b = true;
				if (p2.check && c.check && rh.check) b = true;

				if (b) std::cout << '#';
				else  std::cout << ' ';
			}
		}
		std::cout << '\n';
	 }
}