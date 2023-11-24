#include <functional>
#include "Node.hpp"
template <class Value>
class List
{
private:
    Node<Value> *_top;
    Node<Value> *_last;
    size_t _size;
    void destroyRecursive(Node<Value> *node)
    {
        if (node->next != nullptr)
            destroyRecursive(node->next);
        delete node;
    }

    class BaseIterator
    {
    protected:
        Node<Value> *ptr;

    public:
        BaseIterator()
        {
            this->ptr = nullptr;
        }
        BaseIterator(Node<Value> *ptr)
        {
            this->ptr = ptr;
        }
        ~BaseIterator() {}

        const bool operator==(const BaseIterator &other) const
        {
            return this->ptr == other->ptr;
        }
        const bool operator!=(const BaseIterator &other) const
        {
            return this->ptr != other->ptr;
        }

        Value &operator*()
        {
            return this->ptr->_value;
        };
    };

public:
    List()
    {
        this->_top = nullptr;
        this->_last = nullptr;
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
        this->push(value);
    }

    ~List()
    {
        this->destroyRecursive(this->_top);
    }

    void push(const Value &value)
    {
        this->_size++;

        if (this->_top == nullptr)
        {
            this->_top = new Node(value);
            this->_last = this->_top;
            return;
        }

        this->_last->next = new Node<Value>(value);
        this->_last = this->_last->next;
    }

    template <class Comparator = std::less<Value>>
    void sort()
    {
        if (this->_size < 2)
            return;
        // bubble sort algorithm
        Comparator comparator;

        for (size_t i = 0; i < this->_size; i++)
        {
            Node<Value> *current = this->_top;
            Node<Value> *next = this->_top->next;
            for (size_t j = 0; j < this->_size; j++)
            {
                if (!comparator(current->value, next->value))
                {
                    // swap nodes
                    /**
                     * <-curr-> <-next->
                     */
                    Node<Value> *tmpCurrPrevious = current->previous;
                    Node<Value> *tmpNextNext = next->next;

                    next->previous = tmpCurrPrevious;
                    current->next = tmpNextNext;

                    next->next = current;
                    current->previous = next;

                    if (next->previous == nullptr)
                        this->_top = next;
                    if (current->next == nullptr)
                        this->_last = current;
                }
            }
        }
    }

    size_t size()
    {
        return this->_size;
    }

    class Iterator : public BaseIterator
    {
    public:
        Iterator()
        {
            this->ptr = nullptr;
        }
        Iterator(Node<Value> *ptr)
        {
            this->ptr = ptr;
        }
        ~Iterator() {}
        void operator++()
        {
            if (this->ptr)
                this->ptr = this->ptr->next;
        }

        void operator--()
        {
            if (this->ptr)
                this->ptr = this->ptr->previous;
        }
    };

    Iterator begin()
    {
        return Iterator(this->_top);
    }

    Iterator end()
    {
        return Iterator();
    }

    class ReverseIterator : public BaseIterator
    {
    public:
        ReverseIterator() { this->ptr = nullptr; }
        ReverseIterator(Node<Value> *ptr) { this->ptr = ptr; }
        ~ReverseIterator() {}
        void operator--()
        {
            if (this->ptr)
                this->ptr = this->ptr->next;
        }

        void operator++()
        {
            if (this->ptr)
                this->ptr = this->ptr->previous;
        }
    };

    ReverseIterator rbegin()
    {
        return ReverseIterator(this->_last);
    }
    ReverseIterator rend()
    {
        return ReverseIterator();
    }
};
