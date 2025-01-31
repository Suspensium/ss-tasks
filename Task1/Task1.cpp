#include "Task1.h"

#include <stdlib.h>
#include <string.h>

void str_list::add_string(char ***list, const char *str) {
    if (list == nullptr) return;

    if (*list == nullptr) {
        *list = static_cast<char **>(malloc(sizeof(char *) * 2));

        (*list)[0] = strdup(str);
        (*list)[1] = nullptr;
    } else {
        int list_size = 0;
        while ((*list)[list_size] != nullptr) ++list_size;

        *list = static_cast<char **>(realloc(*list, sizeof(char *) * (list_size + 2)));

        (*list)[list_size] = strdup(str);
        (*list)[list_size + 1] = nullptr;
    }
}

void str_list::remove_string(char ***list, const char *str) {
    if (list == nullptr || *list == nullptr) return;

    for (int i = 0; (*list)[i] != nullptr; ++i) {
        if (strcmp((*list)[i], str) != 0) continue;

        free((*list)[i]);

        for (int j = i; (*list)[j] != nullptr; ++j) {
            (*list)[j] = (*list)[j + 1];
        }

        --i;
    }
}

void str_list::clear(char ***list) {
    if (list == nullptr || *list == nullptr) return;

    for (int i = 0; (*list)[i] != nullptr; ++i) {
        free((*list)[i]);
        (*list)[i] = nullptr;
    }
    free(*list);
    *list = nullptr;
}

size_t str_list::match_index(char ***list, const char *str) {
    if (list == nullptr || *list == nullptr) return NULL;

    for (int i = 0; (*list)[i] != nullptr; ++i) {
        if (strcmp((*list)[i], str) != 0) continue;

        return i;
    }

    return NULL;
}

size_t str_list::num_items(char ***list) {
    if (list == nullptr || *list == nullptr) return 0;

    int list_size = 0;
    while ((*list)[list_size] != nullptr) ++list_size;

    return list_size;
}

void str_list::remove_duplicates(char ***list) {
    if (list == nullptr || *list == nullptr) return;

    if (num_items(list) == 1) return;

    for (int i = 0; (*list)[i] != nullptr; ++i) {
        for (int j = i + 1; (*list)[j] != nullptr; ++j) {
            if (strcmp((*list)[i], (*list)[j]) != 0) continue;

            free((*list)[j]);

            for (int k = j; (*list)[k] != nullptr; ++k) {
                (*list)[k] = (*list)[k + 1];
            }

            --j;
        }
    }
}

void str_list::replace_str(char ***list, const char *str_to_replace, const char *str_to_insert) {
    if (list == nullptr || *list == nullptr) return;

    for (int i = 0; (*list)[i] != nullptr; ++i) {
        if (strcmp((*list)[i], str_to_replace) != 0) continue;

        (*list)[i] = strdup(str_to_insert);
    }
}

void str_list::sort(char ***list) {
    if (list == nullptr || *list == nullptr) return;

    const size_t list_size = num_items(list);

    for (int i = 0; i < list_size - 1; ++i) {
        for (int j = 0; j < list_size - 1 - i; ++j) {
            if (strcmp((*list)[j], (*list)[j + 1]) > 0) {
                char *temp = (*list)[j];
                (*list)[j] = (*list)[j + 1];
                (*list)[j + 1] = temp;
            }
        }
    }
}
