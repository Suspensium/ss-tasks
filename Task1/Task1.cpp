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
        const size_t list_size = num_items(list);

        *list = static_cast<char **>(realloc(*list, sizeof(char *) * (list_size + 2)));

        (*list)[list_size] = strdup(str);
        (*list)[list_size + 1] = nullptr;
    }
}

bool str_list::remove_string(char ***list, const char *str) {
    if (list == nullptr || *list == nullptr) return false;

    bool bFound = false;
    for (int i = 0; (*list)[i] != nullptr; ++i) {
        if (strcmp((*list)[i], str) != 0) continue;

        free((*list)[i]);

        for (int j = i; (*list)[j] != nullptr; ++j) {
            (*list)[j] = (*list)[j + 1];
        }

        --i;
        bFound = true;
    }

    return bFound;
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

bool str_list::match_index(char ***list, const char *str, unsigned int &found_index) {
    if (list == nullptr || *list == nullptr) return false;

    for (int i = 0; (*list)[i] != nullptr; ++i) {
        if (strcmp((*list)[i], str) == 0) {
            found_index = i;
            return true;
        }
    }

    return false;
}

size_t str_list::num_items(char ***list) {
    if (list == nullptr || *list == nullptr) return 0;

    int list_size = 0;
    while ((*list)[list_size] != nullptr) ++list_size;

    return list_size;
}

void str_list::remove_duplicates(char ***list) {
    if (list == nullptr || *list == nullptr) return;

    const size_t list_size = num_items(list);
    if (list_size < 2) return;

    for (int i = 0; i < list_size; ++i) {
        if ((*list)[i] == nullptr) continue;
        for (int j = i + 1; j < list_size; ++j) {
            if ((*list)[i] == nullptr || (*list)[j] == nullptr || strcmp((*list)[i], (*list)[j]) != 0) continue;

            free((*list)[j]);
            (*list)[j] = nullptr;
        }
    }

    int newIndex = 0;
    for (int i = 0; i < list_size; ++i) {
        if ((*list)[i] != nullptr) {
            (*list)[newIndex++] = (*list)[i];
        }
    }

    (*list)[newIndex] = nullptr;
}

bool str_list::replace_str(char ***list, const char *str_to_replace, const char *str_to_insert) {
    if (list == nullptr || *list == nullptr) return false;

    for (int i = 0; (*list)[i] != nullptr; ++i) {
        if (strcmp((*list)[i], str_to_replace) == 0) {
            free((*list)[i]);
            (*list)[i] = strdup(str_to_insert);
            return true;
        }
    }

    return false;
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
