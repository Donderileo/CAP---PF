#include <stdio.h>
#include <stdlib.h>
#include <locale.h> 
#define TAM 4

int main(){
    FILE *pc;
    int pos_barcos[3], pos_chute, certo=0, cond_vit[3], pos_acerto, i, j;
    char nome_arquivo_pc[64] = "";
    int id_jogo;
    int n=0, ka, k, x=1;

    
    printf("%s%c%c\n", "Content-Type:text/html;charset=UTF-8", 13, 10); //permitir ações no html
    printf("<!DOCTYPE html><html>" //começo do código em html
            "<head>"
                "<meta charset=\"utf-8\">" //define acentuação
                "<TITLE>Jogo bataha naval</TITLE>"
                "<link href=\"../batalha/vendor/bootstrap/css/bootstrap.min.css\" rel=\"stylesheet\">"
                "<link href=\"../batalha/vendor/font-awesome/css/font-awesome.min.css\" rel=\"stylesheet\" type=\"text/css\">" //chamada das fontes
                "<link href=\"../vendor/font-awesome/css/font-awesome.min.css\" rel=\"stylesheet\" type=\"text/css\">"
                "<link href=\"https://fonts.googleapis.com/css?family=Lora:400,700,400italic,700italic\" rel=\"stylesheet\" type=\"text/css\">"
                "<link href='https://fonts.googleapis.com/css?family=Cabin:700' rel='stylesheet' type='text/css'>"
                "<link rel=\"icon\" href=\"https://img1.picmix.com/output/stamp/normal/3/4/5/4/664543_07f2f.png\">" //define o icone como um barquinho chamado direito do link da internet
                "<link href=\"../batalha/css/grayscale.min.css\" rel=\"stylesheet\">" //chamada do css
            "</head><body>"); //fechar a tag head e abrir tag body que permite alterações no corpo da estrutura
    
    char *data = getenv("QUERY_STRING");

                int linha,coluna;

				if (data == NULL)
								printf("<P>Erro! Erro na passagem dos dados \n");
				else
								sscanf(data,"id_jogo=%d&linha=%d&coluna=%d",&(id_jogo),&(linha),&(coluna));

    linha--;
    coluna--;
    pos_chute = linha*4+coluna; // chute do usuario

    // trecho que lê os arquivo dos barcos/situação do computador
    sprintf(nome_arquivo_pc,"jogos/pc_%d.txt",id_jogo);
    pc = fopen(nome_arquivo_pc,"rb");
    fread(pos_barcos,sizeof(int),3,pc);
    fread(cond_vit,sizeof(int),3,pc);

    for(i=0;i<3;i++) {
        if(pos_barcos[i] == pos_chute){
            certo = 1;
            cond_vit[i] = 1;
        }//e um barco do computador
    } // verifica se o chute dado pelo usuario é uma posição de um barco do computador

    
    if(certo)
	   printf("<center>"
            "<div class=\"container\">"
            "<br>"
            "<h3> Belo tiro!</h3>");
    else
        printf("<center>"
            "<div class=\"container\">"
            "<br>"
            "<h3> Apontar canhoes!</h3>");


    
    for (i = 0; i < TAM; i++) {
             printf("<div class=\"row\">");
        for (j = 0; j < TAM; j++) {
            if(i == linha && j == coluna) { // verifica o acerto / erro
                if(certo){
                    printf("<div class=\"col-md-3 text-center\"><img src='http://cap.dc.ufscar.br/~759378/batalha/img/barco.jpg'"
                        "width=\"200\" height=\"125\"></div>");
        
                    }
                else {
                   printf ("<div class=\"col-md-3 text-center\"><img src='http://cap.dc.ufscar.br/~759378/batalha/img/erro.png'"
                        "width=\"200\" height=\"125\"></div>");
                }
            } 

            else {
                ka = 0;
                for(k=0; k<3; k++) {
                    if(pos_barcos[k] == n && cond_vit[k]) { // coloca a imagem do barco afundando nas posições já descobertas com acertos
                        printf("<div class=\"col-md-3 text-center\"><img src='http://cap.dc.ufscar.br/~759378/batalha/img/barco.jpg'"
                           "width=\"200\" height=\"125\"></div>");
                        ka++;
                    }
                }
                if(ka == 0)
                    printf ("<div class=\"col-md-3 text-center\">" // preenche o resto com mar (não clicável)
                                "<img src=\"http://cap.dc.ufscar.br/~759378/batalha/img/mar.jpg\""
                                    "width=\"200\" height=\"125\">"
                            "</div>",
                            id_jogo, i+1, j+1); 
            }
            n++; // percorre posições reais
            printf("<br/>");
        }
        printf("</div><div><br/></div>");
    }

    

    fclose(pc);
    pc = fopen(nome_arquivo_pc,"wb");
    fwrite(pos_barcos,sizeof(int),3,pc); // reescreve o arquivo de posições/estados com as alterações
    fwrite(cond_vit,sizeof(int),3,pc);
    fclose(pc);
    printf("</div></body>");

    printf("<center><a href=\"jogada_pc.cgi?id_jogo=%d\"><input value=\"Vez do adversário!\" class=\"btn btn-default btn-lag\" style=\"border-radius:6px\"></input></a></center>",id_jogo);
    //botão que oscila o jogador.
	printf("<br>");

    //Esse bloco verifica se o usuário venceu com essa jogada.
    for(i = 0; i < 3; i++){
        if(!cond_vit[i]) x = 0;
    }
    if(x){
        printf("async function demo() { await sleep(25000);}demo();"); //delay para não avançar para outra página muito rápido
        printf("<script>window.location.href=\"http://cap.dc.ufscar.br/~759378/batalha/win.html\";</script>"); //js para a partir da condição de vitória redirecionar para a página win.html
    }

    return 0;
}
