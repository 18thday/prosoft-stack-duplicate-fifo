#pragma once

#include <deque>
#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>

template <typename T>
class StackDuplicateFifo
{
public:
    StackDuplicateFifo() = default;

    StackDuplicateFifo(const StackDuplicateFifo& other) : m_stack(other.m_stack)
    {
        for (auto it = m_stack.begin(), it_end = m_stack.end(); it != it_end; ++it)
        {
            m_valueToDuplicateIter[*it].push(it);
        }
    }

    StackDuplicateFifo& operator=(const StackDuplicateFifo& other)
    {
        if (this == &other)
        {
            return *this;
        }
        StackDuplicateFifo tmp(other);
        this->Swap(tmp);
        return *this;
    }

    StackDuplicateFifo(StackDuplicateFifo&& other) :
        m_stack(std::move(other.m_stack)),
        m_valueToDuplicateIter(std::move(other.m_valueToDuplicateIter))
    {
        other.Clear();
    }

    StackDuplicateFifo& operator=(StackDuplicateFifo&& other)
    {
        if (this == &other)
        {
            return *this;
        }
        m_stack = std::move(other.m_stack);
        m_valueToDuplicateIter = std::move(other.m_valueToDuplicateIter);
        other.Clear();
        return *this;
    }

    ~StackDuplicateFifo() = default;

    T& Top()
    {
        return m_stack.back();
    }
    const T& Top() const
    {
        return m_stack.back();
    }

    bool Empty() const noexcept
    {
        return m_stack.empty();
    }
    size_t Size() const noexcept
    {
        return m_stack.size();
    }

    void Push(const T& value)
    {
        m_stack.push_back(value);
        m_valueToDuplicateIter[m_stack.back()].push(--m_stack.end());
    }
    void Push(T&& value)
    {
        m_stack.push_back(std::move(value));
        m_valueToDuplicateIter[m_stack.back()].push(--m_stack.end());
    }

    void Pop()
    {
        if (m_stack.size() == 0)
        {
            return;
        }
        auto it = m_valueToDuplicateIter.find(m_stack.back());
        m_stack.erase(it->second.front());
        it->second.pop();
        if (it->second.empty())
        {
            m_valueToDuplicateIter.erase(it);
        }
    }
private:
    std::list<T> m_stack;
    std::unordered_map<T, std::queue<typename std::list<T>::iterator> > m_valueToDuplicateIter;

    void Swap(StackDuplicateFifo& other)
    {
        std::swap(m_stack, other.m_stack);
        std::swap(m_valueToDuplicateIter, other.m_valueToDuplicateIter);
    }

    void Clear()
    {
        m_stack.clear();
        m_valueToDuplicateIter.clear();
    }
};