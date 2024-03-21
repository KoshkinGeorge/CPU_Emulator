#include <gtest/gtest.h>
#include "../include/Stack.hpp"
#include <iostream>

class InitialStack: public ::testing::Test
{
protected:
    void SetUp()
    {
        s = new Stack<unsigned>(1024);
        s->push(1);
        s->push(2);
        s->push(3);
        s->push(4);
        s->push(5);
    }
    void TearDown()
    {
        delete s;
    }
    Stack<unsigned> *s;
};

class EmptyStack: public ::testing::Test
{
protected:
    void SetUp()
    {
        s = new Stack<unsigned>(1024);
    }
    void TearDown()
    {
        delete s;
    }
    Stack<unsigned> *s;
};

class SmallStack: public::testing::Test
{
protected:
    void SetUp()
    {
        s = new Stack<unsigned>(1);
    }

    void TearDown()
    {
        delete s;
    }
    Stack<unsigned> *s;
};

TEST_F(EmptyStack, clear_test)
{
    ASSERT_EQ(s->get_size(), 0);
}

TEST(ConstructorTests, default_constructor_test)
{
    ASSERT_NO_THROW(Stack<unsigned> s);
    Stack<unsigned> s;
    ASSERT_TRUE(s.empty());
}

TEST(ConstructorTests, size_constructor_test)
{
    ASSERT_NO_THROW(Stack<unsigned> s(1024));
    Stack<unsigned> s(1024);
}

TEST(ConstructorTests, moving_constructor_test)
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

TEST(ConstructorTests, moving_constructor_test2)
{
    Stack<unsigned> s(1024);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    Stack<unsigned> s2(std::move(s));
    ASSERT_EQ(s2.get_top(), 5);
    ASSERT_EQ(s.get_size(), 0);
}

TEST(ConstructorTests, copying_contructor_test)
{
    Stack<unsigned> s(1024);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    Stack<unsigned> s2(s);
    ASSERT_EQ(s2.get_top(), 5);
    ASSERT_EQ(s2.get_size(), 5);

    s.pop();
    ASSERT_EQ(s2.get_size(), 5);
    ASSERT_EQ(s2.get_top(), 5);
}

TEST(ConstructorTests, copying_contructor_test2)
{
    Stack<unsigned> s(1024);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    Stack<unsigned> s2 = s;
    ASSERT_EQ(s2.get_top(), 5);
    ASSERT_EQ(s2.get_size(), 5);

    s.pop();
    ASSERT_EQ(s2.get_size(), 5);
    ASSERT_EQ(s2.get_top(), 5);
}

TEST_F(EmptyStack, push_test)
{
    s->push(2);
    ASSERT_EQ(s->get_top(), 2);
}

TEST_F(EmptyStack, get_size_test)
{
    ASSERT_EQ(s->get_size(), 0);
    s->push(1);
    ASSERT_FALSE(s->empty());
}

TEST_F(EmptyStack, empty_test)
{
    ASSERT_TRUE(s->empty());
    s->push(1);
    ASSERT_FALSE(s->empty());
}

TEST_F(InitialStack, clear_test)
{
    ASSERT_FALSE(s->empty());
    s->clear();
    ASSERT_TRUE(s->empty());
}

TEST_F(EmptyStack, get_top_test)
{
    ASSERT_ANY_THROW(s->get_top());
    s->push(1);
    ASSERT_EQ(s->get_top(), 1);
}

TEST_F(EmptyStack, pop_test)
{
    ASSERT_ANY_THROW(s->get_top());
    s->push(1);
    s->push(2);
    s->pop();
    ASSERT_EQ(s->get_top(), 1);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
