//
// \file path_compression.cpp
// \brief path compression for quick union with weighted.
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
    while (scanf("%d %d", &p, &q) == 2) {
        int i;
        int j;
        for (i = p; i != id[i]; i = id[i]) ;
        for (j = q; j != id[j]; j = id[j]) ;

        if (i != j) {
            int s = 0;
            int t;
            if (sz[i] > sz[j]) {
                j = q;
                do {
                    t = id[j];
                    id[j] = i;
                    if (j == t)
                        break;
                    s = sz[j];
                    if (sz[j] > 1) sz[j]--;
                    j = t;
                } while (true);
                sz[i] += s + 1;
                sz[j] -= s;
            } else {
                i = p;
                do {
                    t = id[i];
                    id[i] = j;
                    if (i == t)
                        break;
                    s = sz[i];
                    if (sz[i] > 1) sz[i]--;
                    i = t;
                } while (true);
                sz[j] += s + 1;
                sz[i] -= s;
            }
            printf("[%d-%d]", p, q);
        } else {
            printf("[CON]");
        }

        for (i = 0; i < 10; i++)
            printf(" %d", id[i]);
        printf("\n[siz]");
        for (i = 0; i < 10; i++)
            printf(" %d", sz[i]);
        printf("\n");
    }
    return 0;
}
