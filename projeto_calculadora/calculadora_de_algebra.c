#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

#define MAX_n 3

void resolve_sistema_2x2(float a[2][3]) {
    int i, j;
    float fator, x[2];

    // Eliminação
    fator = a[1][0] / a[0][0];
    for (j = 0; j < 3; j++) {
        a[1][j] = a[1][j] - fator * a[0][j];
    }

    // Resolução de y
    x[1] = a[1][2] / a[1][1];

    // Resolução de x
    x[0] = (a[0][2] - a[0][1] * x[1]) / a[0][0];

    printf("Soluções:\n");
    printf("x = %.2f\n", x[0]);
    printf("y = %.2f\n", x[1]);
}

void resolve_sistema_3x3(float a[3][4]) {
    int i, j, k;
    float fator, x[3];

    // Eliminação
    for (i = 0; i < 2; i++) {
        for (k = i + 1; k < 3; k++) {
            fator = a[k][i] / a[i][i];
            for (j = 0; j < 4; j++) {
                a[k][j] = a[k][j] - fator * a[i][j];
            }
        }
    }

    // Resolução das variáveis
    x[2] = a[2][3] / a[2][2];
    x[1] = (a[1][3] - a[1][2] * x[2]) / a[1][1];
    x[0] = (a[0][3] - a[0][2] * x[2] - a[0][1] * x[1]) / a[0][0];

    printf("Soluções:\n");
    printf("x = %.2f\n", x[0]);
    printf("y = %.2f\n", x[1]);
    printf("z = %.2f\n", x[2]);
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

    printf("Digite a dimensão da matriz(2x3 ou 3x4):\n");
    
    scanf("%d", &n);
    system("cls");
    float matriz[n][n+1];
    
    printf("Digite os valores da matriz com espaço entre eles:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n+1; j++) {
            scanf("%f", &matriz[i][j]);
        }
    }
    
    printf("Aqui está sua matriz:\n");
    printMatriz(matriz, n);

    if (n==2)
    {
        resolve_sistema_2x2(matriz)
    }
    if (n==3)
    {
        resolve_sistema_3x3(matriz)
    }
    if (n!=3&&n!=2)
    {
        printf("Dimensão da matriz inválida. Aceito somente matrizes 2x3 e 3x4");
        break;
    }


    
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