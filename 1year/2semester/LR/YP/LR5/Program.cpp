#include <fstream>
#include <cctype>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

const char* INP_FILENAME = "input.txt";
const char* OUTP_FILENAME = "output.txt";
const char* FILE_DELIMETER = " ";

/// @brief Читает весь файл с данным названием filename в C-строку 
/// @param filename Путь/название файла
/// @return C-строка с содержимым файла
char* read_whole_file(const char* filename)
{
    ifstream input(filename, ios::binary);

    //Читаем размер файла
    input.seekg(0, ios::end);
    size_t byte_filesize = input.tellg();
    input.seekg(0, ios::beg);

    //Читаем сам файл
    char* content = new char[byte_filesize+1];
    input.read(content, byte_filesize);

    input.close();

    content[byte_filesize] = '\0';

    return content;
}

struct vertex
{
    int x;
    int y;

    vertex() : x(0), y(0)
    {}

    vertex(int x, int y) : x(x), y(y)
    {}

    bool operator==(const vertex& v) const
    {
        return x == v.x && y == v.y;
    }

    bool operator!=(const vertex& v) const
    {
        return !(*this == v);
    }

    friend istream& operator >> (istream &in, vertex& v);
    friend ostream& operator << (ostream &out, const vertex& v);
};

istream& operator >> (istream &in, vertex& v)
{
    in >> v.x;
    in >> v.y;

    return in;
}

ostream& operator << (ostream &out, const vertex& v)
{
    out << v.x;
    out << ' ';
    out << v.y;
    return out;
}

class polygon
{
    private:
        vertex* vertices;
        int vertices_size;

        /// @brief Копирует src_arr в новый массив
        /// @tparam T Тип элементов массива
        /// @param src_arr Откуда копировать
        /// @param src_size Размер исходного массива
        /// @param new_size Новый размер массива
        /// @return Копию массива
        template<typename T>
        T* create_copy(T* src_arr, int src_size, int new_size)
        {
            T* container = new T[new_size];
            memcpy(container, src_arr, sizeof(struct vertex) * src_size);
            return container;
        }

        /// @brief Устанавливает в поля класса копию src_vertices
        /// @param src_vertices Массив вершин
        /// @param src_size Размер массива вершин
        void set_vertices_copy(vertex* src_vertices, int src_size)
        {
            vertices = create_copy(src_vertices, src_size, src_size);
            vertices_size = src_size;
        }

        /// @brief Добавляет вершину в список вершин полигона
        /// @param vertex Вершина
        void add_vertex(const vertex& vertex)
        {
            vertices = create_copy(vertices, vertices_size, vertices_size+1);
            vertices[vertices_size] = vertex;
            vertices_size+=1;
        }

        /// @brief Удаляет вершину из списка вершин полигона
        /// @param i Индекс вершины
        void remove_vertex(int i)
        {
            //копируем слева от i
            vertex* container = create_copy(vertices, i, vertices_size-1);

            if (i+1 != vertices_size)
            {
                //копируем справа от i
                memcpy(container+i, vertices+i+1, sizeof(struct vertex) * vertices_size-i-1);
            }

            vertices = container;
            vertices_size -= 1;
        }

        /// @brief Вычисляет периметр полигона
        float calc_perimeter() const
        {
            float p = 0;
            for (int i = 0, j = 1; j < vertices_size; i++, j++)
            {
                p += sqrt(pow(vertices[j].x - vertices[i].x, 2) + pow(vertices[j].y-vertices[i].y, 2));
            }

            return p;
        }

    public:
        polygon() : vertices(new vertex[0]), vertices_size(0)
        {}

        polygon(polygon& orig)
        {
            set_vertices_copy(orig.vertices, orig.vertices_size);
        }

        polygon(vertex* vert, int size)
        {
            set_vertices_copy(vert, size);
        }

        /// @brief Вовращает количество вершин
        int get_size()
        {
            return vertices_size;
        }

        void operator=(const polygon& poly)
        {
            if (this != &poly)
            {
                delete [] vertices;
                vertices_size = 0;
                set_vertices_copy(poly.vertices, poly.vertices_size);
            }
        }

        /// @brief Добавляет вершину vertex
        /// @param vertex Вершина
        polygon& operator+=(const vertex& vertex)
        {
            add_vertex(vertex);
            return *this;
        }
        
        /// @brief Удаляет вершину по индексу i
        /// @param i Индекс вершины
        polygon& operator-=(int i)
        {
            remove_vertex(i);
            return *this;
        }

        bool operator&&(const polygon& poly)
        {
            return intersects(poly);
        }

        bool operator&&(const vertex& v)
        {
            return contains(v);
        }

        bool operator>(const polygon& poly)
        {
            float p1 = this->calc_perimeter();
            float p2 = poly.calc_perimeter();

            return p1 > p2;
        }

        bool operator>=(const polygon& poly)
        {
            return *this == poly || *this > poly;
        }

        bool operator<(const polygon& poly)
        {
            float p1 = this->calc_perimeter();
            float p2 = poly.calc_perimeter();

            return p1 < p2;
        }

        bool operator<=(const polygon& poly)
        {
            return *this == poly || *this < poly;
        }

        bool operator==(const polygon& poly) const
        {
            if (poly.vertices_size != vertices_size)
                return false;

            for (int i = 0; i < vertices_size; i++)
            {
                if (poly.vertices[i] != vertices[i])
                    return false;
            }
            
            return true;
        }

        /// @brief Возвращает индекс вершины v, сравнение по значению
        /// @param v вершина
        int get_index(vertex& v)
        {
            int i = 0;
            for (; i < vertices_size; i++)
            {
                if (vertices[i] == v)
                    return i;
            }
            
            return i;
        }

        /// @brief Проверяет, содержится ли точка v в данном полигоне
        /// @param v Точка в 2д пространстве
        /// @return true если содержится, false иначе
        bool contains(const vertex& v) const
        {
            bool inside = false;
            for (int i = 0, j = vertices_size - 1; i < vertices_size; j = i++)
            {
                int xi = vertices[i].x, yi = vertices[i].y;
                int xj = vertices[j].x, yj = vertices[j].y;

                bool intersect = ((yi > v.y) != (yj > v.y))
                    && (v.x < (xj - xi) * (v.y - yi) / (yj - yi) + xi);

                if (intersect) inside = !inside;
            }

            return inside;
        }

        /// @brief Проверяет, пересекается ли полигон poly с данным полигоном
        /// @param poly Полигон
        /// @return true если пересекается, false иначе
        bool intersects(const polygon& poly)
        {
            for (int i = 0; i < vertices_size; i++)
            {
                if (poly.contains(vertices[i]))
                    return true;
            }

            for (int i = 0; i < poly.vertices_size; i++)
            {
                if (contains(poly.vertices[i]))
                    return true;
            }
            
            return false;
        }

        friend istream& operator >> (istream &in, polygon& p);
        friend ostream& operator << (ostream &out, const polygon& p);

        ~polygon()
        {
            delete [] vertices;      
        }

};

istream& operator >> (istream &in, polygon& p)
{
    delete [] p.vertices;

    in >> p.vertices_size;
    p.vertices = new vertex[p.vertices_size];
    for (int i = 0; i < p.vertices_size; i++)
    {
        in >> p.vertices[i];
    }

    return in;
}

ostream& operator << (ostream &out, const polygon& p)
{
    out << p.vertices_size;
    out << '\n';
    for (int i = 0; i < p.vertices_size; i++)
    {
        out << p.vertices[i];
        out << '\n';
    }

    return out;
}

/// @brief Аргументы программы
struct args
{
    int method_key;
    vertex* add_vertex;
    polygon* add_vertices;
    polygon* vertices;

    args() : method_key(0), add_vertex(NULL), vertices(NULL)
    {}

    ~args()
    {
        delete add_vertex;
        delete add_vertices;
        delete vertices;
    }
};


/// @brief Получает аргументы программы из файла
args* read_file(const char* filename) 
{
    ifstream in(filename, ios::binary);
    args* a = new args();

    in >> a->method_key;

    //основной вектор
    a->vertices = new polygon();
    in >> *a->vertices;
    
    //доп информация
    if (a->method_key == 2 || a->method_key == 3 || a->method_key == 4)
    {
        a->add_vertex = new vertex();
        in >> *a->add_vertex;
    }
    else if (a->method_key == 5 || a->method_key == 6 || a->method_key == 7 || a->method_key == 8)
    {
        a->add_vertices = new polygon();
        in >> *a->add_vertices;
    }

    in.close();

    return a;
}

int main()
{
    args* args = read_file(INP_FILENAME);

    ofstream out(OUTP_FILENAME);

    polygon& polyg = *args->vertices;
    switch (args->method_key)
    {
        //просто вывдоим полигон
        case 0:
            out << polyg;
            break;
        //выводим размер
        case 1:
            out << polyg.get_size();
            break;
        //добавляем вершину и выводим полигон
        case 2:
        {
            polyg += *args->add_vertex;
            out << polyg;
            break;
        }
        //удаляем вершину и выводим полигон
        case 3:
        {
            int i = polyg.get_index(*args->add_vertex);
            polyg -= i;
            out << polyg;
            break;
        }
        //проверяем содержится ли точка в полигоне
        case 4:
        {
            out << (polyg && *args->add_vertex ? "Yes" : "No");
            break;
        }
        //проверяем пересекаются ли полигоны
        case 5:
        {
            out << (polyg && *args->add_vertices ? "Yes" : "No");
            break;
        } 
        //проверяем равны ли полигоны
        case 6:
        {
            out << (polyg == *args->add_vertices ? "Yes" : "No");
            break;
        } 
        //проверяем присваивание между полигонами
        case 7:
        {
            polyg = *args->add_vertices;
            out << polyg;
            out << *args->add_vertices;
            break;
        }
        //проверяем копирование между полигонами
        case 8:
        {
            polygon poly2(polyg);

            out << polyg;
            out << poly2;
            break;
        }

        default:
            break;
    }

    out.close();

    delete args;

    return 0;
}
