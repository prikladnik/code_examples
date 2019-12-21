#include "iostream"
using namespace std;

// структура определяет одну точку на плоскости
struct Point {
	double x; // координата по x
	double y; // координата по y
  // конструктор
  Point() { 
    // обнуление координат
    x=0;
    y=0;
  };
  void print(int num = 0) // функция вывода точки
  {
	if (num!=0)
		cout<<"V"<<num;
	cout.precision(2); // сколько выводить цифр после после запятой
	cout<<"("<<x<<","<<y<<")";
  }
  // перегрузка оператора сравнения
  const bool operator != (const Point &p)
  {
	  return !((x == p.x) && (y == p.y));
  }
};

class Figure
{
protected:
	Point * Points; // вершины фигуры
	int size; // количество вершин
public:
	Figure();
	~Figure();
	int GetSize(); // получение количества вершин
	Point GetPoint(int i); // получение вершины по ее индексу
	void SetX(int i, double x); // установление координаты x в вершине с индексом i
	void SetY(int i, double y); // установление координаты y в вершине с индексом i
	void SetXY(int i, double x, double y); // установление координат x y в вершине с индексом i
	virtual void ProcessInput() = 0; // чистая виртуальная функция, которая делает класс Figure абстрактным
	void Print(); // печать на экран
	bool ReadFromFile(char* path, bool showMessage); 
	bool SaveToFile(char* path, bool showMessage);
	void CopyPoints(Point * Points, int size); // копирование в класс вершин из массива Points размера size
};
