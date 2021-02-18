/*
2a) Create an abstract class named Shape. 
This class should have three functions: a pure virtual print function that takes and returns a std::ostream, 
an overloaded operator<< and an empty virtual destructor.
*/
#include<iostream>
#include<vector>

class Shape {
public:
	virtual ~Shape() {}
	virtual std::ostream& print(std::ostream &out) const = 0;

	friend std::ostream& operator<<(std::ostream &out, const Shape &shape) {
		return shape.print(out);
	}
};

/*
2b) Derive two classes from Shape: a Triangle, and a Circle. The Triangle should have 3 Points as members. 
The Circle should have one center Point, and an integer radius. Overload the print() function so the following program runs:

This should print:

Circle(Point(1, 2, 3), radius 7)
Triangle(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9))

*/
//Point class provided by problem
class Point
{
private:
	int m_x{ 0 };
	int m_y{ 0 };
	int m_z{ 0 };

public:
	Point(int x, int y, int z)
		: m_x{ x }, m_y{ y }, m_z{ z }
	{

	}

	friend std::ostream& operator<<(std::ostream &out, const Point &p)
	{
		out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ')';
		return out;
	}
};

class Triangle : public Shape {
private:
	Point m_points[3];
	
public:
	Triangle(const Point one, const Point two, const Point three) : m_points{ one, two, three } {}
	~Triangle() override {}

	virtual std::ostream& print(std::ostream& out) const override {
		out << "Triangle(" << m_points[0] << ", " << m_points[1] << ", " << m_points[2] << ')';
		return out;
	}
};

class Circle : public Shape {
private:
	Point m_center;
	int m_radius;

public:
	Circle(const Point center, const int rad) : m_center{ center }, m_radius{ rad } {}
	~Circle() override {}

	int getRadius() const { return m_radius; }

	virtual std::ostream& print(std::ostream& out) const override {
		out << "Circle(" << m_center << ", " << m_radius << ')';
		return out;
	}
};
/*
int main()
{
	Circle c{ Point{ 1, 2, 3 }, 7 };
	std::cout << c << '\n';

	Triangle t{Point{1, 2, 3}, Point{4, 5, 6}, Point{7, 8, 9}};
	std::cout << t << '\n';

	return 0;
}
*/
/*
2c) Given the above classes (Point, Shape, Circle, and Triangle), finish the following program:
*/
int getLargestRadius(const std::vector<Shape*> &v) {
	int maxRadius{ 0 };

	for (auto& shape : v) {
		if (dynamic_cast<Circle*>(shape) && dynamic_cast<Circle*>(shape)->getRadius() > maxRadius) {
			maxRadius = dynamic_cast<Circle*>(shape)->getRadius();
		}
	}

	return maxRadius;
}

int main()
{
	std::vector<Shape*> v{
	  new Circle{Point{1, 2, 3}, 7},
	  new Triangle{Point{1, 2, 3}, Point{4, 5, 6}, Point{7, 8, 9}},
	  new Circle{Point{4, 5, 6}, 3}
	};

	// print each shape in vector v on its own line here
	std::cout << *v[0] << '\n';
	std::cout << *v[1] << '\n';
	std::cout << *v[2] << '\n';

	std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // write this function

// delete each element in the vector here
	for (auto& element : v) {
		delete element;
	}

	return 0;
}