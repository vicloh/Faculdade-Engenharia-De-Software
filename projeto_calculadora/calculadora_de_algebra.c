#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>

#define MAX 4

int determinante(int mat[MAX][MAX], int n) {
    int det = 0;
    if (n == 1) {
        return mat[0][0];
    }

    int temp[MAX][MAX];
    int sinal = 1;

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
        sinal = -sinal;
    }

    return det;
}

void resolve_sistema_2x2(float a[MAX][MAX]) {
    int i, j;
    float fator, x[2];

    // Eliminação
    fator = a[1][0] / a[0][0];
    for (j = 0; j < 3; j++) {
        a[1][j] = a[1][j] - fator * a[0][j];
    }

    //Metodo de classificação com base no resultado da eliminação
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

void resolve_sistema_3x3(float a[MAX][MAX]) {
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

    //Metodo de classificação de sistema com base no resultado da eliminação
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


void solucaoSistemaLinear(){    
    int n;

    printf("Digite a dimensão da matriz(2x3 ou 3x4):\n");
    
    scanf("%d", &n);

    if (n!=3&&n!=2)
    {
        printf("Dimensão da matriz inválida. Aceito somente matrizes 2x3 e 3x4");
        return;
    }

    system("cls");

    float matriz[MAX][MAX];
    float matriz1[MAX][MAX];
    
    char equacao[100];
    char equacao1[100];
    int i = 0;
    int j = 0;
    for (int j = 0; j<n;j++) {
        printf("Digite a %d equação:\n",j+1);
        scanf(" %[^\n]", equacao);
        char *token1 = strtok(equacao, " xyz+=\n"); 
        while (token1 != NULL) {
            sscanf(token1, "%f",  &matriz[j][i]);
            i++;
            token1 = strtok(NULL, " xyz+=\n");
        }
        i=0;
    }
    
    
    printf("Aqui está os valores da matriz original:\n");
    for(int i=0; i<n; i++){
        printf("\n");
        for(int j=0; j<=n; j++){
            printf("%0.2f  ", matriz[i][j]);
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

void determinacaoBase(){

    int dim, det;
    int matriz[MAX][MAX];
    int matrizTransposta[MAX][MAX];
    
    printf("Insira o valor 2 para bases em R^2 ou 3 para bases em R^3:\n");
    scanf("%d", &dim);

    if(dim != 2 && dim != 3){
        printf("Só aceito os seguintes valores: 2 ou 3\n");
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

void calcularAutovalores(double a, double b, double c, double d, double *lambda1, double *lambda2) {
    double traco = a + d;
    double det = (a * d) - (b * c);

    double discriminante = traco * traco - 4 * det;

    if (discriminante < 0) {
        printf("A matriz não pode ser diagonalizada com autovalores reais.\n");
        return;
    }

    *lambda1 = (traco + sqrt(discriminante)) / 2; 
    *lambda2 = (traco - sqrt(discriminante)) / 2;
}

void calcularAutovetor(double a, double b, double c, double d, double lambda, double *x, double *y) {
    
   if (b != 0 || c != 0) {
        if (b != 0) {
            *x = -(a - lambda) / b;
            *y =1;
        } else if (c != 0) {
            *x = -(d - lambda) / c;
            *y = 1;
        }
    } else {
        if (a == lambda) {
            *x = 1;
            *y = 0;
        } else if (d == lambda) {
            *x = 0;
            *y = 1;
        }
    }
}


void calculoAutovaloresAutovetores() {
    double a, b, c, d;
    double lambda1, lambda2;
    double v1_x, v1_y, v2_x, v2_y;

    printf("Digite os elementos da matriz 2x2 (a, b, c, d): ");
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

    calcularAutovalores(a, b, c, d, &lambda1, &lambda2);
    printf("Autovalores: lambda1 = %.2f, lambda2 = %.2f\n", lambda1, lambda2);

    // Calcular autovetor lambda1
    calcularAutovetor(a, b, c, d, lambda1, &v1_x, &v1_y);
    printf("Autovetor correspondente a lambda1: v1 = (%.2f, %.2f)\n", v1_x, v1_y);

    // Calcular autovetor lambda2
    calcularAutovetor(a, b, c, d, lambda2, &v2_x, &v2_y);
    printf("Autovetor correspondente a lambda2: v2 = (%.2f, %.2f)\n", v2_x, v2_y);
}

void diagonalizacao(){
    double a, b, c, d;
    double lambda1, lambda2;
    double v1_x, v1_y, v2_x, v2_y;

    printf("Digite os elementos da matriz 2x2 (a, b, c, d): ");
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

    // Calcular diagonalização
    calcularAutovalores(a, b, c, d, &lambda1, &lambda2);
    printf("Autovalores: lambda1 = %.2f, lambda2 = %.2f\n", lambda1, lambda2);
    
    printf("Matriz diagonal D:\n");
    printf("[ %.2f, %.2f ]\n", lambda1, 0.0);
    printf("[ %.2f, %.2f ]\n", 0.0, lambda2);

    // Formar a matriz de mudança de base
    calcularAutovetor(a, b, c, d, lambda1, &v1_x, &v1_y);
    printf("Autovetor correspondente a lambda1: v1 = (%.2f, %.2f)\n", v1_x, v1_y);

    calcularAutovetor(a, b, c, d, lambda2, &v2_x, &v2_y);
    printf("Autovetor correspondente a lambda2: v2 = (%.2f, %.2f)\n", v2_x, v2_y);

    printf("Matriz de mudança de base P:\n");
    printf("[ %.2f, %.2f ]\n",v1_x,  v2_x);
    printf("[ %.2f, %.2f ]\n",v1_y,  v2_y);
}

int main(){

    int a;

    do {
        printf("\nDigite o número da opção desejada: ");
        printf("\n1- Resolução de Sistemas Lineares\n");
        printf("\n2- Verificação de Injetividade, Sobrejetividade e Bijetividade\n");
        printf("\n3- Determinação de Bases\n");
        printf("\n4- Cálculo de Autovalores e Autovetores de matrizes\n");
        printf("\n5- Diagonalização de Matrizes 2x2\n");
        printf("0- Encerra o programa\n");
        scanf("%d", &a);
        system("cls");

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
            case 4:
                calculoAutovaloresAutovetores();
                break;
            case 5:
                diagonalizacao();
                break;
            case 0:
                printf("Programa encerrado ;)");
                break;
       }
       //printf("\nDeseja continuar?");
        
    } while(a!=0);

    return 0;
}