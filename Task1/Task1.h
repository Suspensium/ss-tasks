#pragma once

#include <cstdio>

namespace str_list {
    // Adds string to list
    void add_string(char ***list, const char *str);

    // Removes string from list. Returns true if string was removed
    bool remove_string(char ***list, const char *str);

    void clear(char ***list);

    // Returns true if index found, false otherwise
    bool match_index(char ***list, const char *str, unsigned int &found_index);

    // Returns number of strings in list
    size_t num_items(char ***list);

    // Remove all duplicates in list
    void remove_duplicates(char ***list);

    // Replace string with different string. Returns true if replaced successfully
    bool replace_str(char ***list, const char *str_to_replace, const char *str_to_insert);

    // Sorts list with bubble sort
    void sort(char ***list);

    // Prints list to the console
    inline void print(char ***list) {
        if (list == nullptr || *list == nullptr) return;

        for (int i = 0; (*list)[i] != nullptr; ++i) {
            printf("%s ", (*list)[i]);
        }

        printf("\n");
    }

    inline void run_task1() {
        char **list = nullptr;

        add_string(&list, "Dynamically");
        add_string(&list, "sized");
        add_string(&list, "sized");
        add_string(&list, "C");
        add_string(&list, "list");
        add_string(&list, "list");
        add_string(&list, "Dynamically");
        add_string(&list, "of");
        add_string(&list, "sized");
        add_string(&list, "C");
        add_string(&list, "strings");
        add_string(&list, "list");
        add_string(&list, "sized");
        add_string(&list, "C");
        add_string(&list, "A");
        add_string(&list, "B");
        add_string(&list, "E");
        add_string(&list, "G");

        printf("Initial list: \n");
        print(&list);
        printf("Size: %llu\n", num_items(&list));
        printf("\n");

        if (unsigned int index; match_index(&list, "of", index)) {
            printf("'of': Matched index at: %d\n", index);
        }

        remove_string(&list, "sized");

        print(&list);
        printf("Size: %llu\n", num_items(&list));

        remove_duplicates(&list);

        print(&list);
        printf("Size: %llu\n", num_items(&list));

        replace_str(&list, "list", "LIST");
        replace_str(&list, "G", "C++");
        print(&list);

        sort(&list);
        print(&list);
        printf("Size: %llu\n", num_items(&list));

        clear(&list);
        print(&list);
        printf("Size: %llu\n", num_items(&list));
    }
}
