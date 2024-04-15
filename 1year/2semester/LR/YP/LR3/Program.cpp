#include <fstream>
#include <cctype>
#include <cstring>
#include <iostream>

using namespace std;

const char* INP_FILENAME = "input.txt";
const char* OUTP_FILENAME = "output.txt";
const char* FILE_DELIMETER = " ";


/// @brief Получает размер файла (считается на стороне жесткого диска)
/// @param filename Путь/название файла
/// @return
int get_filesize(const char* filename)
{
    ifstream is;
    is.open (filename, ios::binary );
    is.seekg (0, ios::end);
    int size = is.tellg();
    is.close();
    
    return size;
}

/// @brief Читает весь файл с данным названием filename в C-строку 
/// @param filename Путь/название файла
/// @return C-строка с содержимым файла
char* read_whole_file(const char* filename)
{
    ifstream input(filename);
    int filesize = get_filesize(filename);

    char* content = new char[filesize+1];
    for (int i = 0; i < filesize; i++)
    {
        input >> noskipws >> content[i];
    }

    input.close();

    content[filesize] = '\0';

    return content;
}


template<typename T>
class dl_node
{
    private:
        T data;
        dl_node<T>* next;
        dl_node<T>* prev;

    public:
        dl_node(dl_node* prev, dl_node* next, T data): prev(prev), next(next), data(data)
        {
        }

        void set_next(dl_node<T>* n)
        {
            next = n;
        }

        dl_node<T>* get_next()
        {
            return next;
        }

        void set_prev(dl_node<T>* p)
        {
            prev = p;
        }

        dl_node<T>* get_prev()
        {
            return prev;
        }

        T& get_data()
        {
            return data;
        }
};

template<typename T>
class dl_list
{
    private:
        dl_node<T>* head;
        dl_node<T>* tail;

        void push_back(dl_node<T>* node)
        {
            node->set_next(NULL);

            if (tail == NULL)
            {
                head = tail = node;
                return;
            }

            tail->set_next(node);
            node->set_prev(tail);

            tail = node;
        }

    public:
        class Iterator;

        dl_list(): head(NULL), tail(NULL)
        {}

        dl_list(Iterator begin, Iterator end): head(begin), tail(end)
        {}

        dl_node<T> get_head()
        {
            return head;
        }

        dl_node<T> get_tail()
        {
            return tail;
        }

        void push_back(T data)
        {
            dl_node<T>* node = new dl_node<T>(NULL, NULL, data);

            if (tail == NULL)
            {
                head = tail = node;
                return;
            }

            tail->set_next(node);
            node->set_prev(tail);
            tail = node;
        }

        /// @brief Меняет произвольные два элемента в списке местами
        /// @param first 
        /// @param second 
        void swap(Iterator first, Iterator second)
        {
            swap(first.curr_node, second.curr_node);
        }

        /// @brief Меняет произвольные два элемента в списке местами
        /// @param first 
        /// @param second 
        void swap(dl_node<T>* first_node, dl_node<T>* second_node)
        {
            dl_node<T>* first_prev = first_node->get_prev();
            dl_node<T>* first_next = first_node->get_next();

            dl_node<T>* second_prev = second_node->get_prev();
            dl_node<T>* second_next = second_node->get_next();

            if (second_next == first_node)
            {
                std::swap(first_node, second_node);

                std::swap(first_prev, second_prev);
                std::swap(first_next, second_next);
            }

            if (first_next == second_node)
            {
                //first_prev:
                if (first_prev != NULL)
                    first_prev->set_next(second_node);

                second_node->set_prev(first_prev);

                //second_next:
                if (second_next != NULL)
                    second_next->set_prev(first_node);

                first_node->set_next(second_next);
                
                second_node->set_next(first_node);
                first_node->set_prev(second_node);
            }
            else
            {
                if (first_prev != NULL)
                    first_prev->set_next(second_node);

                if (first_next != NULL)
                    first_next->set_prev(second_node);

                if (second_prev != NULL)
                    second_prev->set_next(first_node);

                if (second_next != NULL)
                    second_next->set_prev(first_node);

                first_node->set_prev(second_prev);
                first_node->set_next(second_next);

                second_node->set_prev(first_prev);
                second_node->set_next(first_next);
            }

            if (head == first_node)
                head = second_node;
            else if(head == second_node)
                head = first_node;

            if (tail == first_node)
                tail = second_node;
            else if(tail == second_node)
                tail = first_node;            
        }

        class Iterator
        {
            friend void dl_list<T>::swap(Iterator, Iterator);

            private:
                dl_node<T>* curr_node;

            public:
                Iterator(dl_node<T>* node): curr_node(node)
                {}

                Iterator& operator= (dl_node<T>* node)
                {
                    curr_node = node;
                    return *this;
                }

                /// @brief Prefix ++
                /// @return 
                Iterator& operator++ ()
                {
                    if (curr_node)
                        curr_node = curr_node->get_next();

                    return *this;
                }

                /// @brief Postfix ++
                /// @return 
                Iterator operator++ (int)
                {
                    Iterator prev_iterator = *this;
                    ++*this;
                    return prev_iterator;
                }
                
                bool operator== (const Iterator& iter)
                {
                    return curr_node == iter.curr_node;
                }

                bool operator!= (const Iterator& iter)
                {
                    return curr_node != iter.curr_node;
                }

                T& operator* ()
                {
                    return curr_node->get_data();
                }
        };

        Iterator begin()
        {
            return Iterator(head);
        }

        Iterator end()
        {
            return Iterator(NULL);
        }

        void selection_sort()
        {
            dl_node<T>* end = NULL;
            dl_node<T>* begin = head;
            
            while (begin != end)
            {
                dl_node<T>* min = begin;
                dl_node<T>* iter = begin;
                iter = iter->get_next();
                for (; iter != end; iter = iter->get_next())
                {
                    if (iter->get_data() < min->get_data())
                    {
                        min = iter;
                    }
                }

                dl_node<T>* temp_begin = begin;
                begin = begin->get_next();
                swap(temp_begin, min);
            }
        }

        dl_list<T>* merge_sort_internal(dl_node<T>* begin, dl_node<T>* end, int size)
        {
            dl_list<T>* new_container = new dl_list<T>();

            if (size == 1)
            {
                new_container->push_back(begin);
                return new_container;
            }

            int new_size = size / 2;

            // станет началом второго суб-массива
            dl_node<T>* separator = begin;
            for (int i = 0; i < new_size; i++)
            {
                separator = separator->get_next();
            }

            dl_list<T>* l_list = merge_sort_internal(begin, separator, new_size);
            dl_list<T>* l_right = merge_sort_internal(separator, end, size-new_size);

            dl_node<T>* left = l_list->head;
            dl_node<T>* right = l_right->head;

            
            while (right != NULL || left != NULL)
            {
                while (right != NULL && (left == NULL  || right->get_data() <= left->get_data()))
                {
                    dl_node<T>* temp = right->get_next();
                    new_container->push_back(right);
                    right = temp;
                }

                while (left != NULL && (right == NULL || left->get_data() <= right->get_data()))
                {
                    dl_node<T>* temp = left->get_next();
                    new_container->push_back(left);
                    left = temp;
                }
            }

            //это просто временные контейнеры для удобной передачи нодов.
            delete l_list;
            delete l_right;

            return new_container;
        }

        dl_list<T>* merge_sort()
        {
            int size = 0;
            for (typename dl_list<T>::Iterator iter = begin(); iter != end(); iter++)
            {
                size++;
            }

            dl_node<T>* local_head = head;
            dl_node<T>* local_tail = tail;

            return merge_sort_internal(local_head, local_tail, size);
        }
};

template<typename T>
struct file_content
{
    int type_of_sort;
    int size;
    dl_list<T>* list;
};

/// @brief Парсит С-строку в массив чисел типа double 
/// @param str C-строка, будет изменена и токенизирована используя strtok!
/// @return 
template<typename T>
file_content<T> parse_file_content(char* str, T (*convert)(const char*)) 
{
    file_content<T> result;
    dl_list<T>* list = new dl_list<T>();

    int i = 0;
    char* curr_token = strtok(str, " ");

    result.type_of_sort = atoi(curr_token);
    curr_token = strtok(NULL, " ");

    while (curr_token != NULL)
    {
        list->push_back(convert(curr_token));
        curr_token = strtok(NULL, " ");
        i++;
    }

    result.size = i;
    result.list = list;

    return result;
}


int main()
{
    char* content = read_whole_file(INP_FILENAME);

    file_content<double> parsed_file = parse_file_content<double>(content, &atof);
    dl_list<double>* nums = parsed_file.list;

    ofstream output(OUTP_FILENAME);

    if (parsed_file.type_of_sort)
    {
        //selection sort
        nums->selection_sort();
    }
    else
    {
        //я слишком сильно увлекся итераторами и из за этого не успел самое главное сделать :(
        nums = nums->merge_sort();
    }

    output << parsed_file.size << ' ';
    

    for (dl_list<double>::Iterator iter = nums->begin(); iter != nums->end(); iter++)
    {
        output << *iter << ' ';
    }

    output.close();

    delete nums;
    delete [] content;

    return 0;
}