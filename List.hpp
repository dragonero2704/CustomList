#include <functional>
#include "Node.hpp"
template <class Value>
class List
{
private:
    Node<Value> *start;
    Node<Value> *end;
    size_t _size;
    void destroyRecursive(Node<Value> *node)
    {
        if (node->next != nullptr)
            destroyRecursive(node->next);
        delete node;
    }

public:
    List()
    {
        this->start = nullptr;
        this->_size = 0;
    }

    List(Value *start, Value *end)
    {
        while (start != end)
        {
            this->push(*start);
            start++;
        }
    }

    List(const Value &value)
    {
        if (this->start != nullptr)
            this->push(value);
        else
        {
            this->start = new Node<Value>(value);
            this->end = start;
        }
    }

    ~List()
    {
        this->destroyRecursive(this->start);
    }

    void push(const Value &value)
    {
        this->_size++;

        if (this->start == nullptr)
        {
            this->start = new Node(value);
            return;
        }
        Node<Value> *tmp = this->start;
        while (tmp->next != nullptr)
            tmp = tmp->next;
        tmp->next = new Node(value);
        tmp->next->previous = tmp;

        this->end = tmp->next;
    }

    void sort(class Comparator = std::less<Value>)
    {
        if (this->_size < 2)
            return;
        // bubble sort algorithm
        Comparator comparator;

        for (size_t i = 0; i < this->_size; i++)
        {
            Node<Value> *current = this->start;
            Node<Value> *next = this->start->next;
            for (size_t j = 0; j < this->_size; j++)
            {
                if (!comparator(current->value, next->value))
                {
                    // swap nodes
                    /**
                     * <-curr-> <-next->
                     *
                     *
                     */
                    Node<Value> *tmpCurrPrevious = current->previous;
                    Node<Value> *tmpNextNext = next->next;

                    next->previous = tmpCurrPrevious;
                    current->next = tmpNextNext;

                    next->next = current;
                    current->previous = next;

                    if (next->previous == nullptr)
                        this->start = next;
                    if (current->next == nullptr)
                        this->end = current
                }
            }
        }
    }

    size_t size()
    {
        return this->_size;
    }

    class Iterator
    {
    private:
        Node<Value> *ptr;

    public:
        Iterator()
        {
            this->ptr = nullptr;
        }
    };

    Iterator begin()
    {
    }

    class ReverseIterator
    {
    private:
        Node<Value> *ptr;
        ReverseIterator()
        {
            this->ptr = nullptr;
        }
    };
};