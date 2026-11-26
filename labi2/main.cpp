#include "CircularList.h"
#include "Dimensions.h"
#include "Input.h"

#include <exception>
#include <iostream>
#include <stdexcept>

CircularList readList()
{
    const int size = readNumber<int>("Количество элементов: ");

    if (size < 0) {
        throw std::invalid_argument("Размер списка должен быть неотрицательным.");
    }
    if (size == 0) {
        return CircularList();
    }

    CircularList list(readNumber<int>("Элемент 1: "));
    for (int i = 1; i < size; ++i) {
        std::cout << "Элемент " << i + 1;
        list.insert(readNumber<int>(": "));
    }
    return list;
}

Dimensions* readDimensions(Dimensions* target)
{
    const double height = readNumber<double>("Высота: ");
    const double width = readNumber<double>("Ширина: ");
    const double depth = readNumber<double>("Глубина: ");

    *target = Dimensions(height, width, depth);
    return target;
}

int main()
{
    CircularList listA;
    CircularList listB;
    Dimensions dimensionsA;
    Dimensions dimensionsB;

    int section = 0;
    while (true) {
        try {
            if (section == 0) {
                const int choice = readNumber<int>(
                    "\n1. Список   2. Габариты   0. Выход\nРаздел: ");

                if (choice == 0) {
                    return 0;
                }
                if (choice != 1 && choice != 2) {
                    throw std::invalid_argument("Такого раздела нет.");
                }
                section = choice;
            }

            if (section == 1) {
                CircularList& a = listA;
                CircularList& b = listB;

                std::cout << "\n1. Ввести список   2. Показать список\n"
                    << "3. Выбрать текущую позицию   4. Изменить значение\n"
                    << "5. Вставить по позиции   6. Удалить по позиции\n"
                    << "7. Очистить   8. ++b   9. b++   10. --b   11. b--\n"
                    << "0. Назад\n";

                switch (readNumber<int>("Действие: ")) {
                case 0:
                    section = 0;
                    break;
                case 1:
                    b = readList();
                    break;
                case 2:
                    std::cout << "b = " << b << '\n';
                    break;
                case 3:
                    b.setCurrentPosition(readNumber<int>("Текущая позиция: "));
                    std::cout << "Текущее значение: " << b.getCurrentValue() << '\n';
                    break;
                case 4: {
                    const int position = readNumber<int>("Позиция: ");
                    const int value = readNumber<int>("Новое значение: ");
                    b.setValue(position, value);
                    break;
                }
                case 5: {
                    const int position = readNumber<int>("Позиция (0 — в конец): ");
                    const int value = readNumber<int>("Значение: ");
                    b.insert(value, position);
                    break;
                }
                case 6:
                    b.erase(readNumber<int>("Позиция: "));
                    break;
                case 7:
                    b.clear();
                    break;
                case 8:
                    a = ++b;
                    std::cout << "a = " << a << "\nb = " << b << '\n';
                    break;
                case 9:
                    a = b++;
                    std::cout << "a = " << a << "\nb = " << b << '\n';
                    break;
                case 10:
                    a = --b;
                    std::cout << "a = " << a << "\nb = " << b << '\n';
                    break;
                case 11:
                    a = b--;
                    std::cout << "a = " << a << "\nb = " << b << '\n';
                    break;
                default:
                    throw std::invalid_argument("Такого действия нет.");
                }
            }
            else {
                Dimensions& a = dimensionsA;
                Dimensions& b = dimensionsB;

                std::cout << "\n1. Ввести габариты   2. Показать габариты   3. Обнулить\n"
                    << "4. Изменить компонент\n"
                    << "5. b + c   6. b - c   7. b * c   8. b / c\n"
                    << "9. c + b  10. c - b  11. c * b  12. c / b\n"
                    << "13. b += c   14. b -= c   15. b *= c   16. b /= c\n"
                    << "0. Назад\n";

                const int action = readNumber<int>("Действие: ");
                switch (action) {
                case 0:
                    section = 0;
                    continue;
                case 1:
                    std::cout << "b = " << *readDimensions(&b) << '\n';
                    continue;
                case 2:
                    std::cout << "b = " << b << '\n';
                    continue;
                case 3:
                    b = Dimensions();
                    continue;
                case 4: {
                    const int component =
                        readNumber<int>("1 — высота, 2 — ширина, 3 — глубина: ");

                    switch (component) {
                    case 1: b.setHeight(readNumber<double>("Высота: ")); break;
                    case 2: b.setWidth(readNumber<double>("Ширина: ")); break;
                    case 3: b.setDepth(readNumber<double>("Глубина: ")); break;
                    default: throw std::invalid_argument("Такого компонента нет.");
                    }
                    continue;
                }
                }

                if (action < 5 || action > 16) {
                    throw std::invalid_argument("Такого действия нет.");
                }

                const double c = readNumber<double>("Число c: ");
                switch (action) {
                case 5: a = b + c; break;
                case 6: a = b - c; break;
                case 7: a = b * c; break;
                case 8: a = b / c; break;
                case 9: a = c + b; break;
                case 10: a = c - b; break;
                case 11: a = c * b; break;
                case 12: a = c / b; break;
                case 13: a = (b += c); break;
                case 14: a = (b -= c); break;
                case 15: a = (b *= c); break;
                case 16: a = (b /= c); break;
                }

                std::cout << "a = " << a << "\nb = " << b << "\nc = " << c << '\n';
            }
        }
        catch (const std::exception& error) {
            std::cout << "\nОшибка: " << error.what() << '\n';
            if (std::cin.eof()) {
                return 0;
            }
        }
    }
}