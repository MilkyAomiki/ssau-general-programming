#include <iostream>
#include <fstream>
#include <memory.h>

using namespace std;

struct COORD {
	int x;
	int y;

	~COORD() {};
};

class Poligon {
private:
	COORD* arr; // массив точек
	int size;   // размер полигона

public:
	Poligon() { size = 0; arr = 0; };
	Poligon(COORD* arr2, int newsize) {
		size = newsize;
		arr = new COORD[size];
		for (int i = 0; i < size; i++) arr[i] = arr2[i];
	}
	Poligon(const Poligon& p) {
		size = p.size;
		arr = new COORD[size];
		for (int i = 0; i < size; i++) arr[i] = p.arr[i];
	}

	~Poligon() { delete[] arr; };

	//Методы:

	int GetSize() const { return size; }

	const Poligon AddCord(int a, int b) { COORD cor; cor.x = a; cor.y = b; return *this + cor; }// добавление точки
	const Poligon DelCord(int a, int b) { COORD cor; cor.x = a; cor.y = b; return *this - cor; }//удаление

	

	double SPolygon(const Poligon &p) {//нахождение плошади полигона медодом шнуровки гаусса
		int i = 0;
		int Svn = 0;
		int Svr = 0;
		while (i < p.size) {
			int s = p.size - i - 1;
			if (i == 0) {
				Svn += p.arr[i].x * p.arr[s].y;
				Svr += p.arr[i].y * p.arr[s].x;
			}
			else {
				Svn += p.arr[s+1].x * p.arr[s].y;
				Svr += p.arr[s+1].y * p.arr[s].x;
			}
			++i;
		}
		double s = abs(Svn - Svr);
		return s/2;
	}

	bool IsDotPol(int a, int b) {//проверка на принадлежность точки полигону
		for (int i = 0; i < size; i++) {
			if (arr[i].x == a && arr[i].y == b) return true;
		}
		return false;
	}

	bool Intersection(const Poligon& p) {//пересечение графа путем проверки вхождения каждой отдельной точки
		int i, j;
		for (i = 0; i < size; ) {
			for (j = 0; i < p.size; j++) {
				if (IsDotPol(p.arr[j].x, p.arr[j].y)) return true;
			}
		}
		return false;
	}
	//операторы:
	const Poligon operator+(const Poligon& p) {//слияние полигонов
		int newsize = size + p.size;
		COORD* newarr = new COORD[newsize];
		for (int i = 0; i < size; i++) newarr[i] = arr[i];
		for (int i = 0; i < p.size; i++) newarr[size + i] = p.arr[i];

		Poligon temp(newarr, newsize);
		delete[] newarr;
		return temp;
	}

	const Poligon operator+(COORD cor) {
		Poligon temp(arr, size + 1);
		temp.arr[size] = cor;
		return temp;
	}

	const Poligon operator-(COORD cor) {
		int newsize, size2;
		COORD* newarr;

		if (!size) return *this;

		COORD* temp = arr;
		while ((*temp).x != cor.x && temp != arr + size) temp++;
		if (temp == arr + size && ((*temp).x != cor.x || (*temp).y != cor.y)) return *this; // ничего не нашли

		newsize = size - 1;
		newarr = new COORD[newsize];
		size2 = temp - arr;
		for (int i = 0; i < size2; i++) newarr[i] = arr[i];
		for (int i = size2; i < newsize; i++) newarr[i] = arr[i + 1];

		Poligon temp2(newarr, newsize);
		delete[] newarr;
		return temp2;
	}

	//Оператор присваивания

	void operator=(const Poligon& p) {
		size = p.size;
		arr = new COORD[size];
		for (int i = 0; i < size; i++) arr[i] = p.arr[i];
	}

	//Операторы > < >= <= == 
	//сравнение по площади

	bool operator>(Poligon& p) { return(SPolygon(*this) > SPolygon(p)); }
	bool operator<(Poligon& p) { return (SPolygon(*this) < SPolygon(p));}
	bool operator<=(Poligon& p) { return(SPolygon(*this) >= SPolygon(p));}
	bool operator>=(Poligon& p) { return (SPolygon(*this) >= SPolygon(p));}
	bool operator==(Poligon& p) {
		return (SPolygon(*this) == SPolygon(p));
	}

	//Операторы чтения из потока и вывода в поток
	friend ostream& operator<<(ostream&, const Poligon&);
	friend istream& operator>>(istream&, Poligon&);
};

ostream& operator<<(ostream& out, const Poligon& p) {
	int i;
	for (i = 0; i < p.size; i++) out << '(' << p.arr[i].x << "; " << p.arr[i].y << ") ";
	return out;
}

istream& operator>>(istream& in, Poligon& p) {
	int n1, n2, k = 0;
	char ch;
	streampos temp = in.tellg();

	while (in >> n1 >> n2) k++;

	in.clear();
	in.seekg(temp);

	p.size = k;
	p.arr = new COORD[p.size];

	for (int i = 0; i < p.size; i++) {
		if (in >> n1 >> n2) {
			p.arr[i].x = n1;
			p.arr[i].y = n2;
		}
	}

	ch = 0;
	while (ch != '|' && !in.eof()) in.get(ch);

	return in;
}

int main() {
	Poligon p1, p2, p3;
	int n1, n2;
	int n;

	ifstream inp("input.txt");
	ofstream outp("output.txt");

	inp >> n;
	inp >> p1;

	switch (n) {
	case 1:
		outp << p1.GetSize();
		break;

	case 2:
		inp >> n1 >> n2;
		outp << p1.AddCord(n1, n2);
		break;

	case 3:
		inp >> n1 >> n2;
		outp << p1.DelCord(n1, n2);
		break;

	case 4:
		inp >> n1 >> n2;
		outp << p1.IsDotPol(n1, n2);
		break;

	case 5:
		inp >> p2;
		outp << p1.Intersection(p2);
		break;

	case 6:
		inp >> p2;
		if (p1 > p2) outp << "size p1 > size p2";
		else if (p1 < p2) outp << "size p1 < size p2";
		else if (p1 == p2) outp << "size p1 = size p2";

	default: break;
	}

	inp.close();
	outp.close();
	return 0;
}