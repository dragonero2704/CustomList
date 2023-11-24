#include <functional>
template <class Value>
class Node
{
    template<class _Value>
    friend class List;

private:
    Value _value;
    Node<Value> *next;
    Node<Value> *previous;

public:
    Node()
    {
        this->_value = Value();
        this->next = nullptr;
        this->previous = nullptr;
    }

    Node(const Value &value)
    {
        this->_value = value;
        this->next = nullptr;
        this->previous = nullptr;
    }
};