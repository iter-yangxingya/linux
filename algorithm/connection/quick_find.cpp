//
// \file quick_find.cpp
// \brief quick find for connection problem...
//

#include <stdio.h>

#define N 10000

int main() {

    int id[N];
    for (int i = 0; i < N; i++) id[i] = i;

    int p;
    int q;
    printf("begin......\n");
    while (scanf("%d %d", &p, &q) == 2) {
        if (id[p] != id[q]) {
            for (int i = 0; i < N; i++) {
                if (id[i] == id[p])
                    id[i] = id[q];
            }
            printf("[%d %d]", p, q);
        } else {
            printf("[CON]");
        }

        for (int i = 0; i < 10; i++)
            printf(" %d", id[i]);
        printf("\n");
    }

    return 0;
}
