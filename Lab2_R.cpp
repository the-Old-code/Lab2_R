#include <cstdio>
#include <clocale>
#include <iostream>

class Point {
protected:
	int x;
	int y;
public:
	Point() {//конструктор по умолчанию
		this->x = 0;
		this->y = 0;
		//std::cout << "Point()" << std::endl;
		printf("Point()\n");
	}
	Point(int x, int y) { //конструктор с параметрами
		this->x = x;
		this->y = y;
		//std::cout << "Point(int x = " << x << " ,int y = "<< y <<")" << std::endl;
		printf("Point(int x = %i, int y = %i)\n" ,x ,y);
	}
	Point(const Point& p) { //копирующий конструктор 
		this->x = p.x;
		this->y = p.y;
		printf("Point(const Point &p)\n");
		printf("x = %i, y = %i\n",x,y);
	}
	void SetX(int x) {
		this->x = x;
	}
	void SetY(int y) {
		this->y = y;
	}
	int GetX() {
		return this->x;
	}
	int GetY() {
		return this->y;
	}
	void Reset();

	virtual ~Point() {	//деструктор
		printf("~Point(%i,%i)\n", x, y);
	}
};

void Point::Reset() {
	this->x = 0;
	this->y = 0;
	printf("Reset()\n");
}

class PointZ : public Point {//потомок
private:
	int z;
public:
	PointZ() : Point() {
		this->z = 0;
		printf("PointZ()\n");
	}
	PointZ(int x, int y, int z) : Point(x, y) {
		this->z = z;
		printf("PointZ(int z = %i)\n",z);
	}
	PointZ(const PointZ& p) : Point(p) {
		/*this->x = p.x;
		this->y = p.y;*/
		this->z = p.z;
		printf("PointZ(const PointZ &p)\n");
		printf("z = %i\n",z);
	}
	void SetZ(int z) {
		this->z = z;
	}
	int GetZ() {
		return this->z;
	}
	~PointZ() {
		printf("~PointZ(%i,%i,%i)\n", x, y, z);
	}
};

class Vector {
private:
	Point* p1;
	Point* p2;
public:
	Vector() {
		p1 = new Point;
		p2 = new Point;
		printf("Vector()\n");
	}
	Vector(int x1, int x2, int y1, int y2) {
		p1 = new Point(x1, y1);
		p2 = new Point(x2, y2);
		printf("Vector(int x1,int x2,int y1, int y2)\n");
	}
	Vector(const Vector& v) {		//копирующий конструктор
		p1 = new Point(*(v.p1));	//глубокое копирование
		p2 = new Point(*(v.p2));
		printf("Vector(const Vector &v)\n");
	}
	~Vector() {
		delete p1;
		delete p2;
		printf("~Vector()\n");
	}
};

int main() {
	setlocale(LC_ALL, "");

	{
		printf("___________________________ - статический по умолчанию\n");	//статический
		Point p1;
		printf("___________________________ - статический с параметрами\n");
		Point p2 = Point(1, 2);
		printf("___________________________ - статический копирующий\n");
		Point p3 = Point(p2);
		printf("___________________________ - удаление\n");
	}
	{
		printf("___________________________ - динамический по умолчанию\n");	//динамический
		Point* p1 = new Point;
		printf("___________________________ - динамический с параметрами\n");
		Point* p2 = new Point(1, 2);
		printf("___________________________ - динамический копирующий\n");
		Point* p3 = new Point(*p2);
		printf("___________________________ - удаление\n");
		delete p1;
		delete p2;
		delete p3;
	}

	{
		printf("___________________________\n");
		Point* p = new Point(2, 3);
		printf("X:%i\n", p->GetX());
		p->Reset();

		delete p;
	}
	{
		printf("___________________________ - динамический с параметром\n");
		PointZ* p1 = new PointZ(1, 2, 3);
	
		printf("___________________________ - динамический копирующий\n");
		Point* p2 = new PointZ(*p1);
		printf("___________________________ - удаление\n");
		delete p1;
		delete p2;
	}
	{
		printf("___________________________ - динамический по умолчанию\n");
		Vector* v1 = new Vector;
		printf("___________________________ - динамический с парметром\n");
		Vector* v2 = new Vector(1, 3, 1, 5);
		printf("___________________________ - динамический копирующий\n");
		Vector* v3 = new Vector(*v2);
		printf("___________________________ - удаление\n");
		delete v1;
		delete v2;
		delete v3;
	}

	return 0;
}
