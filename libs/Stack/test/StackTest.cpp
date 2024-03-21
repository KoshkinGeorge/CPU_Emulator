#include <gtest/gtest.h>
#include "../include/Stack.hpp"
#include <iostream>


TEST(StackTest, default_constructor_test)
{
    ASSERT_NO_THROW(Stack<unsigned> s);
}

TEST(StackTest, size_constructor_test)
{
    ASSERT_NO_THROW(Stack<unsigned> s(1024));
}

TEST(StackTest, moving_constructor_test)
{
    Stack<unsigned> s(1024);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    Stack<unsigned> s2 = std::move(s);
    ASSERT_EQ(s2.get_top(), 5);
}

TEST(StackTest, moving_constructor_test2)
{
    Stack<unsigned> s(1024);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    Stack<unsigned> s2(std::move(s));
    ASSERT_EQ(s2.get_top(), 5);
}

TEST(StackTest, push_test)
{
    Stack<unsigned> s(1024);
    s.push(2);
    ASSERT_EQ(s.get_top(), 2);
}

TEST(StakTest, get_size_test)
{
    Stack<unsigned> s(1024);
    ASSERT_EQ(s.get_size(), 0);
    s.push(1);
    ASSERT_FALSE(s.empty());
}

TEST(StakTest, empty_test)
{
    Stack<unsigned> s(1024);
    ASSERT_TRUE(s.empty());
    s.push(1);
    ASSERT_FALSE(s.empty());
}

TEST(StakTest, clear_test)
{
    Stack<unsigned> s(1024);
    s.push(1);
    ASSERT_FALSE(s.empty());
    s.clear();
    ASSERT_TRUE(s.empty());
}

TEST(StackTest, get_top_test)
{
    Stack<unsigned> s(1024);
    ASSERT_ANY_THROW(s.get_top());
    s.push(1);
    ASSERT_EQ(s.get_top(), 1);
}

TEST(StackTest, pop_test)
{
    Stack<unsigned> s(1024);
    ASSERT_ANY_THROW(s.get_top());
    s.push(1);
    s.push(2);
    s.pop();
    ASSERT_EQ(s.get_top(), 1);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
