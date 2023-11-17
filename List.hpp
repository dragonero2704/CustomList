#include <functional>
#include "Node.hpp"
template <class Value, class Comparator = std::greater<Value>>
class List
{
private:
    Node<Value> *root;
    void destroyRecursive(Node<Value> *node)
    {
        if (node->next != nullptr)
            destroyRecursive(node->next);
        delete node;
    }

public:
    List()
    {
        this->root = nullptr;
    }

    List(Value *start, Value *end)
    {
    }

    List(Value value)
    {
        if (this->root != nullptr)
            this->push(value);
        else
            this->root = new Node<Value>(value);
    }

    ~List()
    {
        this->destroyRecursive(this->root);
    }

    void push(const Value &value)
    {
        if (this->root == nullptr)
        {
            this->root = new Node(value);
            return;
        }
        Node<Value> *tmp = this->root;
        while (tmp->next != nullptr)
            tmp = tmp->next;
        tmp->next = new Node(value);
        tmp->next->previous = tmp;
    }
};