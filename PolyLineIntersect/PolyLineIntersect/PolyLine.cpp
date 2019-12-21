#include "iostream"
#include "PolyLineFunctions.h"
#include "PolyLine.h"
using namespace std;

Line::Line():Figure()
{
	size=2;
	Points = new Point[2];
}

Line::~Line()
{
	delete[] this->Points;
	Points = NULL;
	this->size = 0;
}

// ввод координат прямой
void Line::ProcessInput()
{
	// предполагаем, что ввод пользователя некорректный
	bool inputSuccess=false;
    int j = 1;
	while (!inputSuccess)
	{
		cout<<"Введите координаты прямой:\n";
		// цикл по заполнению координат пары точек одного отрезка
		for (int i=0; i<=1; i++)
		{
 			cout<<"Введите х"<<j<<": ";
			Points[i].x = InputDouble();
			cout<<"Введите y"<<j<<": ";
			Points[i].y = InputDouble();
			j++;
		}
		inputSuccess = !(((Points[0].x==Points[1].x) && (Points[0].y==Points[1].y)));
		if (!inputSuccess)
			cout<<"Введена точка, пересечение отрезков выполнить невозможно!\n";
	}
}

Poly::Poly():Figure()
{
}

Poly::~Poly()
{
	delete[] Points;
	Points = NULL;
	size = 0;
}

void Poly::SetSize(int n)
{
	if (n>=0)
	{
		delete []Points;
		if (n>0)
			Points = new Point[n];
		else
			Points = NULL;
		size = n;
	}
}

// ввод количества вершин многоугольника и их координат 
void Poly::ProcessInput()
{
	size = 1;
	while (size < 3)
	{
		cout<<"Введите количество вершин многоугольника: ";
		size = (int)InputDouble();
		if (size < 3)
			cout<<"В многоугольнике должно быть не меньше трех вершин!\n";
	}
	delete []Points;
	Points = new Point[size];
	// предполагаем, что ввод пользователя некорректный
	bool inputSuccess=false;
    int j = 1, i;
	while (!inputSuccess)
	{
		cout<<"Введите координаты вершин:\n";
		// цикл по заполнению координат пары точек одного отрезка
		for (i=0; i<size; i++)
		{
 			cout<<"Введите х"<<j<<": ";
			Points[i].x = InputDouble();
			cout<<"Введите y"<<j<<": ";
			Points[i].y = InputDouble();
			j++;
		}
		// проверяем, чтобы вершины не совпадали между собой
		inputSuccess = true; 
		for (i=0; i<size-1; i++)
		{
			for (j=i+1; j<size; j++)
			{
				inputSuccess = !(((Points[i].x==Points[j].x) && (Points[i].y==Points[j].y)));
				if (!inputSuccess)
				{
					cout<<"Вершины ";
					Points[i].print(i+1);
					cout<<" и ";
					Points[j].print(j+1);
					cout<<" совпадают!\n";
					break;
				}
			}
			if (!inputSuccess) break;
		}
	}
}

/*
   Return whether a polygon in 2D is concave or convex
   return 0 for incomputables eg: colinear points
          CONVEX == 1
          CONCAVE == -1
   It is assumed that the polygon is simple
   (does not intersect itself or have holes)
*/
bool Poly::IsConvex()
{
   int i,j,k;
   int result = 0;
   double z;

   for (i=0; i<size; i++) {
      j = (i + 1) % size;
      k = (i + 2) % size;
      z  = (Points[j].x - Points[i].x) * (Points[k].y - Points[j].y);
      z -= (Points[j].y - Points[i].y) * (Points[k].x - Points[j].x);
      if (z < 0)
         result |= 1;
      else if (z > 0)
         result |= 2;
      if (result == 3)
         return false;
   }
   return (result != 0);
}

// проверяет, что точка t находится на отрезке [p1,p2]
bool IsPointOnLine(Point t, Point p1, Point p2)
{
    bool onLine=false; // первоначально считаем, что точка не принадлежит отрезку
    /*
      Покоординатное равенство проверки принадлежности точки отрезку
      p*x1+(1-p)*x2=x
      p*y1+(1-p)*y2=y
      Из первого уравнения находим p, подставляем во второе: если получаем равенство и
      0<=p<=1, то t на отрезке, иначе - нет.
      http://algolist.manual.ru/maths/geom/belong/otr2d.php
    */
    if ((p1.x-p2.x)!=0)
    {
        double p;
        p=(t.x-p2.x)/(p1.x-p2.x);
		// вторую часть условия проверяем с учетом допустимой погрешности
		if ( ( (p>=0) && (p<=1) ) && (fabs((p*p1.y+(1-p)*p2.y)-t.y)<0.000000001) )
			onLine=true;
    }
    else // случай с перпендикулярным оси ОХ отрезком
        onLine=( ((t.y<=p1.y)&&(t.y>=p2.y)) || ((t.y>=p1.y)&&(t.y<=p2.y)) );
    return onLine;
}

// проверка пересечения двух прямых на плоскости
// возвращает true, если прямые пересекаются, и false в противном случае
bool IsLineIntersect(Point p1, Point p2, Point p3, Point p4, Point &t, bool &isParallel)
{
    double a1, b1, c1, a2, b2, c2;
    bool isIntersect=false;
	isParallel = false;
    // находим коэффециенты общих уравнений прямых
    a1=p1.y-p2.y;
    b1=p2.x-p1.x;
    c1=p1.x*p2.y-p2.x*p1.y;
    a2=p3.y-p4.y;
    b2=p4.x-p3.x;
    c2=p3.x*p4.y-p4.x*p3.y;
    // если прямые пересекаются
    if (a1*b2-a2*b1!=0)
    {
        // находим точку пересечения прямых
        t.x=(b1*c2-b2*c1)/(a1*b2-a2*b1);
        t.y=(c1*a2-c2*a1)/(a1*b2-a2*b1);
        // проверяем, что она находится на первом отрезке
        isIntersect=IsPointOnLine(t,p1,p2);
    } else // проверяем ситуацию, когда прямая "лежит" на стороне многоугольника
	{
		// проверяем: не лежит ли вершина стороны на прямой (для этого подставляем координаты вершины в общее уравнение прямой)
		if (a2*p1.x + b2*p1.y + c2 == 0)
			isParallel = true;
	}
    return isIntersect;
}

// в зависимости от параметров, функция будет либо считать количество вершин у нового многоугольника (параметром будет номера пересеченных сторон), либо заполнять его
int CalcOrFillDivPolyOne(Poly &mn, Poly &part, Point * sect, int * lineIndx, bool calcVertex)
{
	// количество вершин в многоугольнике, который будет сформирован
	int vertexCount=0, i, j=0;
	// проходим от первой вершины до первой точки пересечения
	for (i=0; i<=lineIndx[0]; i++)
	{
		// сравниваем текущую вершину с первой точкой пересечения
		if (mn.GetPoint(i) != sect[0])
		{
			// если true - подсчитываем количество вершин в многоугольнике, который будет сформирован при последующем вызове этого метода
			if (calcVertex)
				vertexCount++;
			else
				// устанавливаем координаты очередной вершины в формируемом многоугольнике
				part.SetXY(j++, mn.GetPoint(i).x, mn.GetPoint(i).y);
		}
	}
	if (calcVertex)
		vertexCount++;
	else
		// берем первую точку пересечения
		part.SetXY(j++, sect[0].x, sect[0].y);
	if (calcVertex)	
		vertexCount++;
	else
		// берем вторую точку пересечения
		part.SetXY(j++, sect[1].x, sect[1].y);
	// добавляем в многоугольник вершины следующие после пересечения
	for (i=lineIndx[1]+1; i<mn.GetSize(); i++)
	{
		if (mn.GetPoint(i) != sect[1])
		{
			if (calcVertex)
				vertexCount++;
			else
				part.SetXY(j++, mn.GetPoint(i).x, mn.GetPoint(i).y);
		}
	}
	return vertexCount;
}

int CalcOrFillDivPolyTwo(Poly &mn, Poly &part, Point * sect, int * lineIndx, bool calcVertex)
{
	int vertexCount=0, i, j=0;
	// берем первую точку пересечения
	if (calcVertex)
		vertexCount++;
	else
		part.SetXY(j++, sect[0].x, sect[0].y);
	// проходим от этой точки до следующей точки пересечения
	for (i=lineIndx[0]+1; i<=lineIndx[1]; i++)
	{
		if (mn.GetPoint(i) != sect[1])
		{
			if (calcVertex)
				vertexCount++;
			else
				part.SetXY(j++, mn.GetPoint(i).x, mn.GetPoint(i).y);
		}
	}
    // добавляем вторую точку пересечения
	if (calcVertex)
		vertexCount++;
	else
		part.SetXY(j++, sect[1].x, sect[1].y);
	return vertexCount;
}

bool CheckPolyLineIntersect(Poly &mn, Line &ln, Poly &onePart, Poly &twoPart, bool showMessage)
{
	if (!mn.IsConvex())
	{
		if (showMessage)
			cout<<"\nМногоугольник должен быть выпуклым! Проверить пересечение невозможно! \n";
		return false;
	}
	Point p;
	int i=0, k1=0, k2=0; // номера вершин, из которых сформирован текущий отрезок многоугольника (проверяем пересечение прямой с ним)
	// массив с точками пересечения
	Point * sect = new Point[2];
	// номера отрезков многоугольника, через которые проходит прямая
	int * lineIndx = new int[2];
	bool trueIntersect = false;
	// количество точек пересечения
	int vertexCount = 0;
	bool isParallel;
	while (i<mn.GetSize())
	{
		// для последнего отрезка второй вершиной отрезка будет первая вершина многоугольника
		if (i==mn.GetSize()-1)
			k2=0;
		else
			k2=k1+1;
		// если есть точка пересечения между отрезком [mn.GetPoint(k1), mn.GetPoint(k2)] и прямой [ln.GetPoint(0), ln.GetPoint(1)]
		if (IsLineIntersect(mn.GetPoint(k1), mn.GetPoint(k2), ln.GetPoint(0), ln.GetPoint(1), p, isParallel))
		{
			if (vertexCount==0) // если это первое найденное пересечение
				trueIntersect = true;
			else
				// проверка на случай, если вторая точка пересечения совпадает с первой
				trueIntersect = (sect[0].x != p.x) || (sect[0].y != p.y);
			if (trueIntersect)
			{
				sect[vertexCount].x = p.x;
				sect[vertexCount].y = p.y;
				lineIndx[vertexCount++] = k1;
				trueIntersect = false;
				if (showMessage)
				{
					cout<<"\nСторона многоугольника:\n";
					mn.GetPoint(k1).print();
					mn.GetPoint(k2).print();
					cout<<"\nТочка пересечения с прямой:\n";
					p.print();
					cout<<endl;
				}
			}
		}
		else
			// если прямая параллельна одной из сторон
			if (isParallel)
			{
				if (showMessage)
					cout<<"\nПрямая параллельна одной из сторон многоугольника, разделять многоугольник не нужно!\n";
				break;
			}
		k1++;
		i++;
	}
	if ((vertexCount > 0) && (!isParallel))
	{
		if (vertexCount > 1)
		{
			onePart.SetSize(CalcOrFillDivPolyOne(mn, onePart, sect, lineIndx, true));
			CalcOrFillDivPolyOne(mn, onePart, sect, lineIndx, false);
			twoPart.SetSize(CalcOrFillDivPolyTwo(mn, twoPart, sect, lineIndx, true));
			CalcOrFillDivPolyTwo(mn, twoPart, sect, lineIndx, false);
		} else
			if (showMessage) cout<<"Только одна точка пересечения, разделять многоугольник не нужно!\n";
	} else
		if ((!isParallel) && (showMessage)) cout<<"Точек пересечения нет!\n";
	delete[] sect;
	delete[] lineIndx;
	return ((vertexCount > 1) && (!isParallel));
}