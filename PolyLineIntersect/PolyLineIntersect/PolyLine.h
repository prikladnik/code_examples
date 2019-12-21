#include "Figure.h"

// прямая
class Line: public Figure
{
public:
	Line();
	~Line();
	void ProcessInput();
};

// многоугольник
class Poly: public Figure
{
public:
	Poly();
	~Poly();
	void SetSize(int n);
	void ProcessInput();
	bool IsConvex();
};

// проверяет, что точка t находится на отрезке [p1,p2]
bool IsPointOnLine(Point t, Point p1, Point p2);

// функция подсчитывает вершины (calcVertex = true) или формирует (calcVertex = false) первый многоугольник 
// как часть основного многоугольника (по точкам пересечения)
int CalcOrFillDivPolyOne(Poly &mn, Poly &part, Point * sect, int * lineIndx, bool calcVertex);
// аналогично для второго многоугольника
int CalcOrFillDivPolyTwo(Poly &mn, Poly &part, Point * sect, int * lineIndx, bool calcVertex);

// проверка пересечения двух прямых на плоскости
// возвращает true, если прямые пересекаются, и false в противном случае
bool CheckPolyLineIntersect(Poly &mn, Line &ln, Poly &onePart, Poly &twoPart, bool showMessage);

