#include <stdio.h>
//Lê valores e os trocam de lugar para mudar a ordem 
int main(){
    
    int o , a , b , c;
    
    scanf("%d", &o);
    scanf("%d", &a);
    scanf("%d", &b);
    
    c = o - a - b;
    //comentario // cometario2 // comentario 3
    if(c < a){
        c = a;
    }
    
    if(c < b){
        c = b;
    }
    
    printf("%d\n", c);

    return 0;
}