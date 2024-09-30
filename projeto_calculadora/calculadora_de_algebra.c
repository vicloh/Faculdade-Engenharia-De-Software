/******************************************************************************
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

#define MAX_n 3

void resolucaoSistemaLinear(double matriz[MAX_n][MAX_n+1], int n){
    
    for(int i = 0; i < n; i++){
        int max_row = i;
        
        for(int k = i; k<n; k++){
            if(fabs(matriz[k][i]) > fabs(matriz[max_row][i])){
                max_row = k;
            }
        }

        for(int k = i; k <= n; k++){
            double aux = matriz[max_row][k];
            matriz[max_row][k] = matriz[i][k];
            matriz[i][k] = aux;
        }

        for(int k = i +1; k<n; k++){
            double fator = matriz[k][i] / matriz[i][i];
            for(int j = i; j<= n; j++){
                matriz[k][j] -= fator* matriz[i][j];
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        matriz[i][n] /= matriz[i][i];
        matriz[i][i] = 1;
        for (int j = i - 1; j >= 0; j--) {
            matriz[j][n] -= matriz[j][i] * matriz[i][n];
            matriz[j][i] = 0;
        }
    }
}

void printMatriz(double matriz[MAX_n][MAX_n+1], int n){

    printf("Aqui está os valores da matriz original:\n");
    for(int i=0; i<n; i++){
        printf("\n");
        for(int j=0; j<=n; j++){
            printf("%8.4f", matriz[i][j]);
        }
        printf("\n");
    }
}

void solucaoSistemaLinear(){    

    int n;

    printf("Digite a dimensão da matriz quadrada:\n");
    
    scanf("%d", &n);
    system("cls");
    double matriz[MAX_n][MAX_n+1];
    
    printf("Digite os valores da matriz com espaço entre eles:\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<=n; j++){
            scanf("%lf", &matriz[i][j]);
        }
    }
    
    printf("Aqui está sua matriz:\n");
    printMatriz(matriz, n);

    resolucaoSistemaLinear(matriz, n);

    printf("Aqui está a resolucao da matriz na forma escalonada reduzida:\n");
    printMatriz(matriz, n);

    printf("Solucao do sistema:\n");
    
}
 
int main(){

                                                
    int a;

    do {
        printf("Digite o número da opção desejada: ");
        printf("\n1- Resolução de Sistemas Lineares\n");
        printf("0- Encerra o programa\n");
        scanf("%d", &a);
        system("cls");

       switch(a){           
            case 1:
                solucaoSistemaLinear();
                break;
            case 0:
                printf("Programa encerrado ;)");
                break;
       }
       //printf("\nDeseja continuar?");
        
    } while(a!=0);

    return 0;
}