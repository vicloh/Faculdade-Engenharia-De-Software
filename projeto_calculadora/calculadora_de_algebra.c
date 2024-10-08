#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

#define MAX 4

// Função para limpar a tela de acordo com o sistema operacional
void limparTela() {
    #ifdef _WIN32
        system("cls"); // Comando para limpar no Windows
    #elif __linux__
        system("clear"); // Comando para limpar no Linux
    #else
        printf("\033[H\033[J"); // Alternativa usando escape sequences ANSI
    #endif
}

//Função para calcular o determinante de uma matriz quadrada
int determinante(int mat[MAX][MAX], int n) {
    int det = 0;

    //Caso para matriz 1x1
    if (n == 1) {
        return mat[0][0];
    }

    int temp[MAX][MAX];
    int sinal = 1;

    // Calcula  o determinante
    for (int f = 0; f < n; f++) {
        int aux1 = 0;
        for (int i = 1; i < n; i++) {
            int aux2 = 0;
            for (int j = 0; j < n; j++) {
                if (j == f) {
                    continue;
                }
                temp[aux1][aux2] = mat[i][j];
                aux2++;
            }
            aux1++;
        }
        det += sinal * mat[0][f] * determinante(temp, n - 1);
        sinal = -sinal; // Alterna o sinal entre positivo e negativo
    }

    return det;
}

// Função para resolver sistema 2x2
void resolve_sistema_2x2(float a[MAX][MAX]) {
    int i, j;
    float fator, x[2];

    printf("\n--- Resolução de Sistema 2x2 ---\n");

    // Eliminação
    fator = a[1][0] / a[0][0];
    for (j = 0; j < 3; j++) {
        a[1][j] = a[1][j] - fator * a[0][j];
    }

    //Metodo de verificação de SPI ou SI com base no resultado da eliminação
    if (a[1][1] == 0){
        if (a[1][2] == 0){
            printf("O sistema é Possível e Indeterminado (SPI).\n");
            return;
        } 
        else{
            printf("O sistema é Impossível (SI).\n");
            return;
        }
    }

    // Resolução de y
    x[1] = a[1][2] / a[1][1];

    // Resolução de x
    x[0] = (a[0][2] - a[0][1] * x[1]) / a[0][0];

    printf("Soluções:\n");
    printf("x = %.2f\n", x[0]);
    printf("y = %.2f\n", x[1]);
}

// Função para resolver sistema 3x3
void resolve_sistema_3x3(float a[MAX][MAX]) {
    int i, j, k;
    float fator, x[3];

    printf("\n--- Resolução de Sistema 3x3 ---\n");

    // Eliminação
    for (i = 0; i < 2; i++) {
        for (k = i + 1; k < 3; k++) {
            fator = a[k][i] / a[i][i];
            for (j = 0; j < 4; j++) {
                a[k][j] = a[k][j] - fator * a[i][j];
            }
        }
    }

    //Metodo de verificação de SPI ou SI com base no resultado da eliminação
    if (a[2][2] == 0){
        if (a[2][3] == 0){ 
            printf("O sistema é Possível e Indeterminado (SPI).\n");
            return;
        } 
        else{
            printf("O sistema é Impossível (SI).\n");
            return;
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

// Função principal para resolução de sistemas lineares
void solucaoSistemaLinear(){    
    int n;

    printf("Digite a dimensão da matriz: 2 para (2x3) ou 3 para(3x4):\n");
    
    scanf("%d", &n);

    if (n!=3&&n!=2)
    {
        printf("Dimensão da matriz inválida. Aceito somente matrizes 2x3 e 3x4.\n");
        return solucaoSistemaLinear();
    }

    float matriz[MAX][MAX];
    
    printf("Digite os valores da matriz com espaço entre eles:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n+1; j++) {
            scanf("%f", &matriz[i][j]);
        }
    }
    
    printf("\nMatriz original:\n");
    for(int i=0; i<n; i++){
        printf("\n");
        for(int j=0; j<=n; j++){
            printf("%.2f  ", matriz[i][j]);
        }
        printf("\n");
    }

    if (n==2)
    {
        resolve_sistema_2x2(matriz);
    }
    if (n==3)
    {
        resolve_sistema_3x3(matriz);
    }

}

// Função para verificar se a matriz é bijetiva

void verificarTransformacaoMatriz() {

    int mat[MAX][MAX];
    int linhas, colunas;

    printf("Digite o numeros de linhas da matriz: ");
    scanf("%d", &linhas);

    printf("Digite o numeros de colunas da matriz: ");
    scanf("%d", &colunas);

    printf("Digite os elementos da matriz %dx%d:\n", linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    if (linhas != colunas) {
        printf("A matriz não é quadrada, então não pode ser bijetiva.\n");

        if (linhas > colunas) {
            printf("A transformação pode ser sobrejetiva, mas não é injetiva.\n");
        }
        if (linhas < colunas) {
            printf("A transformação pode ser injetiva, mas não é sobrejetiva.\n");
        }
    } 

    if (linhas == colunas) {
        int det = determinante(mat, linhas);
        if (det != 0) {
            printf("A matriz é bijetiva (injetiva e sobrejetiva).\n");
        } 
        if (det == 0) {
            printf("A matriz não é bijetiva.\n");
            printf("A transformação não é injetiva.\n");
        }
    }
}

// Função para determinar se os vetores formam uma base
void determinacaoBase(){

    int dim, det;
    int matriz[MAX][MAX];
    int matrizTransposta[MAX][MAX];
    
    printf("Insira o valor 2 para bases em R^2 ou 3 para bases em R^3:\n");
    scanf("%d", &dim);

    if(dim != 2 && dim != 3){
        printf("Dimensão inválida! Aceito somente R^2 ou R^3.\n");
        return determinacaoBase(); 
    }

    for(int i=0; i<dim; i++){
        printf("Vetor %d: ", i+1);
        for(int j=0; j<dim; j++){
            scanf("%d", &matriz[i][j]);
        }
    }

    printf("\n");
    
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            matrizTransposta[j][i] = matriz[i][j];
        }
    }

    det = determinante(matriz, dim);

    if(det != 0){
        printf("Os vetores formam uma base em R^%d\n", dim);
    }

    if(det == 0){
        printf("Os vetores NÃO formam uma base em R^%d\n", dim);
    }
}

int main(){

    int a;

    do {
        printf("\nDigite o número da opção desejada: \n");
        printf("\n1- Resolução de Sistemas Lineares");
        printf("\n2- Verificação de Injetividade, Sobrejetividade e Bijetividad");
        printf("\n3- Determinação de Bases\n");
        printf("0- Encerra o programa\n");
        scanf("%d", &a);

        limparTela();//limpa tela

       switch(a){           
            case 1:
                solucaoSistemaLinear();
                break;
            case 2:
                verificarTransformacaoMatriz();
                break;
            case 3:
                determinacaoBase();
                break;
            case 0:
                printf("Programa encerrado ;)");
                break;
       }        
    } while(a!=0);

    return 0;
}