#include "iostream"
#include <fstream>
#include "PolyLineFunctions.h"
#include "Figure.h"
using namespace std;

Figure::Figure()
{
	Points = NULL;
	size = 0;
}

Figure::~Figure()
{
}

int Figure::GetSize()
{
	return size;
}

Point Figure::GetPoint(int i)
{
	return Points[i];
}

void Figure::SetX(int i, double x)
{
	if ((i>=0) && (i<size)) // проверка выхода за пределы массива
	{
		Points[i].x = x;
	}
}

void Figure::SetY(int i, double y)
{
	if ((i>=0) && (i<size))
	{
		Points[i].y = y;
	}
}

void Figure::SetXY(int i, double x, double y)
{
	if ((i>=0) && (i<size))
	{
		Points[i].x = x;
		Points[i].y = y;
	}
}

void Figure::Print()
{
	for (int i=0; i<size; i++)
	{
		Points[i].print(i+1);
		if (i<size-1) cout<<", ";
	}
	cout<<endl;
}

bool Figure::ReadFromFile(char* path, bool showMessage)
{
	int new_size = 0;
	bool read_error = false;
	ifstream ifin (path,ios::in); // открытие для чтения
	if (!ifin) //если при открытии файла были ошибки, то !ifin вернет значение отличное от 0
	{
		if (showMessage) cout<<"Файл "<<path<<" открыть не удалось!"<<endl;
		read_error = true;
	}
    // сравниваем символ, который находится в начале файла и будет прочитан в качестве размера с символом конца файла
	// если файл пуст - то это будет символ конца файла
	else if (ifin.peek() == EOF) 
	{
		if (showMessage) cout<<"Файл пуст!\n";
		ifin.close();
		read_error = true;
	} else {
		char str[255];
		double value_out;
		// вначале считываем количество вершин в файле
		ifin.getline(str, 255);
		if (!IsCorrectDouble(str, value_out))
		{
			if (showMessage) cout<<"При чтении файла возникли ошибки: количество вершин "<<str<<" не является числом!\n";
			return false;
		}
		new_size = (int)value_out;
		// выделяем память под массив
		Point  * arr = NULL;
		// временный массив 
		arr = new Point[new_size];
		int i=0;
		char seps[]   = " \t";
		char *token, *next_token;
		// говорит, в какую из координат сохранять считанное значение из файла
		bool x = true; // если true - сохраняем в x, false - в y
		// заполняем массив
		while (!ifin.eof() && (i<new_size) && (!read_error))
		{
			// считываем строчку из файла
			ifin.getline(str, 255);
			// выделяем первое "число" из массива
			token = strtok_s(str, seps, &next_token);
			// цикл пока из строки удается выделять "числа"
			while(token != NULL)
			{
				if (IsCorrectDouble(token, value_out))
					if (x) {
						arr[i].x = value_out;
						x = false;	
					} else {
						arr[i++].y = value_out;
						x = true;
					}
				else
				{
					if (showMessage)
						cout<<"При чтении файла возникли ошибки: "<<token<<" не является числом!";
					delete []arr;
					arr = NULL;
					read_error = true;
					break;
				}
				// выделяем следующее "число" из строки
				token = strtok_s(NULL, seps, &next_token);
			}
		}
		if (!read_error)
		{
			ifin.close();
			// обрабатываем случай, когда в файле было меньше указанного количества вершин
			if (i < new_size) {
				if (showMessage)
					cout<<"При чтении файла возникли ошибки: указано "<<new_size<<" вершин, а на самом деле их "<<i<<"!";
				delete []arr;
				read_error = true;
				arr = NULL;
			} else {
				// копируем считанные вершины в класс многоугольник из буфера (временного массива)
				CopyPoints(arr, new_size);
				if (showMessage)
					cout<<"Файл "<<path<<" был успешно считан!\n";
			}
		}
		delete []arr;
	}
	return !read_error;
}

bool Figure::SaveToFile(char* path, bool showMessage)
{
	ofstream ifout (path,ios::out); // открытие для записи
	if (!ifout) //если при создании файла были ошибки, то !ifin вернет значение отличное от 0
	{
		if (showMessage) cout<<"Файл "<<path<<" создать не удалось!"<<endl;
		return false;
	} else {
		// вначале записываем количество вершин
		ifout<<size<<endl;
		// сохраняем числа
		for (int i=0; i<size; i++)
		{
			ifout<<Points[i].x<<" ";
			ifout<<Points[i].y<<" ";
		}
		ifout<<endl;
		ifout.close();
		if (showMessage) cout<<"Файл "<<path<<" был успешно сохранен!\n";
		return true;
	}
}

// копирование в класс вершин из массива Points размера size
void Figure::CopyPoints(Point * Points, int size)
{
	delete []this->Points;
	this->size = size;
	this->Points = new Point[size];
	for (int i=0; i<size; i++)
	{
		this->Points[i].x = Points[i].x;
		this->Points[i].y = Points[i].y;
	}
}