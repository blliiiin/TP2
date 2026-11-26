#include "CircularList.h"
#include "Input.h"

#include <iostream>
#include <limits>
#include <stdexcept>

CircularList::CircularList()
{
    std::cout << "CircularList: конструктор без параметров.\n";
}

CircularList::CircularList(int firstValue)
{
    insert(firstValue);
    std::cout << "CircularList: конструктор с параметром.\n";
}

CircularList::CircularList(const CircularList& other)
{
    try {
        const Node* source = other.tail_ ? other.tail_->next : nullptr;
        for (int i = 0; i < other.size_; ++i) {
            insert(source->value);
            if (source == other.current_) {
                current_ = tail_;
            }
            source = source->next;
        }
    }
    catch (...) {
        clear();
        throw;
    }

    std::cout << "CircularList: конструктор копирования.\n";
}

CircularList::~CircularList()
{
    clear();
    std::cout << "CircularList: деструктор.\n";
}

CircularList& CircularList::operator=(CircularList other)
{
    Node* oldTail = tail_;
    Node* oldCurrent = current_;
    int oldSize = size_;

    tail_ = other.tail_;
    current_ = other.current_;
    size_ = other.size_;

    other.tail_ = oldTail;
    other.current_ = oldCurrent;
    other.size_ = oldSize;
    return *this;
}

int CircularList::getSize() const
{
    return size_;
}

int CircularList::getCurrentValue() const
{
    if (!current_) {
        throw std::out_of_range("Список пуст.");
    }
    return current_->value;
}

CircularList::Node* CircularList::nodeAt(int position)
{
    if (position < 1 || position > size_) {
        throw std::out_of_range("Такой позиции в списке нет.");
    }

    Node* node = tail_->next;
    for (int i = 1; i < position; ++i) {
        node = node->next;
    }
    return node;
}

void CircularList::setCurrentPosition(int position)
{
    current_ = nodeAt(position);
}

void CircularList::setValue(int position, int value)
{
    nodeAt(position)->value = value;
}

void CircularList::insert(int value, int position)
{
    if (size_ == std::numeric_limits<int>::max()) {
        throw std::length_error("Достигнут предельный размер списка.");
    }
    if (position < 0 || position > size_ + 1) {
        throw std::out_of_range("Недопустимая позиция вставки.");
    }

    if (!tail_) {
        tail_ = new Node{ value, nullptr };
        tail_->next = tail_;
        current_ = tail_;
    }
    else {
        const bool append = position == 0 || position == size_ + 1;
        Node* previous = (append || position == 1) ? tail_ : nodeAt(position - 1);

        Node* node = new Node{ value, previous->next };
        previous->next = node;
        if (append) {
            tail_ = node;
        }
    }
    ++size_;
}

void CircularList::eraseNode(Node* node)
{
    if (size_ == 1) {
        clear();
        return;
    }

    Node* previous = tail_;
    while (previous->next != node) {
        previous = previous->next;
    }

    previous->next = node->next;
    if (node == tail_) {
        tail_ = previous;
    }
    if (node == current_) {
        current_ = node->next;
    }

    delete node;
    --size_;
}

void CircularList::erase(int position)
{
    eraseNode(nodeAt(position));
}

void CircularList::clear()
{
    if (tail_) {
        Node* node = tail_->next;
        tail_->next = nullptr;

        while (node) {
            Node* next = node->next;
            delete node;
            node = next;
        }
    }

    tail_ = nullptr;
    current_ = nullptr;
    size_ = 0;
}

CircularList& CircularList::operator++()
{
    insert(readNumber<int>("Новый элемент: "));
    return *this;
}

CircularList CircularList::operator++(int)
{
    const int first = readNumber<int>("Первый новый элемент: ");
    const int second = readNumber<int>("Второй новый элемент: ");
    CircularList old(*this);

    insert(first);
    try {
        insert(second);
    }
    catch (...) {
        eraseNode(tail_);
        throw;
    }
    return old;
}

CircularList& operator--(CircularList& list)
{
    const int value = list.getCurrentValue();
    std::cout << "Текущий элемент: " << value << '\n';
    list.eraseNode(list.current_);
    return list;
}

CircularList operator--(CircularList& list, int)
{
    if (list.size_ < 2) {
        throw std::out_of_range("Для b-- нужны как минимум два элемента.");
    }

    CircularList old(list);
    std::cout << "Текущий элемент: " << list.getCurrentValue()
        << ", следующий: " << list.current_->next->value << '\n';

    list.eraseNode(list.current_);
    list.eraseNode(list.current_);
    return old;
}

std::ostream& operator<<(std::ostream& out, const CircularList& list)
{
    out << "Размер " << list.getSize() << ", список {";

    if (list.tail_) {
        const CircularList::Node* node = list.tail_->next;
        for (int i = 0; i < list.size_; ++i) {
            if (i > 0) {
                out << ", ";
            }
            out << i + 1 << ": " << node->value;
            if (node == list.current_) {
                out << " [текущий]";
            }
            node = node->next;
        }
    }

    return out << '}';
}