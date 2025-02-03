#include <fstream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../Task1/Task1.h"
#include "../Task2/Task2.h"
#include "../Task3/Task3.h"

TEST(TestTask1, Test1) {
    using namespace str_list;

    char **list = nullptr;
    add_string(&list, "Dynamically");

    EXPECT_TRUE(list != nullptr);

    add_string(&list, "sized");
    add_string(&list, "list");

    EXPECT_TRUE(num_items(&list) == 3);

    replace_str(&list, "list", "LIST");

    unsigned int index;
    EXPECT_TRUE(match_index(&list, "LIST", index));
    EXPECT_TRUE(index == 2);

    EXPECT_FALSE(match_index(&list, "Missing string", index));

    clear(&list);

    EXPECT_TRUE(list == nullptr);
    EXPECT_FALSE(num_items(&list) != 0);

    add_string(&list, "I live again!");

    EXPECT_TRUE(list != nullptr);
    EXPECT_TRUE(num_items(&list) == 1);
}

TEST(TestTask2Union, Test2Union) {
    AnyType anyType1 = 1;

    EXPECT_NO_THROW(anyType1.getInt());

    anyType1 = 2.621515;
    EXPECT_NO_THROW(anyType1.getDouble());
    EXPECT_THROW(anyType1.getInt(), std::bad_cast);

    anyType1 = true;
    EXPECT_NO_THROW(anyType1.getBool());
    EXPECT_THROW(anyType1.getInt(), std::bad_cast);
}

TEST(TestTask2Variadic, Test2Variadic) {
    VariadicType variadicType1 = 1;
    EXPECT_NO_THROW(variadicType1.get<int>());

    variadicType1 = 2.621515;
    EXPECT_NO_THROW(variadicType1.get<double>());
    EXPECT_THROW(variadicType1.get<int>(), std::bad_variant_access);

    variadicType1 = true;
    EXPECT_THROW(std::any_cast<int>(variadicType1.get()), std::bad_any_cast);
}

TEST(TestTask3, Test3) {
    namespace fs = std::filesystem;

    std::ofstream ofstream;

    EXPECT_NO_THROW(CodeReader fileReader("Task3/Task3.h", fs::file_type::regular));
    EXPECT_NO_THROW(CodeReader dirReader("Task3", fs::file_type::directory));
    EXPECT_THROW(CodeReader errReader("test.cpp", fs::file_type::directory), std::runtime_error);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
