#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h> 
#define TAM 4

int main(){
    FILE *barcos_usr, *matriz_jogadas;
    int id_jogo;
    char nome_arquivo_usr[64] = "";
    int acertou = 1, cond_vit[3], pos_real_usr[3];
    int nao, alvo, i, j, k;

    srand(time(NULL));
    //nao comentei linhas iguais por já ter comentado no gerar_navios

    printf("%s%c%c\n", "Content-Type:text/html;charset=UTF-8", 13, 10);
    printf("<!DOCTYPE html><html>"
            "<head>"
                "<meta charset=\"utf-8\">"
                "<TITLE>Jogo batalha naval</TITLE>"
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
    barcos_usr = fopen(nome_arquivo_usr,"rb");

    fread(pos_real_usr,sizeof(int),3,barcos_usr);
    fread(cond_vit,sizeof(int),3,barcos_usr);

    do {
        nao = 0;

        alvo = rand() % 16;
	acertou = 0;
	for(k=0; k<3 && nao != 1; k++) {
	   if(pos_real_usr[k] == alvo) {
             if(cond_vit[k])
                nao = 1;
             else {
  	        cond_vit[k] = 1;
                acertou = 1;
             }
	   }
        }
    } while(nao); // bloco que cria o chute do pc e não o deixa repetir na mesma posição  

  printf("<div class=\"container text-center\">"
      
      "<h3> Vez do computador!</h3>");
   
	printf("<p>O pc atirou em: %d &nbsp&nbsp&nbsp Seus Barcos: %d, %d e %d</p>",alvo+1, pos_real_usr[0]+1, pos_real_usr[1]+1, pos_real_usr[2]+1);
    // leitura da jogada do computador para o usuario


    //esse bloco efetua o mesmo do realizar-jogada.c, verifica os acerto e preenche o mapa
    int n=0, ka;
    for (i = 0; i < TAM; i++) {
        printf("<div class=\"row\">");
        for (j = 0; j < TAM; j++) {
            if(n == alvo) {
                if(acertou) {
                    printf("<div class=\"col-md-3 text-center\"><img class=\"this-shot\" src='http://cap.dc.ufscar.br/~759378/batalha/img/barco.jpg'"
                        "width=\"200\" height=\"125\" /></div>");

                } else {
                    printf ("<div class=\"col-md-3 text-center\"><img src='http://cap.dc.ufscar.br/~759378/batalha/img/erro.png'"
                        "width=\"200\" height=\"125\" /></div>");
                }
            } else {
                ka = 0;
                for(k=0; k<3; k++) {
                    if(pos_real_usr[k] == n && cond_vit[k]) {
                        printf("<div class=\"col-md-3 text-center\"><img class=\"older-shot\" src='http://cap.dc.ufscar.br/~759378/batalha/img/barco.jpg'"
                           "width=\"200\" height=\"125\" /></div>");
                        ka++;
                    }
                }
                if(ka == 0)
                    printf ("<div class=\"col-md-3 text-center\">"
                                "<img src=\"http://cap.dc.ufscar.br/~759378/batalha/img/mar.jpg\""
                                    "width=\"200\" height=\"125\" />"
                            "</div>");
            }
            n++;
        }
        printf("</div><br/>");
    }




    fclose(barcos_usr);
    barcos_usr = fopen(nome_arquivo_usr,"wb");
    fwrite(pos_real_usr,sizeof(int),3,barcos_usr); // reescreve o arquivo de posições/estados com as alterações
    fwrite(cond_vit,sizeof(int),3,barcos_usr);
    fclose(barcos_usr);
    printf("</div>");


    int x = 1;
    for(i = 0; i < 3; i++){
        if(!cond_vit[i]) x = 0; // verifica se o computador venceu.
    }
    if(x){
        printf("async function demo() { await sleep(25000);}demo();"); //delay para não avançar para outra página muito rápido
        printf("<script>window.location.href=\"http://cap.dc.ufscar.br/~759378/batalha/lose.html\";</script>"); //js para a partir da condição de vitória redirecionar para a página lose.html
    }

    printf("<center><a href=\"jogada.cgi?id_jogo=%d\"><input value=\"Sua vez!\" class=\"btn btn-default btn-lag\" style=\"border-radius:6px\"></input></a></center>",id_jogo);
    //botão para oscilar o jogador.
	printf("<br>");
    printf("</body></html>");
    return 0;
}
