/******************************************************************************
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


void imprimeSolucaoSistemaLinear(){
    
    int n;
    
    printf("Digite a dimensão da matriz quadrada:\n");
    
    scanf("%d", &n);
    system("cls");
    int matriz[n][n];
    
    printf("Digite os valores da matriz com espaço entre eles:\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d", &matriz[i][j]);
        }
    }
    
    printf("Aqui está os valores da matriz:\n");
    for(int i=0; i<n; i++){
        printf("\n");
        for(int j=0; j<n; j++){
            printf("%d ", matriz[i][j]);
        }
    }
    printf("\n");
}
 
int main(){

                                                
    int a;

    do{
        printf("Digite o número da opção desejada: ");
        printf("\n1- Resolução de Sistemas Lineares\n");
        printf("0- Encerra o programa\n");
        scanf("%d", &a);
        system("cls");
       switch(a){
            
            case 1:
                imprimeSolucaoSistemaLinear();
                break;
            
            case 0:
                printf("Programa encerrado ;)");
                break;
       }
       //printf("\nDeseja continuar?");
        
    }while(a!=0);

    return 0;
}