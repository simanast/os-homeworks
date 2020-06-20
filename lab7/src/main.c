#include <stdio.h>
#include <stdint.h>


void ChangeCase(char* string, int len) {
    if (!len)
        return;
    while (len >= 8) {
        (*(uint64_t*) string) ^= 0b0010000000100000001000000010000000100000001000000010000000100000;
        string += 8;
        len -= 8;
    }
    while (len >= 4) {
        (*(uint32_t*) string) ^= 0b100000001000000010000000100000;
        string += 4;
        len -= 4;
    }
    while (len >= 2) {
        (*(uint16_t*) string) ^= 0b10000000100000;
        string += 2;
        len -= 2;
    }
    if (len)
        (*(int*) string) ^= 0b100000;
}

int main(int argc, char** argv) {
    char* str = argv[1];
//    scanf("%s", str);
    int change_count = 0;       // счётчик подряд идущих букв
    char* change_str = str;     // указатель на первый символ из несколько подряд идущих букв
    char* iter = str;
    while (*iter != '\0') {
        if ((*iter >= 'A' && *iter <= 'Z') ||
            (*iter >= 'a' && *iter <= 'z')) {
            change_count++;
        } else {
            // если встретили небуквенный символ, то в цепочке подряд идущих перед ним букв меняем регистр
            ChangeCase(change_str, change_count);
            change_count = 0;
            change_str = iter + 1;
        }
        iter++;
    }

    if (change_count)
        // если строка завершается цепочкой подряд идущих букв
        ChangeCase(change_str, change_count);
    printf("%s\n", str);
    return 0;
}
