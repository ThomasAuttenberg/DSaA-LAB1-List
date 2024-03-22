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
	auto iter = list.begin();
	//list.push_back(1);
	//auto iter2 = list.begin();
	//list.push_back(2);
	//list.push_back(3);
	//iter2++;
	//list.erase(iter2);
	//list.push_back(4);
	List<type>::iterator iter_fixed;
	bool fixedIterActive = false;
	enum OPERATION_TYPE {
		Front,
		Back
	};
	//list.push_back(3);
	OPERATION_TYPE operationType;
	Menu navigationMenu([&]() {

			std::cout <<
				" ==================================================================\n\n"
				<< " Используйте стрелки, чтобы переключаться между пунктами меню\n"
				<< " Используйте TAB чтобы зафиксировать итератор и создать новый\n"
				<< "\n ==================================================================\n\n"
				<< (fixedIterActive ? "\033[1;32m Итератор зафиксирован как \033[4mитератор начала\033[0m\033[1;32m. Перемещайте новый итератор \033[0m\n\n" : "")
				<< " Текущее содержимое списка: ";

			for (auto it = list.begin(); it != list.end(); it++) {
				if (fixedIterActive && &(*iter_fixed) == &(*it)) std::cout << "\033[1;37;46m";
				if (iter != list.end() && &(*iter) == &(*it)) std::cout << "\033[1;37;42m";
				//std::cout << "[this:]" << it.targetIndex << "[prev:]" << list.getNode(it).previousNodeIndex << "[next:]" << list.getNode(it).nextNodeIndex << " value: ";
				std::cout << *it << "\033[0m ";
			}
			if (iter == list.end()) std::cout << "\033[1;37;42m[end]\033[0m";

	});

	navigationMenu.addKeyListener(75, [&iter]() {
		try {
			iter--;
		}
		catch (std::exception ex) {
			std::cout << "\n\n Поймано исключение: " << ex.what();
			_getch();
		}
	}, true);

	navigationMenu.addKeyListener(77, [&iter]() {
		try {
			iter++;
		}
		catch (std::exception ex) {
			std::cout << "\n\n Поймано исключение: " << ex.what();
			_getch();
		}
	}, true);

	navigationMenu.addKeyListener(9, [&]() {
		if (fixedIterActive) fixedIterActive = false;
		else try {
			*iter;
			iter_fixed = iter;
			fixedIterActive = true;
		}
		catch (std::exception ex) {
			std::cout << "\n\n Первого итератора не существует! Заполните список";
			_getch();
		}
	}, false);

	Menu inputMenu([&] {
		std::cout << "Введите значение элемента: ";
	std::cin >> inputBuffer;;
	if(operationType == OPERATION_TYPE::Front)
		list.push_front(inputBuffer);
	if (operationType == OPERATION_TYPE::Back)
		list.push_back(inputBuffer);
	if (list.size() == 1) iter = list.begin();
	Menu::console.setMenu(&navigationMenu);
	}, true);
	MenuItem iterplus("iter++", [&] {
		try {
			iter++;
		}
		catch(std::exception e){
			std::cout << "\n" << e.what();
			_getch();
		}
	});
	MenuItem iterminus("iter--", [&] {
		try {
		iter--;
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
		iter = list.begin();
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
		list.insert(iter, a);
		if (list.size() == 1) iter = list.begin();
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
			if (list.size() == 1) iter = list.begin();
		}
		catch (std::exception e) {
			std::cout << " [!] Exception: " << e.what();
			_getch();
		}
	});
	MenuItem erase("erase", [&]() {
		try {
			if (!fixedIterActive) {
				list.erase(iter);
				iter = list.begin();
			}
			else {
				list.erase(iter_fixed, iter);
				iter = list.begin();
				fixedIterActive = false;
			}
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
		if (*iter == a) iter = list.begin();
		list.removeValue(a);
		
	});
	MenuItem removeAt("removeAt", [&]() {
	type index;
	std::cout << "Введите индекс: ";
	std::cin >> index;

	try {
		list.removeAt(index);
		iter = list.begin();
	}
	catch (std::exception e) {
		std::cout << " [!] Exception: " << e.what();
		_getch();
	}
	});
	MenuItem edit("edit", [&]() {
	try {
		type* a = &(*iter);
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
		iter = list.begin();
		});
	MenuItem end("end", [&]() {
		iter = list.end();
		});
	MenuItem star(" * ", [&](){
		try {
			type a = *iter;
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
	navigationMenu.addItem(erase);
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
