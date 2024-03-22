// List.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "IndexedList.h"
#include <vector>
#include <list>
#include "Menu.h"
#include <conio.h>
int main()
{
	
	system("chcp 1251");
	using type = int;
	type inputBuffer;
	List<int> list;
	//list.push_back(2);
	//list.push_back(4);
	auto iterator = list.begin();
	enum OPERATION_TYPE {
		Front,
		Back
	};
	OPERATION_TYPE operationType;
	Menu navigationMenu([&]() {
		//std::cout << "Menu";
		std::cout << "List: ";
		for (auto it = list.begin(); it != list.end(); it++) {
			if (it == iterator) std::cout << "[" << *it << "]" << " ";
			else
			std::cout << * it << " ";
		}
	});
	Menu inputMenu([&] {
		std::cout << "Введите значение элемента: ";
	std::cin >> inputBuffer;;
	if(operationType == OPERATION_TYPE::Front)
		list.push_front(inputBuffer);
	if (operationType == OPERATION_TYPE::Back)
		list.push_back(inputBuffer);
	if (list.size() == 1) iterator = list.begin();
	Menu::console.setMenu(&navigationMenu);
	}, true);
	MenuItem iterplus("iter++", [&] {
		try {
			iterator++;
		}
		catch(std::exception e){
			std::cout << "\n" << e.what();
			_getch();
		}
	});
	MenuItem iterminus("iter--", [&] {
		try {
		iterator--;
	}
	catch (std::exception e) {
		std::cout << "\n" << e.what();
		_getch();
	}
		});
	MenuItem push_back("push_back", [&]() {
		operationType = OPERATION_TYPE::Back;
		Menu::console.setMenu(&inputMenu);
	});
	MenuItem push_front("push_front", [&]() {
		operationType = OPERATION_TYPE::Front;
		Menu::console.setMenu(&inputMenu);
	});
	MenuItem back("back", [&]() {
		try {
		std::cout<<"\n"<<list.back();
	}
	catch (std::exception e) {
		std::cout << " [!] Exception: " << e.what();
	}
	_getch();
	Menu::console.setMenu(&navigationMenu);
		});
	MenuItem front("front", [&]() {
			try {
			std::cout<<"\n"<<list.front();
		}
		catch (std::exception e) {
			std::cout << " [!] Exception: " << e.what();
		}
	_getch();
		Menu::console.setMenu(&navigationMenu);
	});
	MenuItem clear("clear", [&]() {
		list.clear();
		iterator = list.begin();
		Menu::console.setMenu(&navigationMenu);
	});
	MenuItem pop_front("pop_front", [&]() {
		try {
		list.pop_front();
		}
		catch (std::exception e) {
		std::cout << " [!] Exception: " << e.what();
		_getch();
		}
	});
	MenuItem pop_back("pop_back", [&]() {
		try {
		list.pop_back();
	}
	catch (std::exception e) {
		std::cout << " [!] Exception: " << e.what();
		_getch();
	}
		});
	MenuItem contains("contains", [&]() {
		type a;
		std::cout << "Введите элемент: ";
		std::cin >> a;
		std::cout << (list.contains(a) ? "Contains" : "Doesn't contain");
		_getch();
	});
	MenuItem getIndexOf("getIndexOf", [&]() {
		type a;
	std::cout << "Введите элемент: ";
	std::cin >> a;
	std::cout <<"\n Индекс: " << list.getIndexOf(a);
	_getch();
	});
	MenuItem insert("insert", [&]() {
		type a;
		std::cout << "Введите элемент: ";
		std::cin >> a;
		list.insert(iterator, a);
		if (list.size() == 1) iterator = list.begin();
	});
	MenuItem insertAt("insertAt", [&]() {
		type a;
		type index;
		std::cout << "Введите элемент: ";
		std::cin >> a;
		std::cout << "\nВведите индекс: ";
		std::cin >> index;
		try {
			list.insertAt(index, a);
			if (list.size() == 1) iterator = list.begin();
		}
		catch (std::exception e) {
			std::cout << " [!] Exception: " << e.what();
			_getch();
		}
	});
	MenuItem erase("erase", [&]() {
		try {
			list.erase(iterator);
		}
		catch (std::exception e) {
			std::cout << " [!] Exception: " << e.what();
			_getch();
		}
	});
	MenuItem removeValue("removeValue", [&]() {
		type a;
		std::cout << "Введите элемент: ";
		std::cin >> a;
		list.removeValue(a);
	});
	MenuItem removeAt("removeAt", [&]() {
	type index;
	std::cout << "Введите индекс: ";
	std::cin >> index;
	try {
		list.removeAt(index);
	}
	catch (std::exception e) {
		std::cout << " [!] Exception: " << e.what();
		_getch();
	}
	});
	MenuItem edit("edit", [&]() {
	try {
		type* a = &(*iterator);
		type val;
		std::cout << "Введите новое значение: ";
		std::cin >> val;
		*a = val;
	}
	catch (std::exception e) {
		std::cout << " [!] Exception: " << e.what();
		_getch();
	}
	});
	MenuItem editAt("editAt", [&]() {
		try {
		type index;
		std::cout << "Введите индекс: ";
		std::cin >> index;
		type* a = &(list.at(index));
		type val;
		std::cout << "Введите новое значение: ";
		std::cin >> val;
		*a = val;
	}
	catch (std::exception e) {
		std::cout << " [!] Exception: " << e.what();
		_getch();
	}
		});
	MenuItem begin("begin", [&]() {
		iterator = list.begin();
		});
	MenuItem end("end", [&]() {
		iterator = list.end();
		});
	MenuItem star(" * ", [&](){
		try {
			type a = *iterator;
			std::cout<<"Element iterator's pointing at:"<<a;
			_getch();
		}
		catch (std::exception e) {
			std::cout << " [!] Exception: " << e.what();
			_getch();
		}
	});
	
	navigationMenu.addItem(iterplus);
	navigationMenu.addItem(iterminus);
	navigationMenu.addItem(push_back);
	navigationMenu.addItem(push_front);
	navigationMenu.addItem(front);
	navigationMenu.addItem(back);
	navigationMenu.addItem(clear);
	navigationMenu.addItem(pop_front);
	navigationMenu.addItem(pop_back);
	navigationMenu.addItem(contains);
	navigationMenu.addItem(getIndexOf);
	navigationMenu.addItem(insert);
	navigationMenu.addItem(insertAt);
	navigationMenu.addItem(removeValue);
	navigationMenu.addItem(removeAt);
	navigationMenu.addItem(edit);
	navigationMenu.addItem(editAt);
	navigationMenu.addItem(begin);
	navigationMenu.addItem(end);
	navigationMenu.addItem(star);
	Menu::console.setMenu(&navigationMenu);
	Menu::console.show();
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
