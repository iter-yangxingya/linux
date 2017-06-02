//
// \file quick_merge_weight.cpp
// \brief quick merge improve with weight...
//

#include <stdio.h>
#define N 10000

int main() {
    int id[N];
    int sz[N];

    for (int i = 0; i < N; i++) {
        id[i] = i;
        sz[i] = 1;
    }

    int p;
    int q;
    while(scanf("%d %d", &p, &q) == 2) {
        int i;
        int j;
        for (i = p; i != id[i]; i = id[i]);
        for (j = q; j != id[j]; j = id[j]);

        if (i != j) {
            if (sz[i] > sz[j]) {
                id[j] = i;
                sz[i] += sz[j];
                printf("[%d->%d]", j, i);
            } else {
                id[i] = j;
                sz[j] += sz[i];
                printf("[%d->%d]", i, j);
            }
        } else {
            printf("[CON]");
        }
        for (i = 0; i < 10; i++)
            printf(" %d", id[i]);
        printf("\n");
    }
    return 0;
}
