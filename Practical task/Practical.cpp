#include <iostream>
using namespace std;

struct Data
{
	double x0, y0, Ax, Ay;
};

class Rectangle
{
private:
	Data* data;
	static int count;
	const int obj_id;

public:
	Rectangle();
	Rectangle(double x0, double y0, double Ax, double Ay);
	Rectangle(const Rectangle& obj);
	~Rectangle();
	void print() const;
	void setData(double x0, double y0, double Ax, double Ay);
	static int getCount();
	const Rectangle& operator=(const Rectangle& obj);
	friend const Rectangle operator-(const Rectangle& left, const Rectangle& right);
	const Rectangle operator-() const;
};

int Rectangle::count = 0;

Rectangle::Rectangle() : obj_id(count++), data(new Data)
{
	data->x0 = 0.0;
	data->y0 = 0.0;
	data->Ax = 10.0;
	data->Ay = 10.0;
	cout << "Вызван конструктор по умолчанию для: " << this << endl;
}

Rectangle::Rectangle(double x0, double y0, double Ax, double Ay) : obj_id(count++)
{
	setData(x0, y0, Ax, Ay);
	cout << "Вызван конструктор с параметрами для: " << this << endl;
}

Rectangle::Rectangle(const Rectangle& obj) : obj_id(count++), data(new Data)
{
	data->x0 = obj.data->x0;
	data->y0 = obj.data->y0;
	data->Ax = obj.data->Ax;
	data->Ay = obj.data->Ay;
	cout << "Вызван конструктор копирования для: " << this << endl;
}

Rectangle::~Rectangle()
{
	count--;
	delete data;
	cout << "Вызван деструктор для: " << this << endl;
	cout << "Счётчик объектов класса Rectangle = " << Rectangle::getCount() << endl;
}

void Rectangle::print() const
{
	cout << "ID объекта: " << obj_id << endl;
	cout << "x0: " << data->x0 << endl;
	cout << "y0: " << data->y0 << endl;
	cout << "Ax: " << data->Ax << endl;
	cout << "Ay: " << data->Ay << endl;
}

void Rectangle::setData(double x0, double y0, double Ax, double Ay)
{
	data = new Data;
	data->x0 = x0;
	data->y0 = y0;
	data->Ax = Ax;
	data->Ay = Ay;
}

int Rectangle::getCount()
{
	return count;
}

const Rectangle& Rectangle::operator=(const Rectangle& obj)
{
	if (this == &obj)
		return *this;

	delete data;
	data = new Data;
	data->x0 = obj.data->x0;
	data->y0 = obj.data->y0;
	data->Ax = obj.data->Ax;
	data->Ay = obj.data->Ay;
	return *this;
}

const Rectangle operator-(const Rectangle& left, const Rectangle& right)
{
	return Rectangle(left.data->x0 - right.data->x0, left.data->y0 - right.data->y0,
		left.data->Ax - right.data->Ax, left.data->Ay - right.data->Ay);
}

const Rectangle Rectangle::operator-() const
{
	return Rectangle(-data->x0, -data->y0, -data->Ax, -data->Ay);
}

int main()
{
	system("chcp 1251");
	system("cls");

	Rectangle rect0;
	rect0.print();
	cout << "Счётчик объектов класса Rectangle = " << Rectangle::getCount() << endl << endl;

	Rectangle rect1(1.0, 2.0, 5.0, 6.0);
	rect1.print();
	cout << "Счётчик объектов класса Rectangle = " << Rectangle::getCount() << endl << endl;

	Rectangle rect2(rect1);
	rect2.print();
	cout << "Счётчик объектов класса Rectangle = " << Rectangle::getCount() << endl << endl;

	Rectangle rect3(1.2, 2.3, 3.4, 4.5);
	rect3 = rect0;
	rect3.print();
	cout << "Счётчик объектов класса Rectangle = " << Rectangle::getCount() << endl << endl;

	Rectangle rect4;
	rect4 = rect3 - rect1;
	rect4.print();
	cout << "Счётчик объектов класса Rectangle = " << Rectangle::getCount() << endl << endl;

	Rectangle rect5;
	rect5 = -rect1;
	rect5.print();
	cout << "Счётчик объектов класса Rectangle = " << Rectangle::getCount() << endl << endl;

	Rectangle rect6;
	rect6.setData(3, 5, 7, 9);
	rect6.print();
	cout << "Счётчик объектов класса Rectangle = " << Rectangle::getCount() << endl << endl;

	const Rectangle rect7;
	rect7.print();
	cout << "Счётчик объектов класса Rectangle = " << Rectangle::getCount() << endl << endl;
	
	system("pause");
	return 0;
}
