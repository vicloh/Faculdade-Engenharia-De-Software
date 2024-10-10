#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"

#define MAX 4

/*=======================================
        Made by Victor's
 ========================================*/

// Funcao para limpar a tela de acordo com o sistema operacional
void limparTela() {
    #ifdef _WIN32
        system("cls"); // Comando para limpar no Windows
    #elif __linux__
        system("clear"); // Comando para limpar no Linux
    #else
        printf("\033[H\033[J"); // Alternativa usando escape sequences ANSI
    #endif
}

//Funcao para calcular o determinante de uma matriz quadrada
int determinante(int mat[MAX][MAX], int n) {
    int det = 0;

    //Caso para matriz 1x1
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
                temp[aux1][aux2] = mat[i][j];//Elimina linha e coluna onde f e j sao iguais
                aux2++;
            }
            aux1++;
        }
        det += sinal * mat[0][f] * determinante(temp, n - 1); // Calcula o determinante
        sinal = -sinal;
    }

    return det;
}

// Funcao para resolver sistema 2x2
void resolve_sistema_2x2(float a[MAX][MAX]) {
    int i, j;
    float fator, x[2];

    printf("\n--- Resolucao de Sistema 2x2 ---\n");

    // Eliminacao
    fator = a[1][0] / a[0][0];
    for (j = 0; j < 3; j++) {
        a[1][j] = a[1][j] - fator * a[0][j];
    }

    //Metodo de verificacao de SPI ou SI com base no resultado da eliminacao
    if (a[1][1] == 0){
        if (a[1][2] == 0){
            printf(GREEN"Sistema Possível Indeterminado (SPI).\n"RESET);
            return;
        } 
        else{
            printf(GREEN"Sistema Impossivel (SI).\n"RESET);
            return;
        }
    }

    // Resolucao de y
    x[1] = a[1][2] / a[1][1];

    // Resolucao de x
    x[0] = (a[0][2] - a[0][1] * x[1]) / a[0][0];

    printf("Solucao:\n");
    printf(GREEN "x = %.2f" RESET "\n", x[0]);
    printf(GREEN "y = %.2f" RESET "\n", x[1]);

}

// Funcao para resolver sistema 3x3
void resolve_sistema_3x3(float a[MAX][MAX]) {
    int i, j, k;
    float fator, x[3];

    printf("\n--- Resolucao de Sistema 3x3 ---\n");

    // Eliminacao
    for (i = 0; i < 2; i++) {
        for (k = i + 1; k < 3; k++) {
            fator = a[k][i] / a[i][i];
            for (j = 0; j < 4; j++) {
                a[k][j] = a[k][j] - fator * a[i][j];
            }
        }
    }

    //Metodo de verificacao de SPI ou SI com base no resultado da eliminacao
    if (a[2][2] == 0){
        if (a[2][3] == 0){ 
            printf(GREEN "O sistema e Possível e Indeterminado (SPI)." RESET "\n");
            return;
        } 
        else{
            printf(GREEN "O sistema e Impossível (SI)." RESET "\n");
            return;
        }
    }

    // Resolucao das variaveis
    x[2] = a[2][3] / a[2][2];
    x[1] = (a[1][3] - a[1][2] * x[2]) / a[1][1];
    x[0] = (a[0][3] - a[0][2] * x[2] - a[0][1] * x[1]) / a[0][0];

    printf("Solucao:\n");
    printf(GREEN "x = %.2f" RESET "\n", x[0]);
    printf(GREEN "y = %.2f" RESET "\n", x[1]);
    printf(GREEN "z = %.2f" RESET "\n", x[2]);

}

// Funcao principal para resolucao de sistema linear
void solucaoSistemaLinear(){    
    int n;
    desenharLinhadupla();
    centralizarTexto("Digite o numero de equacoes lineares do sistema:(2 ou 3):");
    desenharLinhadupla();

    scanf("%d", &n);
    limparTela();

    if (n!=3&&n!=2)//Condição de erro
    {
        printf(RED "--Dimensao do sistema invalido. Aceito somente sistemas 2x2 e 3x3."RESET "\n");
        return solucaoSistemaLinear();
    }

    float matriz[MAX][MAX];
    
    char equacao[100];
    int i = 0;
    for (int j = 0; j<n;j++) {//Armazena os valores da equação
        printf("Digite a %d equacao:\n",j+1);
        scanf(" %[^\n]", equacao);
        char *token1 = strtok(equacao, " xyz+=\n"); 
        while (token1 != NULL) { 
            sscanf(token1, "%f",  &matriz[j][i]);
            i++;
            token1 = strtok(NULL, " xyz+=\n");
        }
        i=0;
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

// Funcao para verificar se a matriz e bijetiva
void verificarTransformacaoMatriz() {

    int mat[MAX][MAX];
    int linhas, colunas;

    printf("Digite o numeros de linhas da matriz: ");
    scanf("%d", &linhas);

    printf("Digite o numeros de colunas da matriz: ");
    scanf("%d", &colunas);

    printf("\nDigite os elementos da matriz %dx%d:\n\n", linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("Digite o valor para a posição [%d][%d]: ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }

    printf("\n--Matriz original--\n");
    printf("-------------------------\n");
    for(int i=0; i<linhas; i++){
        printf("| ");
        for(int j=0; j<colunas; j++){
            printf("%d  ", mat[i][j]);
        }
        printf("|\n");
    }
    printf("-------------------------\n");

    //Verifica se a transformacao da matriz pode ser injetiva, sobrejetiva ou bijetiva
    if (linhas != colunas) {
        printf(GREEN"A matriz nao e quadrada, entao nao pode ser bijetiva.\n"RESET);

        if (linhas > colunas) {
            printf(GREEN"A transformacao pode ser sobrejetiva, mas nao e injetiva.\n"RESET);
        }
        if (linhas < colunas) {
            printf(GREEN"A transformacao pode ser injetiva, mas nao e sobrejetiva.\n"RESET);
        }
    } 

    //Verifica 
    if (linhas == colunas) {
        int det = determinante(mat, linhas);
        if (det != 0) {
            printf(GREEN"A matriz e bijetiva (injetiva e sobrejetiva).\n"RESET);
        } 
        if (det == 0) {
            printf(GREEN"A matriz nao e bijetiva.\n"RESET);
            printf(GREEN"A transformacao nao e injetiva.\n"RESET);
        }
    }
}

// Funcao para determinar se os vetores formam uma base
void determinacaoBase(){

    int dim, det;
    int matriz[MAX][MAX];
    int matrizTransposta[MAX][MAX];
    
    printf("Insira o valor 2 para bases em R^2 ou 3 para bases em R^3:\n");
    scanf("%d", &dim);

    if(dim != 2 && dim != 3){//Condição de erro
        printf(RED"Dimensao invalida! Aceito somente R^2 ou R^3."RESET"\n");
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

    det = determinante(matrizTransposta, dim);//calcula determinante da matriz gerada

    if(det != 0){
        printf(GREEN"Os vetores formam uma base em R^%d"RESET "\n", dim);
    }

    if(det == 0){
        printf(GREEN"Os vetores NAO formam uma base em R^%d"RESET "\n", dim);
    }
}
//função para calcular autovalor
void calcularAutovalores(double a, double b, double c, double d, double *lambda1, double *lambda2) {
    double traco = a + d;
    double det = (a * d) - (b * c);

    double discriminante = traco * traco - 4 * det;

    if (discriminante < 0) {
        printf(GREEN"A matriz nao pode ser diagonalizada com autovalores reais.\n"RESET);
        return;
    }
    //realiza a raiz quadrada
    *lambda1 = (traco + sqrt(discriminante)) / 2; 
    *lambda2 = (traco - sqrt(discriminante)) / 2;
}
//função para calcular autovetor
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
//função para inserir valores e chamar as funções de autovetor e autovalor para realizar matematica
void calculoAutovaloresAutovetores() {
    double a, b, c, d;
    double lambda1, lambda2;
    double v1_x, v1_y, v2_x, v2_y;

    printf("Digite os elementos da matriz 2x2 (a, b, c, d): \n");
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

    calcularAutovalores(a, b, c, d, &lambda1, &lambda2);
    printf("Autovalores:"GREEN" lambda1 = %.2f, lambda2 = %.2f"RESET"\n", lambda1, lambda2);

    // Calcular autovetor lambda1
    calcularAutovetor(a, b, c, d, lambda1, &v1_x, &v1_y);
    printf("Autovetor correspondente a lambda1:"GREEN" v1 = (%.2f, %.2f)"RESET"\n", v1_x, v1_y);

    // Calcular autovetor lambda2
    calcularAutovetor(a, b, c, d, lambda2, &v2_x, &v2_y);
    printf("Autovetor correspondente a lambda2: "GREEN"v2 = (%.2f, %.2f)"RESET"\n", v2_x, v2_y);
}

void diagonalizacao(){
    double a, b, c, d;
    double lambda1, lambda2;
    double v1_x, v1_y, v2_x, v2_y;

    printf("Digite os elementos da matriz 2x2 (a, b, c, d): \n");
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

    // Calcular diagonalizacao
    calcularAutovalores(a, b, c, d, &lambda1, &lambda2);
    printf("Autovalores: "GREEN"lambda1 = %.2f, lambda2 = %.2f"RESET"\n", lambda1, lambda2);
    
    printf("Matriz diagonal D:\n");
    printf(GREEN"[ %.2f, %.2f ]"RESET"\n", lambda1, 0.0);
    printf(GREEN"[ %.2f, %.2f ]"RESET"\n", 0.0, lambda2);

    // Formar a matriz de mudanca de base
    calcularAutovetor(a, b, c, d, lambda1, &v1_x, &v1_y);
    printf("Autovetor correspondente a lambda1: "GREEN"v1 = (%.2f, %.2f)"RESET"\n", v1_x, v1_y);

    calcularAutovetor(a, b, c, d, lambda2, &v2_x, &v2_y);
    printf("Autovetor correspondente a lambda2: "GREEN"v2 = (%.2f, %.2f)"RESET"\n", v2_x, v2_y);

    printf("Matriz de mudanca de base P:\n");
    printf(GREEN"[ %.2f, %.2f ]"RESET"\n",v1_x,  v2_x);
    printf(GREEN"[ %.2f, %.2f ]"RESET"\n",v1_y,  v2_y);
}
//a partir daqui, funções para personalisar textos
void centralizarTexto(const char* texto) {
    int len = strlen(texto);
    int espacos = (80 - len) / 2;
    for (int i = 0; i < espacos; i++) {
        printf(" ");
    }
    printf("%s\n", texto);
}

void desenharLinhadupla() {
    for (int i = 0; i < 80; i++) {
        printf("=");
    }
    printf("\n");
}
void desenharLinhasimples() {
    printf("    ");
    for (int i = 0; i < 50; i++) {
        printf("-");
    }
    printf("\n");
}

//executa algoritmo
int main(){

    int a;

    do {
        printf("\n");
        desenharLinhadupla();
        centralizarTexto("PABLONATOR");
        desenharLinhadupla();
        centralizarTexto("\n    1- Resolucao de Sistemas Lineares");
        desenharLinhasimples();
        centralizarTexto("\n    2- Verificacao de Injetividade, Sobrejetividade e Bijetividade");
        desenharLinhasimples();
        centralizarTexto("\n    3- Determinacao de Bases");
        desenharLinhasimples();
        centralizarTexto("\n    4- Calculo de Autovalores e Autovetores de matrizes");
        desenharLinhasimples();
        centralizarTexto("\n    5- Diagonalizacao de Matrizes 2x2");
        desenharLinhasimples();
        centralizarTexto("0- Encerra o programa\n");
        desenharLinhadupla();
        printf("\nDigite o numero da opcao desejada: ");
        scanf("%d", &a);
        limparTela();

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
                printf("Programa encerrado. Obrigado por usar a Pablonator =)");
                return 0;
            default:
                printf(RED"\nOpcao invalida. Digite uma das opcoes apresentadas no menu!\n\n"RESET);
                break;
       }

        do{
            desenharLinhadupla();
            centralizarTexto("Deseja encerrar o programa?");
            desenharLinhadupla();
            desenharLinhasimples();
            centralizarTexto("\n    0-Sim.");
            centralizarTexto("\n    1-Nao.");
            desenharLinhasimples();
            printf("\nDigite o numero da opcao desejada: ");
            scanf("%d", &a);
            limparTela();
            if(a!= 0 && a!=1){
                printf(RED"\nOpcao invalida!\n\n"RESET);
                
            }
        }while(a!=0 && a!=1);
        limparTela();
    } while(a!=0);
    printf("-- Programa encerrado. Obrigado por usar a Pablonator =) --");

    return 0;
}