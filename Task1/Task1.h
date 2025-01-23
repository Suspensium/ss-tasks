#pragma once

#include <cstdio>

/* Comment section
 * comment
also comment
  */

namespace str_list {
    // Adds string to list
    void add_string(char ***list, const char *str);

    // Removes string from list
    void remove_string(char ***list, const char *str);

    void clear(char ***list);

    // Returns index of found string, NULL if not found
    size_t match_index(char ***list, const char *str);

    // Returns number of strings in list
    size_t num_items(char ***list);

    // Remove all duplicates in list
    void remove_duplicates(char ***list);

    // Replace string with different string
    void replace_str(char ***list, const char *str_to_replace, const char *str_to_insert);

    // Sorts list with bubble sort
    void sort(char ***list);

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

        printf("Matched index at: %llu\n", match_index(&list, "of"));

        printf("Size: %llu\n", num_items(&list));
        print(&list);

        remove_string(&list, "sized");

        printf("Size: %llu\n", num_items(&list));
        print(&list);

        remove_duplicates(&list);
        print(&list);

        replace_str(&list, "list", "LIST");
        replace_str(&list, "G", "C++");
        print(&list);

        sort(&list);
        printf("Size: %llu\n", num_items(&list));
        print(&list);

        clear(&list);
        printf("Size: %llu\n", num_items(&list));
        print(&list);
    }
}
