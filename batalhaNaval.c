#include <stdio.h>

#define LINHAS 10
#define COLUNAS 10
#define TAMANHO_BARCO 3
// Definindo a linha e a coluna onde ficará o barco horizontal
// Essas informações podem ser alteradas.
#define LINHA_BARCO_HORIZONTAL 0
#define COLUNA_BARCO_HORIZONTAL 3

// Definindo a linha e a coluna onde ficará o barco vertical
// Essas informações podem ser alteradas.
#define LINHA_BARCO_VERTICAL 7
#define COLUNA_BARCO_VERTICAL 4

// Definindo a linha e a coluna onde ficará o barco diagonal principal DECRESCENTE
// Essas informações podem ser alteradas.
#define LINHA_BARCO_DIAGONAL_1 2
#define COLUNA_BARCO_DIAGONAL_1 2

// Definindo a linha e a coluna onde ficará o barco diagonal secundário CRESCENTE
// Essas informações podem ser alteradas.
#define LINHA_BARCO_DIAGONAL_2 1
#define COLUNA_BARCO_DIAGONAL_2 8

// Definindo o triângulo
#define LINHA_TRIANGULO 2
#define COLUNA_TRIANGULO 7
#define ALTURA_TRIANGULO 3  // Quantidade de linhas do triângulo

// Definindo a cruz
#define LINHA_CRUZ 7
#define COLUNA_CRUZ 6
#define TAMANHO_CRUZ 2

// Definindo o octaedro
#define LINHA_OCTAEDRO 1
#define COLUNA_OCTAEDRO 5
#define TAMANHO_OCTAEDRO 1

int main(){
    // Iniciando a variável tabuleiro
    int barcodanificado;
    int tabuleiro [LINHAS][COLUNAS];

    // Iniciando a variável linha
    char linha[LINHAS]= {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I','J'};

    // Utilizando o for para printar a variável linha
    for (int i = 0; i < 10; i++){
        printf(" %c", linha[i]);
    }

    // Quebrando a linha com \n
    printf("\n");

    // Fazendo o tabuleiro inteiro ter valor de 0
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++){
            tabuleiro[i][j] = 0;
        }
    }

    // FOR do Barco HORIZONTAL
    for (int i = LINHA_BARCO_HORIZONTAL; i < LINHA_BARCO_HORIZONTAL + 1; i++){
        for (int j = COLUNA_BARCO_HORIZONTAL; j < COLUNA_BARCO_HORIZONTAL + TAMANHO_BARCO; j++){
            tabuleiro[i][j] = TAMANHO_BARCO;
        }
    }

    // FOR do Barco VERTICAL
    for (int j = COLUNA_BARCO_VERTICAL; j < COLUNA_BARCO_VERTICAL + 1; j++){
        for (int i = LINHA_BARCO_VERTICAL; i < LINHA_BARCO_VERTICAL + TAMANHO_BARCO; i++){
            tabuleiro[i][j] = TAMANHO_BARCO;
        }
    }

    // FOR do Barco diagonal primário

    for (int i = LINHA_BARCO_DIAGONAL_1; i < LINHA_BARCO_DIAGONAL_1 + TAMANHO_BARCO; i++){
        for (int j = COLUNA_BARCO_DIAGONAL_1; j < COLUNA_BARCO_DIAGONAL_1 + TAMANHO_BARCO; j++){
            if(i == j){
                tabuleiro[i][j] = TAMANHO_BARCO;
            }
        }
    }

    // FOR do barco diagonal secundária
    for (int i = LINHA_BARCO_DIAGONAL_2; i < LINHA_BARCO_DIAGONAL_2 + TAMANHO_BARCO; i++){
        for (int j = COLUNA_BARCO_DIAGONAL_2 - TAMANHO_BARCO; j <= COLUNA_BARCO_DIAGONAL_2; j++){
            if (i + j == 9){
                tabuleiro[i][j] = TAMANHO_BARCO;
            }
        }
    }
    

    // Definindo o ataque do triângulo
    for (int i = 0; i < ALTURA_TRIANGULO; i++) { // Altura do triângulo
        int inicio = COLUNA_TRIANGULO - i;  // Define a posição inicial da linha
        int fim = COLUNA_TRIANGULO + i;     // Define a posição final da linha

        for (int j = inicio; j <= fim; j++) {
            barcodanificado = tabuleiro[LINHA_TRIANGULO + i][j] == 3 ? 1 : 0;
            // Verificando se algum barco foi danificado

            tabuleiro[LINHA_TRIANGULO + i][j] = 1; 
            // Conforme o acréscimo do "i" o triângulo irá descendo.
            // O inicio e o fim foi criado para definir que quando mais embaixo tiver o triângulo
            // Mais casas ele terá atrás e encima. Por isso o "J" seria o início. que sempre terá
            // que ser menor que o seu fim.
            if(barcodanificado){
                // Se o barco for danificado será retornado o valor 4
                tabuleiro[LINHA_TRIANGULO + i][j] = 4;
            }
        }
    }

    // Definindo o ataque da cruz

    for (int i = -TAMANHO_CRUZ; i <= TAMANHO_CRUZ; i++) {
        // Observando se há algum barco que será obstruído
        barcodanificado = tabuleiro[LINHA_CRUZ][COLUNA_CRUZ + i] == 3 ? 1 : 0;

        // Linha horizontal da cruz
        tabuleiro[LINHA_CRUZ][COLUNA_CRUZ + i] = 2;
        
        // Linha vertical da cruz
        tabuleiro[LINHA_CRUZ + i][COLUNA_CRUZ] = 2;

        if(barcodanificado){ // Se tiver algum barco, o valor será definido para 4
            tabuleiro[LINHA_CRUZ][COLUNA_CRUZ + i] = 4;        
        }
    }


    // Construção do octaedro
    for (int i = -TAMANHO_OCTAEDRO; i <= TAMANHO_OCTAEDRO; i++) {
        int largura = TAMANHO_OCTAEDRO - (i < 0 ? -i : i);  // Controla a largura do diamante
        // Se o tamanho do octaedro for menor que zero, ele irá retornar um número negativo
        // Para calcular a largura, é subtraído o tamanho do octaedro pelo número

        for (int j = -largura; j <= largura; j++) {
            // Verificando se o barco foi danificado
            barcodanificado = tabuleiro[LINHA_OCTAEDRO + i][COLUNA_OCTAEDRO + j] == 3 ? 1 : 0;


            tabuleiro[LINHA_OCTAEDRO + i][COLUNA_OCTAEDRO + j] = 6;

            // Se tiver sido, ele irá retornar 4
            if(barcodanificado){
                tabuleiro[LINHA_OCTAEDRO + i][COLUNA_OCTAEDRO + j] = 4;
            }
        }
    }



    // Dando o print
    for (int i = 0; i < LINHAS; i++){

        // Print que mostra a linha, por exemplo "linha 9"
        printf("%d ", i);

        for (int j = 0; j < COLUNAS; j++){
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    
    return 0;
}