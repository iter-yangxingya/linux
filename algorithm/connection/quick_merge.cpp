//
// \file quick_merge.cpp
// \brief quick merge for connection.
//

#include <stdio.h>
#define N 10000

int main() {
    int id[N];
    for (int i = 0; i < N; i++) id[i] = i;

    int p;
    int q;
    while (scanf("%d %d", &p, &q) == 2) {
        int i;
        int j;
        for (i = p; i != id[i]; i = id[i]);
        for (j = q; j != id[j]; j = id[j]);

        if (i != j) {
            id[i] = j;
            printf("[%d->%d]", i, j);
        } else {
            printf("[CONN]");
        }

        for (i = 0; i < 10; i++)
            printf(" %d", id[i]);
        printf("\n");
    }

    return 0;
}
