#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <list>
#include <random>
#include <stack>
#include <vector>

#include "stack_duplicate_fifo.h"


TEST(BasicTest, DefaultCtor)
{
    StackDuplicateFifo<int> stack;
    EXPECT_EQ(stack.Size(), 0);
    EXPECT_EQ(stack.Empty(), true);
}

TEST(BasicTest, EmptyPop)
{
    StackDuplicateFifo<int> stack;
    stack.Pop();
    stack.Pop();
}

TEST(BasicTest, PushPop)
{
    StackDuplicateFifo<int> stack;
    stack.Push(5);
    EXPECT_EQ(stack.Top(), 5);
    EXPECT_EQ(stack.Size(), 1);
    EXPECT_EQ(stack.Empty(), false);
    stack.Pop();
    EXPECT_EQ(stack.Size(), 0);
    EXPECT_EQ(stack.Empty(), true);
}

TEST(BasicTest, CopyCtor)
{
    StackDuplicateFifo<int> stack;
    for (int i = 0; i < 5; ++i)
    {
        stack.Push(i);
    }
    StackDuplicateFifo<int> copy_stack = stack;
    EXPECT_EQ(stack.Size(), 5);
    EXPECT_EQ(stack.Empty(), false);
    EXPECT_EQ(copy_stack.Size(), 5);
    EXPECT_EQ(copy_stack.Empty(), false);

    while (!stack.Empty())
    {
        EXPECT_EQ(stack.Size(), copy_stack.Size());
        EXPECT_EQ(stack.Top(), copy_stack.Top());
        stack.Pop();
        copy_stack.Pop();
    }
}

TEST(BasicTest, CopyAssignment)
{
    {
        StackDuplicateFifo<int> a;
        for (int i = 0; i < 5; ++i)
        {
            a.Push(i);
        }
        StackDuplicateFifo<int> b;
        a = b;
        EXPECT_EQ(a.Size(), 0);
        EXPECT_EQ(a.Empty(), true);
    }
    {
        StackDuplicateFifo<int> stack;
        for (int i = 0; i < 5; ++i)
        {
            stack.Push(i);
        }
        StackDuplicateFifo<int> copy_stack;
        copy_stack = stack;
        EXPECT_EQ(stack.Size(), 5);
        EXPECT_EQ(stack.Empty(), false);

        while (!stack.Empty())
        {
            EXPECT_EQ(stack.Size(), copy_stack.Size());
            EXPECT_EQ(stack.Top(), copy_stack.Top());
            stack.Pop();
            copy_stack.Pop();
        }
    }
}

TEST(BasicTest, SelfCopyAssignment)
{
    {
        StackDuplicateFifo<int> a;
        auto& r = a;
        a = r;
        EXPECT_EQ(a.Size(), 0);
        EXPECT_EQ(a.Empty(), true);
    }
    {
        std::vector<int> expected = {0, 1, 2, 3, 4};
        StackDuplicateFifo<int> a;
        for (int i = 0; i < 5; ++i)
        {
            a.Push(i);
        }
        auto& r = a;
        a = r;
        EXPECT_EQ(a.Size(), 5);
        EXPECT_EQ(a.Empty(), false);

        while (!expected.empty())
        {
            EXPECT_EQ(a.Size(), expected.size());
            EXPECT_EQ(a.Top(), expected.back());
            a.Pop();
            expected.pop_back();
        }
    }
}

TEST(BasicTest, ValidAfterMove)
{
    StackDuplicateFifo<int> stack;
    for (int i = 0; i < 5; ++i)
    {
        stack.Push(i);
    }
    StackDuplicateFifo<int> copy_stack = std::move(stack);
    //    stack.Clear();
    EXPECT_EQ(copy_stack.Size(), 5);
    EXPECT_EQ(copy_stack.Empty(), false);

    for (int i = 0; i < 5; ++i)
    {
        stack.Push(i);
    }
    while (!copy_stack.Empty())
    {
        EXPECT_EQ(stack.Size(), copy_stack.Size());
        EXPECT_EQ(stack.Top(), copy_stack.Top());
        stack.Pop();
        copy_stack.Pop();
    }
}

TEST(BasicTest, StackBehaviour)
{
    std::stack<int> expected;
    for (int i = 0; i < 100; ++i)
    {
        expected.push(i);
    }

    StackDuplicateFifo<int> stack;
    for (int i = 0; i < 100; ++i)
    {
        stack.Push(i);
    }

    while (!expected.empty())
    {
        EXPECT_EQ(stack.Size(), expected.size());
        EXPECT_EQ(stack.Top(), expected.top());
        stack.Pop();
        expected.pop();
    }
    EXPECT_EQ(stack.Size(), expected.size());
    EXPECT_EQ(stack.Empty(), expected.empty());
}

TEST(StackDuplicateFifoBehaviour, SimpleTest)
{
    StackDuplicateFifo<int> stack;
    stack.Push(5);
    ASSERT_EQ(stack.Top(), 5);
    stack.Push(3);
    ASSERT_EQ(stack.Top(), 3);
    stack.Push(2);
    ASSERT_EQ(stack.Top(), 2);
    stack.Pop();
    ASSERT_EQ(stack.Top(), 3);
    stack.Push(5);
    ASSERT_EQ(stack.Top(), 5);
    stack.Pop();
    ASSERT_EQ(stack.Top(), 5);
    stack.Pop();
    ASSERT_EQ(stack.Top(), 3);
    stack.Pop();
    ASSERT_EQ(stack.Size(), 0);
    ASSERT_EQ(stack.Empty(), true);
}

TEST(StackDuplicateFifoBehaviour, OnlyEqualElem)
{
    std::vector<int> expected(5, 7);
    StackDuplicateFifo<int> stack;
    for (int i = 0; i < expected.size(); ++i)
    {
        stack.Push(7);
    }

    while (!expected.empty())
    {
        EXPECT_EQ(stack.Size(), expected.size());
        EXPECT_EQ(stack.Top(), expected.back());
        stack.Pop();
        expected.pop_back();
    }
    EXPECT_EQ(stack.Size(), expected.size());
    EXPECT_EQ(stack.Empty(), expected.empty());
}

TEST(StackDuplicateFifoBehaviour, DifferentElem)
{
    std::vector<int> expected = {0, 0, 0, 1, 1, 1, 2, 2, 2};
    StackDuplicateFifo<int> stack;
    for (int i = 0; i < expected.size(); ++i)
    {
        stack.Push(i % 3);
    }

    while (!expected.empty())
    {
        EXPECT_EQ(stack.Size(), expected.size());
        EXPECT_EQ(stack.Top(), expected.back());
        stack.Pop();
        expected.pop_back();
    }
    EXPECT_EQ(stack.Size(), expected.size());
    EXPECT_EQ(stack.Empty(), expected.empty());
}

template <typename T>
class SlowStackDuplicateFifo
{
public:
    T& Top() noexcept
    {
        return m_stack.back();
    }
    const T& Top() const noexcept
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
    }
    void Push(T&& value)
    {
        m_stack.push_back(std::move(value));
    }

    // complexity: O(n)
    void Pop()
    {
        for (auto it = m_stack.begin(), it_end = m_stack.end(); it != it_end; ++it)
        {
            if (*it == m_stack.back())
            {
                m_stack.erase(it);
                return;
            }
        }
    }
private:
    std::list<T> m_stack;
};

TEST(StackDuplicateFifoBehaviour, RandomFilled)
{
    constexpr int num_iterations = 10'000;
    std::mt19937 gen(735'675);
    std::uniform_int_distribution dist(1, 1000);

    StackDuplicateFifo<int> stack;
    SlowStackDuplicateFifo<int> expected;

    for (int i = 0; i < num_iterations; ++i) {
        auto value = dist(gen);
        stack.Push(value);
        expected.Push(value);
    }
    EXPECT_EQ(stack.Size(), expected.Size());
    EXPECT_EQ(stack.Top(), expected.Top());

    while (!expected.Empty()) {
        EXPECT_EQ(stack.Size(), expected.Size());
        EXPECT_EQ(stack.Top(), expected.Top());
        stack.Pop();
        expected.Pop();
    }
    EXPECT_EQ(stack.Size(), expected.Size());
    EXPECT_EQ(stack.Empty(), expected.Empty());
}

TEST(StackDuplicateFifoBehaviour, Stress)
{
    constexpr int num_iterations = 100'000;
    std::mt19937 gen(735'675);
    std::uniform_int_distribution dist(1, 100);

    StackDuplicateFifo<int> stack;
    SlowStackDuplicateFifo<int> expected;

    for (int i = 0; i < num_iterations; ++i) {
        auto code = dist(gen);
        if (code > 70 && !expected.Empty())
        {
            EXPECT_EQ(stack.Top(), expected.Top());
            stack.Pop();
            expected.Pop();
        }
        else
        {
            stack.Push(code);
            expected.Push(code);
        }
    }
    EXPECT_EQ(stack.Size(), expected.Size());
    EXPECT_EQ(stack.Top(), expected.Top());

    while (!expected.Empty()) {
        EXPECT_EQ(stack.Size(), expected.Size());
        EXPECT_EQ(stack.Top(), expected.Top());
        stack.Pop();
        expected.Pop();
    }
    EXPECT_EQ(stack.Size(), expected.Size());
    EXPECT_EQ(stack.Empty(), expected.Empty());
}