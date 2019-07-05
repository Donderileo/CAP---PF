#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h> 

#define TAM 4
typedef struct {
    int linha;
    int coluna;
} pos;


int main(){

    FILE *pc, *usr;
    int id_jogo;
    char nome_arquivo_usr[64] = "", nome_arquivo_pc[64] = "";
    int pos_real_usr[3], pos_real_pc[3], cond_vit[3];
    int i, j, ka, k;

    printf("%s%c%c\n", "Content-Type:text/html;charset=UTF-8", 13, 10);
    printf("<!DOCTYPE html><html>"
            "<head>"
                "<meta charset=\"utf-8\">"
                "<TITLE>Jogo bataha naval</TITLE>"
                "<link href=\"../batalha/vendor/bootstrap/css/bootstrap.min.css\" rel=\"stylesheet\">"
                "<link href=\"../batalha/vendor/font-awesome/css/font-awesome.min.css\" rel=\"stylesheet\" type=\"text/css\">"
                "<link href=\"../vendor/font-awesome/css/font-awesome.min.css\" rel=\"stylesheet\" type=\"text/css\">"
                "<link href=\"https://fonts.googleapis.com/css?family=Lora:400,700,400italic,700italic\" rel=\"stylesheet\" type=\"text/css\">"
                "<link href='https://fonts.googleapis.com/css?family=Cabin:700' rel='stylesheet' type='text/css'>"
                "<link rel=\"icon\" href=\"https://img1.picmix.com/output/stamp/normal/3/4/5/4/664543_07f2f.png\">"
                "<link href=\"../batalha/css/grayscale.min.css\" rel=\"stylesheet\">"
            "</head><body>");

    char *data = getenv("QUERY_STRING");
    if (data == NULL)
        printf("<P>Erro! Erro na passagem dos dados \n");
    else
        sscanf(data,"id_jogo=%d",&id_jogo);

    sprintf(nome_arquivo_usr,"jogos/usr_%d.txt",id_jogo);
    sprintf(nome_arquivo_pc,"jogos/pc_%d.txt",id_jogo);
    //-------------------------------------------------------------------------------------------------------------------//
    usr = fopen(nome_arquivo_usr,"rb");
    pc = fopen(nome_arquivo_pc,"rb");

    fread(pos_real_usr,sizeof(int),3,usr); // Lê as posições dos barcos e a situação dos barcos do pc.
    fread(pos_real_pc,sizeof(int),3,pc);
    fread(cond_vit,sizeof(int),3,pc);

         printf("<center>"
      "<div class=\"container\">"
	  "<br>"
	  "<h3> Disparar!</h3>");
    int n=0;
		for (i = 0; i < TAM; i++) {           // linha
            printf("<div class=\"row\">");
            for (j = 0; j < TAM; j++) {       // coluna
                ka = 0;
                for(k=0; k<3; k++) {  // percorre as 3 posições reais dos barcos gerados pelo pc.
                    if(pos_real_pc[k] == n && cond_vit[k]) { // Verifica se está na posição do barco e se esse barco foi atingido (caso sim, printa o barco)
                        printf("<div class=\"col-md-3 text-center\"><img src='http://cap.dc.ufscar.br/~759378/batalha/img/barco.jpg'"
                        "width=\"200\" height=\"125\"></div>");
                        ka++;
                    }
                }
                if(ka == 0)
                    printf ("<div class=\"col-md-3 text-center\"><a href=\"realizar-jogada.cgi?id_jogo=%d&linha=%d&coluna=%d\"><img src='http://cap.dc.ufscar.br/~759378/batalha/img/mar.jpg'"
                        "width=\"200\" height=\"125\"></div>", id_jogo, i+1, j+1); // Caso não, printa o mar e permite o clique no mesmo.

                n++; // contador para percorrer as posições reais e não linha/coluna
            }
            printf("</div><div><br/></div>");
        }

    fclose(usr);
    fclose(pc);
    printf("</div></body>");

    return 0;

}
