#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 4
typedef struct {
				int linha;
				int coluna;
} pos;


int main(){
    
    FILE *pc, *usr;
    int id_jogo = time(NULL);
    char nome_arquivo_usr[64] = "", nome_arquivo_pc[64] = ""; // Arquivos para evitar conflito com multiplos jogadores
    int pos_real[3] = {-1}; // variavel para conversão de uma matriz 4x4 em posições 1-16
    int destruidos[3] = {0}; // principio com todos os barcos inteiros
    int i;
    pos navios_usr[3]; // linha/col que o usuario insere no inicio.html

    srand(time(NULL));

    printf("%s%c%c\n", "Content-Type:text/html;charset=UTF-8", 13, 10); //permitir ações no html
				printf("<!DOCTYPE html><html>" //tag para começar a codifição em html
								"<head>"
												"<meta charset=\"utf-8\">"
												"<TITLE>Jogo bataha naval</TITLE>" // titulo da página inserido por html
												"<link href=\"../batalha/vendor/bootstrap/css/bootstrap.min.css\" rel=\"stylesheet\">" //chamada do bootstrap
								"</head><body>");


    sprintf(nome_arquivo_usr,"jogos/usr_%d.txt",id_jogo); // recebe o nome do arquivo, dado que o mesmo foi gerado pelo tempo
    sprintf(nome_arquivo_pc,"jogos/pc_%d.txt",id_jogo);
    //-------------------------------------------------------------------------------------------------------------------//
    usr = fopen(nome_arquivo_usr,"wb");     // abre os arquivos para escrita das posições dos barcos
    pc = fopen(nome_arquivo_pc,"wb");
   
    char *data = getenv("QUERY_STRING"); //recebe os dados do html e armazena na variavel data
				
				if (data == NULL) //se a variavel Estiver vazia, não aconteceu a passagem de dados
								printf("<P>Erro! Erro na passagem dos dados \n");
				else
								sscanf(data,
                                    "linha1=%d&coluna1=%d&linha2=%d&coluna2=%d&linha3=%d&coluna3=%d", // recebe os dados do inicio.html
                                    &(navios_usr[0].linha), &(navios_usr[0].coluna),
                                    &(navios_usr[1].linha), &(navios_usr[1].coluna),
                                    &(navios_usr[2].linha), &(navios_usr[2].coluna));

    for(i=0;i<3;i++){
        navios_usr[i].linha--; // transforma a contagem de 1-4 para 0-3.
        navios_usr[i].coluna--;
        pos_real[i] = navios_usr[i].linha*TAM + navios_usr[i].coluna; // converte para posições reais 0-15
    }
    
    fwrite(pos_real,3,sizeof(int),usr); // escreve em um arquivo os 2 vetores com as posições e situação dos barcos - USR
    fwrite(destruidos,3,sizeof(int),usr);
    
    for(i=0;i<3;i++){
        do{
            pos_real[i] = rand()%16; // randomiza as posições 
       }while(pos_real[0] == pos_real[1] || pos_real[1] == pos_real[2] || pos_real[0] == pos_real[2]);
    }

    fwrite(pos_real,3,sizeof(int),pc); // escreve em um arquivo os 2 vetores com as posições e situação dos barcos - USR
    fwrite(destruidos,3,sizeof(int),pc);
    
    fclose(usr);
    fclose(pc);
    
    printf("<script>window.location.href=\"jogada.cgi?id_jogo=%d\";</script></body>",id_jogo); // Chama o arquivo .cgi que começa o jogo

    return 0;

}