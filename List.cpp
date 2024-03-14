// List.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "IndexedList.h"
#include <vector>
#include <list>
int main()
{
    List<int> a;
    a.push_back(0);
    a.size();
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_front(4);
    
    List<int>::iterator b = a.begin();
    b++;
    List<int>::iterator c = b;
    c++;
    c++;
    a.clear();
    //std::cout << *b << std::endl;
    //a.erase(a.begin(), a.end());
    try {
        a.push_back(0);
        a.push_front(1);
        a.push_back(2);
        a.push_back(3);
        a.push_back(4);
        a.push_back(4);
        a.push_back(4);
        auto it = a.begin();
        it++;
        it++;
        it++;
        it++;
        it++;
        a.insert(it, 15);
        a.insertAt(3, 25);
        a.front() = -1;
        a.removeValue(4);
        //a.pop_front();
        std::cout << "index of 25:" << a.getIndexOf(25)<<"\n";
        std::cout << a.at(3) <<" " << a.size() << "\n";
    }
    catch (std::logic_error e) {
        std::cout << e.what() << "\n";
    }
    //std::list<int> s;
   // s.push_back(0);
   // s.push_back(1);
   // s.push_back(2);
    //s.push_back(3);
   // s.push_front(4);
   //std::list<int>::iterator iter = s.begin();
    //iter++;
    //std::list<int>::iterator iter_ = iter;
    //++iter_;
    //s.erase(iter, ++++iter);
    //for (std::list<int>::iterator i = s.begin(); i != s.end(); i++) {
   //     std::cout << *i << "\n";
    //}

    try {
        
        for (List<int>::iterator it = a.begin(); it != a.end(); it++) {
            std::cout << " " << *it;
        }
    }
    catch (std::logic_error e) {
        std::cout << e.what();
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
