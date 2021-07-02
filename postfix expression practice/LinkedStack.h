#include <iostream>

using namespace std;

template <class T>

class  Node {

public:

    T data;

    Node<T>* next;

    Node(const T& d = T(), Node* n = nullptr) {

        data = d;

        next = n;

    }

};

template <class T>

class  LinkedStack {

private:

    Node<T>* topPtr;

public:

    LinkedStack() {

        topPtr = nullptr;

    }

    LinkedStack(const LinkedStack& other) {

        if (other.isEmpty())

            topPtr = nullptr;

        else {

            topPtr = new Node<T>(other.topPtr->data);

            Node<T>* otherCurrent = other.topPtr->next, pre=topPtr;

            while (otherCurrent != nullptr) {

                pre->next = new Node<T>(otherCurrent->data);

                pre = pre->next;

                otherCurrent = otherCurrent->next;

            }

        }

    }

    ~LinkedStack() {

        clear();

    }

    bool isEmpty() const {

        return  nullptr == topPtr;

    }

    bool isFull() const {

        return false;

    }

    T top() const {

        if (isEmpty())

            throw logic_error("Can't get top of an empty stack.");

        return topPtr->data;

    }

    void push(const T& d) {

        if (!isFull())

            topPtr = new Node<T>(d, topPtr);

    }

    void pop() {

        if (!isEmpty()) {

            Node<T>* temp = topPtr;

            topPtr = topPtr->next;

            delete temp;

        }

    }

    void clear() {

        while (!isEmpty())

            pop();
    }

};


