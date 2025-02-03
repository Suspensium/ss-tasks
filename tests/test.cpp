#include <fstream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../Task1/Task1.h"
#include "../Task2/Task2.h"
#include "../Task3/Task3.h"

TEST(TestTask1, Test1) {
    using namespace str_list;

    char **list = nullptr;
    EXPECT_NO_THROW(add_string(&list, "Dynamically"));

    EXPECT_TRUE(list != nullptr);

    EXPECT_NO_THROW(add_string(&list, "sized"));
    EXPECT_NO_THROW(add_string(&list, "sized"));
    EXPECT_NO_THROW(add_string(&list, "Dynamically"));
    EXPECT_NO_THROW(add_string(&list, "list"));

    EXPECT_TRUE(num_items(&list) == 5);

    EXPECT_FALSE(remove_string(&list, "s"));

    EXPECT_TRUE(replace_str(&list, "list", "LIST"));

    unsigned int index;
    EXPECT_TRUE(match_index(&list, "LIST", index));

    EXPECT_NO_THROW(sort(&list));

    EXPECT_FALSE(match_index(&list, "Missing string", index));

    EXPECT_NO_THROW(remove_duplicates(&list));
    EXPECT_NO_THROW(clear(&list));

    EXPECT_TRUE(list == nullptr);
    EXPECT_FALSE(num_items(&list) != 0);

    EXPECT_NO_THROW(add_string(&list, "I live again!"));

    EXPECT_TRUE(list != nullptr);
    EXPECT_TRUE(num_items(&list) == 1);

    EXPECT_NO_THROW(print(&list));
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

    AnyType anyType2 = anyType1;
    EXPECT_NO_THROW(anyType2.getBool());

    AnyType anyType3 = std::move(anyType2);
    EXPECT_THROW(anyType2.getInt(), std::bad_cast);
    EXPECT_NO_THROW(anyType3.getBool());

    anyType1 = -51261;
    anyType1.swap(anyType3);
    EXPECT_NO_THROW(anyType1.getBool());
    EXPECT_NO_THROW(anyType3.getInt());
}

TEST(TestTask2Variadic, Test2Variadic) {
    VariadicType variadicType1 = 1;
    EXPECT_NO_THROW(variadicType1.get<int>());

    variadicType1 = 2.621515;
    EXPECT_NO_THROW(variadicType1.get<double>());
    EXPECT_THROW(variadicType1.get<int>(), std::bad_variant_access);

    variadicType1 = true;
    EXPECT_THROW(std::any_cast<int>(variadicType1.get()), std::bad_any_cast);

    VariadicType variadicType2 = variadicType1;
    EXPECT_NO_THROW(variadicType1.get<bool>());

    VariadicType variadicType3 = std::move(variadicType2);
    EXPECT_THROW(variadicType2.get<int>(), std::bad_variant_access);
    EXPECT_NO_THROW(variadicType3.get<bool>());

    variadicType3 = 515.6262f;
    variadicType1.swap(variadicType3);
    EXPECT_NO_THROW(variadicType1.get<float>());
    EXPECT_NO_THROW(variadicType3.get<bool>());
}

TEST(TestTask3, Test3) {
    namespace fs = std::filesystem;

    std::ofstream ofstream;
    std::unique_ptr<CodeReader> fileReader;
    std::unique_ptr<CodeReader> dirReader;
    std::unique_ptr<CodeReader> errReader;

    EXPECT_NO_THROW(fileReader = std::make_unique<CodeReader>("Task3/Task3.h", fs::file_type::regular));
    EXPECT_NO_THROW(dirReader = std::make_unique<CodeReader>("Task3", fs::file_type::directory));
    EXPECT_THROW(errReader = std::make_unique<CodeReader>("test.cpp", fs::file_type::directory), std::runtime_error);

    EXPECT_NO_THROW(fileReader->outputInfo(ofstream));
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
