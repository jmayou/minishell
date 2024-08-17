#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_space(char c) {
    return (c == ' ' || c == '\t');
}

char *get_last_word(char *str) {
    int len = strlen(str);
    while (len > 0 && !is_space(str[len - 1])) {
        len--;
    }
    char *last_word = strdup(&str[len]);
    str[len] = '\0';
    return last_word;
}

char *get_first_word(char *str) {
    int len = 0;
    while (str[len] && !is_space(str[len])) {
        len++;
    }
    char *word = (char *)malloc(len + 1);
    strncpy(word, str, len);
    word[len] = '\0';
    memmove(str, str + len, strlen(str) - len + 1);
    return word;
}

char **ft_join(char **str) {
    int i = 0;
    while (str[i] && str[i + 1]) {
        int current_len = strlen(str[i]);
        int next_len = strlen(str[i + 1]);

        if (!is_space(str[i][current_len - 1]) && (str[i + 1][0] == '\'' || str[i + 1][0] == '"')) {
            char *last_word = get_last_word(str[i]);
            int new_len = next_len + strlen(last_word) + 1;
            char *new_next = (char *)malloc(new_len);

            new_next[0] = str[i + 1][0];
            strcpy(&new_next[1], last_word);
            strcpy(&new_next[1 + strlen(last_word)], &str[i + 1][1]);

            free(str[i + 1]);
            str[i + 1] = new_next;
            free(last_word);
        } 
        else if ((str[i][current_len - 1] == '\'' || str[i][current_len - 1] == '"') && !is_space(str[i + 1][0])) {
            char *first_word = get_first_word(str[i + 1]);
            int new_len = current_len + strlen(first_word);
            char *new_current = (char *)malloc(new_len);

            strncpy(new_current, str[i], current_len - 1);
            strcpy(&new_current[current_len - 1], first_word);
            new_current[current_len - 1 + strlen(first_word)] = str[i][current_len - 1];
            new_current[new_len - 1] = '\0';

            free(str[i]);
            str[i] = new_current;
            free(first_word);
        } 
        else if ((str[i][current_len - 1] == '\'' || str[i][current_len - 1] == '"') &&
                 (str[i + 1][0] == '\'' || str[i + 1][0] == '"')) {
            int new_len = current_len + next_len - 2;
            char *new_current = (char *)malloc(new_len);

            strncpy(new_current, str[i], current_len - 1);
            strncpy(&new_current[current_len - 1], &str[i + 1][1], next_len - 2);
            new_current[new_len - 1] = str[i][current_len - 1];

            free(str[i]);
            str[i] = new_current;
        }
        i++;
    }
    return str;
}

int main() {
    char *strings[] = {strdup("H "), strdup("tt"), strdup("r st"), strdup("\"In\""), NULL};

    char **result = ft_join(strings);

    for (int i = 0; result[i] != NULL; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }

    return 0;
}