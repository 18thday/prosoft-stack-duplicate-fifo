#pragma once

#include <deque>
#include <iostream>
#include <queue>
#include <unordered_map>


template <typename T>
class StackDuplicateFifo
{
public:
    StackDuplicateFifo() = default;
    StackDuplicateFifo(const StackDuplicateFifo&) = default;
    StackDuplicateFifo& operator=(const StackDuplicateFifo&) = default;

    StackDuplicateFifo(StackDuplicateFifo&& other) :
        m_stack(std::move(other.m_stack)),
        m_valueToCount(std::move(other.m_valueToCount)),
        m_size(other.m_size)
    {
        other.Clear();
    }

    StackDuplicateFifo& operator=(StackDuplicateFifo&& other)
    {
        if (this == &other) {
            return *this;
        }
        m_stack = std::move(other.m_stack);
        m_valueToCount = std::move(other.m_valueToCount);
        m_size = other.m_size;
        other.Clear();
        return *this;
    }

    T& Top()
    {
        RemoveInvalid();
        return m_stack.back();
    }
    const T& Top() const
    {
        RemoveInvalid();
        return m_stack.back();
    }

    bool Empty() const noexcept
    {
        return m_size == 0;
    }
    size_t Size() const noexcept
    {
        return m_size;
    }

    void Push(const T& value)
    {
        m_stack.push_back(value);
        ++m_valueToCount[m_stack.back()];
        ++m_size;
    }
    void Push(T&& value)
    {
        m_stack.push_back(std::move(value));
        ++m_valueToCount[m_stack.back()];
        ++m_size;
    }

    void Pop()
    {
        if (m_size == 0)
        {
            return;
        }
        auto it = m_valueToCount.find(m_stack.back());
        while (it == m_valueToCount.end())
        {
            m_stack.pop_back();
            it = m_valueToCount.find(m_stack.back());
        }
        if (--(it->second) == 0)
        {
            m_valueToCount.erase(it);
            m_stack.pop_back();
        }
        if (--m_size == 0 && !m_stack.empty())
        {
            m_stack.clear();
        }
    }

private:
    std::deque<T> m_stack;
    std::unordered_map<T, size_t> m_valueToCount;
    size_t m_size = 0;

    void RemoveInvalid()
    {
        while (!m_stack.empty() && !m_valueToCount.count(m_stack.back()))
        {
            m_stack.pop_back();
        }
    }

    void Clear()
    {
        m_size = 0;
        m_stack.clear();
        m_valueToCount.clear();
    }
};