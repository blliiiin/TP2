#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include <iosfwd>

class CircularList {
private:
    struct Node {
        int value;
        Node* next;
    };

    Node* tail_ = nullptr;
    Node* current_ = nullptr;
    int size_ = 0;

    Node* nodeAt(int position);
    void eraseNode(Node* node);

public:
    CircularList();
    explicit CircularList(int firstValue);
    CircularList(const CircularList& other);
    ~CircularList();

    CircularList& operator=(CircularList other);

    int getSize() const;
    int getCurrentValue() const;
    void setCurrentPosition(int position);
    void setValue(int position, int value);
    void insert(int value, int position = 0);
    void erase(int position);
    void clear();

    CircularList& operator++();
    CircularList operator++(int);

    friend CircularList& operator--(CircularList& list);
    friend CircularList operator--(CircularList& list, int);
    friend std::ostream& operator<<(std::ostream& out, const CircularList& list);
};

#endif
