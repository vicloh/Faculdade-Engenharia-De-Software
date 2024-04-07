#include <stdio.h>

int main() {
 
    int x , y , soma = 0;
    int troca;
    int i;
    
    scanf("%d", &x);
    scanf("%d", &y);
    
    if(x > y){
        troca = x;
        x = y;
        y = troca;
    }
    
    for(i = x + 1; i < y; i++){
        if(i % 2 != 0){
            soma += i;
        }
    }
    
    printf("%d\n", soma);
 
    return 0;
}