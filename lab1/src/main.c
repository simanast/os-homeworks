#include <stdio.h>

extern int f();
extern int b();

int main() {
    printf("%d\n", f());
    printf("%d\n", b());
    return 0;
}
