#include <iostream>
#include <vector>
#include <utility>
#include <string>

class Graph {
public:
	enum gType {none, line, rectangle, circle, parabola, rhombus};
	std::string name;
	gType type = line;
	double posX = 0, posY = 0;
	double sizeX = 1, sizeY = 1;
	bool x0y0 = false;
	bool invert = false;

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
		return y < x;
	}
	bool CheckRectangle(double x, double y) {
		return abs(x) < 0.5 && abs(y) < 0.5;
	}
	bool CheckCircle(double x, double y) {
		return x * x + y * y < 0.25;
	}
	bool CheckParabola(double x, double y) {
		return y < x * x;
	} 
	bool CheckRhombus(double x, double y) {
		return CheckLine(x + 0.5, y) && !CheckLine(x - 0.5, y) && CheckLine(-x + 0.5, y) && !CheckLine(-x - 0.5, y);
	}
	bool CheckNone(double x, double y) {
		return false;
	}
	bool ApplyX0Y0(double x, double y, bool (Graph::*f)(double, double)) {
		return (*this.*f)(y, x) == ((*this.*f)(0, 0) == x0y0);
	}
	bool Check(double x, double y) {
		double posXt = posX, posYt = posY;
		if (invert) {
			posX = posYt, posY = posXt;
			std::swap(x, y);
		}
		x -= posY;
		y -= posX;

		x /= sizeY;
		y /= sizeX;

		auto checkFunc = &Graph::CheckLine;
		if (type == line)      checkFunc = &Graph::CheckLine;
		if (type == rectangle) checkFunc = &Graph::CheckRectangle;
		if (type == circle)    checkFunc = &Graph::CheckCircle;
		if (type == parabola)  checkFunc = &Graph::CheckParabola;
		if (type == rhombus)   checkFunc = &Graph::CheckRhombus;
		if (type == none)      checkFunc = &Graph::CheckNone;

		bool b = ApplyX0Y0(x, y, checkFunc);

		posX = posXt, posY =  posYt;

		return b;
	}
};
class Checker {
public:
	std::vector<Graph> graphs;
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
