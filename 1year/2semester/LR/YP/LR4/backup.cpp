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

/// @brief Узел дерева
/// @tparam T 
template<typename T>
class tree_node
{
    private:
        T data;
        tree_node<T>* left;
        tree_node<T>* right;

    public:
        tree_node(tree_node* left, tree_node* right, T data):  data(data), left(left), right(right)
        {
        }

        void set_left(tree_node<T>* n)
        {
            left = n;
        }

        tree_node<T>* get_left()
        {
            return left;
        }

        void set_right(tree_node<T>* n)
        {
            right = n;
        }

        tree_node<T>* get_right()
        {
            return right;
        }

        T& get_data()
        {
            return data;
        }

        void set_data(T& data)
        {
            data = data;
        }
};

/// @brief Дерево поиска
/// @tparam T Тип значений в дереве
template<typename T>
class search_tree {
    private:
        tree_node<T>* root;

        /// @brief Итерируется через узлы в in-order порядке
        /// @tparam F 
        /// @param node 
        /// @param func 
        /// @param parent 
        template<typename F>
        void foreach_inorder_node(tree_node<T>* node, F && func, tree_node<T>* parent = NULL)
        {
            if (!node) return;

            if (node->get_left())
            {
                foreach_inorder_node(node->get_left(), func, node);
            }

            tree_node<T>* right = node->get_right();
            func(node, parent);

            if (right)
            {
                foreach_inorder_node(right, func, node);
            }
        }

        /// @brief Ставит на место child узел new_child
        /// @param parent Узел содержащий в left/right узел child
        /// @param child Наследник parent
        /// @param new_child Узел который нужно поставить на место child
        void replace_child(tree_node<T>* parent, tree_node<T>* child, tree_node<T>* new_child)
        {
            if (!parent) return;

            if (parent->get_left() == child)
                parent->set_left(new_child);
            else
                parent->set_right(new_child);
        }

        /// @brief Удаляет узел n
        /// @param n Узел на удаление
        /// @param parent Узел, наследником которого является n
        void remove(tree_node<T>* n, tree_node<T>* parent)
        {
            tree_node<T>* replacement;
            if (!n->get_left() && !n->get_right()) //both null
            {
                replacement = NULL;
                replace_child(parent, n, replacement);
            }
            else if(!n->get_right()) //right is null
            {
                replacement = n->get_left();
                replace_child(parent, n, replacement);
            }
            else if(!n->get_left()) //left is null
            {
                replacement = n->get_right();
                replace_child(parent, n, replacement);
            }
            else //both non-null
            {
                tree_node<T>* successor_parent = NULL;
                tree_node<T>* successor = NULL;
                foreach_inorder_node(n->get_right(), [&successor_parent, &successor](tree_node<T>* curr, tree_node<T>* s_parent)
                {
                    if (!successor)
                    {
                        successor_parent = s_parent;
                        successor = curr;
                    }
                }, n);

                //удаляем  in-order наследника (у него одно значимое свойство - left всегда равен null)
                replace_child(successor_parent, successor, successor->get_right());

                //заменяем удаляемый элемент на in-order наследника
                replacement = new tree_node<T>(n->get_left(), n->get_right(), successor->get_data());
                replace_child(parent, n, replacement);

                delete successor;
            }

            if (n == root)
            {
                root = replacement;
            }

            delete n;
        }

    public:
        search_tree(): root(NULL)
        {}

        /// @brief Добавление значения в дерево
        /// @param data 
        void add(T data)
        {
            tree_node<T>* node = new tree_node<T>(NULL, NULL, data);

            if (!root)
            {
                root = node;
                return;
            }

            tree_node<T>* curr = root;
            while (curr)
            {
                //then left
                if (node->get_data() <= curr->get_data())
                {
                    //then insert
                    if (!curr->get_left())
                    {
                        curr->set_left(node);
                        break;
                    }
                    //then continue
                    else
                    {
                        curr = curr->get_left();
                    }
                }
                //then right
                else
                {
                    //then insert
                    if (!curr->get_right())
                    {
                        curr->set_right(node);
                        break;
                    }
                    //then continue
                    else
                    {
                        curr = curr->get_right();
                    }
                }
            }
        }

        /// @brief Добавление значения в дерево
        /// @return true если значение присутсововало в дерево, false иначе
        bool remove(T data)
        {
            tree_node<T>* parent = NULL;
            tree_node<T>* n = NULL;
            foreach_inorder_node(root, [&n, &data, &parent](tree_node<T>* c, tree_node<T>* p)
            {
                if (c->get_data() == data)
                {
                    n = c;
                    parent = p;
                } 
            });

            if (!n)
                return false;

            remove(n, parent);

            return true;
        }
        
        template<typename F>
        void foreach_inorder(F && func)
        {
            foreach_inorder_node(root, [&func](tree_node<T>* n, tree_node<T>* p) { func(n->get_data()); } );
        }

        ~ search_tree()
        {
            //удаляем все узлы
            foreach_inorder_node(root, [](tree_node<T>* curr, tree_node<T>* p) { delete curr; });
        }
};


/// @brief Парсит С-строку в массив чисел типа double 
/// @param str C-строка, будет изменена и токенизирована используя strtok!
/// @return 
template<typename T>
search_tree<T>* parse_file_content(char* str, T (*convert)(const char*)) 
{
    search_tree<T>* tree = new search_tree<T>();

    int i = 0;
    char* curr_token = strtok(str, " ");

    while (curr_token)
    {
        tree->add(convert(curr_token));
        curr_token = strtok(NULL, " ");
        i++;
    }

    return tree;
}

/// @brief Удаляет из tree все четные значения
/// @param tree 
void remove_even(search_tree<int>* tree)
{
    int even_count = 0;
    tree->foreach_inorder([&even_count](int& d)
    {
        if (d % 2 == 0)
            even_count++;
    });

    int* even_numbers = new int[even_count]; 
    int i = 0;
    tree->foreach_inorder([&even_numbers, &i](int& d)
    {
        if (d % 2 == 0)
            even_numbers[i++] = d;
    });

    for (i = 0; i < even_count; i++)
    {
        tree->remove(even_numbers[i]);
    }

    delete [] even_numbers;
}

/// @brief Выводит tree в файл в in-order порядке
/// @param tree 
void output_tree(search_tree<int>* tree)
{
    ofstream output(OUTP_FILENAME);

    tree->foreach_inorder([&output](int& d)
    {
        output << d << ' ';
    });

    output.close();
}

int main()
{
    char* content = read_whole_file(INP_FILENAME);

    search_tree<int>* parsed_tree = parse_file_content<int>(content, &atoi);

    remove_even(parsed_tree);
    output_tree(parsed_tree);

    delete parsed_tree;
    delete [] content;

    return 0;
}
