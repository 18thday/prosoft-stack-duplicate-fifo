#include <cassert>

#include "stack_duplicate_fifo.h"


int main()
{
    StackDuplicateFifo<int> stack;
    stack.Push(5);
    assert(stack.Top() == 5);
    stack.Push(3);
    assert(stack.Top() == 3);
    stack.Push(2);
    assert(stack.Top() == 2);
    stack.Pop();
    assert(stack.Top() == 3);
    stack.Push(5);
    assert(stack.Top() == 5);
    stack.Pop();
    assert(stack.Top() == 5);
    stack.Pop();
    assert(stack.Top() == 3);
    return 0;
}
