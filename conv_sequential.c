#include<stdio.h>
#include<stdlib.h>

int main(){
    // ---- input and malloc A, F ----
    int NA, NF;
    scanf("%d %d", &NA, &NF);
    int *A = malloc(sizeof(int) * NA);
    int *F = malloc(sizeof(int) * NF);

    for(int i = 0; i < NA; i++){
        scanf("%d", &A[i]);
    }
    for(int i = 0; i < NF; i++){
        scanf("%d", &F[i]);
    }
    // ---- end input and malloc----

    int *res = calloc((NA + NF - 1),sizeof(int));
    for (int i = 0; i < NA; i++) {
        for (int j = 0; j < NF; j++) {
            res[i + j] += A[i] * F[j];
        }
    }

    for(int i = NF - 1; i < NA; i++){
        printf("%d\n",res[i]);
    }

    // ---- free memory ----
    free(F);
    free(A);
    free(res);
    // ---- end free ----
    return 0;
}

