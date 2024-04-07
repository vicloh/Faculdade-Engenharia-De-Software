#include <stdio.h>
//Apresenta um printf para cada resposta a ser digitada
int main(){    
    int n , i , a;

    scanf("%d", &n);

    for(i = 1; i <= n; i++){
        scanf("%d", &a);
        printf("resposta %d: %d\n", i , a);
    }

    return 0; 
}