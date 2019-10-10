#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int x, i, j;

#define clear() printf("\033[H\033[J");

int* criarTorre(int n){ // cria as tres torres em um array de 60 posições
    int i, c = 20 - n;
    static int torre[60];

    for (i = 59; i >= 0; i--){ // coloca 0s nas 60 posições
      if(i < 20 && i >=c){
        torre[i] = n;
        n--;
      }else{
        torre[i] = 0;
      }
    }

    return torre;
}

void apres(char k[], int n){
    if(strcmp(k, "\n")==0){
        for(int i = 0; i < n; i++) putchar(45);
        printf("\n");
        return;
    }
    apres("\n", 125);
    for(int i = 0; i < n; i++) putchar(45);
    printf("%s", k);
    apres("\n", n);
    apres("\n", 125);
}


void printTorre(int* t, int n){
    int grafica[23][125]; //matriz que contem as torres prontas
    int i, j, aux, anel, c;
    apres("\n", 125);
    printf("\n\n");//utilizado para separar as linhas de texto da ilustração da torre

    for (i = 0; i < 23; i++){ //inicia a matriz grafica "vazia"
        for (j = 0; j < 125; j++){
            if (j == 20 || j == 62 || j == 104){
                grafica[i][j] = 124;
            }else{
                grafica[i][j] = 32;
            }
        }
    }

    for (i = 0; i < 60; i++){ //posiciona os aneis nas posições corretas
      if(i < 20){
        c = 0;
      }else if(i<40){
        c = 1;
      }else{
        c = 2;
      }
      if(t[i] != 0){
          anel = t[i];
              for (; anel > 0; anel--){
                  grafica[i + 3 - c* 20][20+ c*42] = 35;
                  grafica[i + 3 - c* 20][20+ c*42 + anel] = 35; //i+3 pois a matriz grafica possui 23 linhas e a matriz representacao possui 20
                  grafica[i + 3 - c* 20][20+ c*42- anel] = 35;
              }
      }}

	for (i = 20 - n; i < 23; i++){ //imprime o resultado final
        for (j = 0; j < 125; j++){
            printf("%c", grafica[i][j]);
        }
        printf("\n");
	}
	printf("\n\n");
}


int verifTorreZerada(int* t, int o){
  if (t[o*20 - 1] != 0){ // se o último disco for não-nulo, então a torre é não-nula
      for(int i = (o-1)*20; i < o*20; i++){
        if(t[i] != 0){
          return t[i];
        }
      }
      return 0;
  }else{ // se não, então a torre é nula
      return 0;
  }
}


int verifTransf(int*t, int d, int p){
  int i;

  for (i = d * 20 - 1; i >= (d-1) * 20; i--){ // começando de baixo para cima na torre
      if (t[i - 1] == 0){ // se a próxima posição estiver vazia e...
          if (t[i] > p || t[i] == p || t[i] == 0){ // ... se o disco do topo for maior que o disco atual...
              return 1; // ... é possível transferir
          }
          else{
              return 0;
          }
      }
  }
}

int verifResposta(int* t, int n){ // checar se a torre atual é equivalente a torre da resposta
    int i;
    int c = 0;

    for (i = 59; i >= 40; i--){ // coloca os valores de 1 a n, a partir da posição k
      if(n > 0){
        if(t[i]==n){
        n--;
        c++;
        }
      }else if(t[i]==0){
          c++;
        }
    }

    if (c == 20){ // se, para as 20 posições do array 3, tivermos 20 elementos iguais ao vetor resposta, então o jogador vence
        return 1;
    }
    else{
        return 0; // caso contrário, continua jogando
    }
}

void move(int ori, int des, int* t, int m){ // movendo o disco do topo da torre de origem para o topo da torre de destino
  int i, j;
  int transf;

  for (i = ori*20 -1; i >= (ori-1)*20; i--){
      if (t[i - 1] == 0){
          transf = t[i];
          t[i] = 0;
          break;
      }
  }
  for (j = des*20 -1; j >= (des-1)*20; j--){
      if (t[j] == 0){
          t[j] = transf;
          break;
      }
  }

    printTorre(t, m);
}

void auto_hanoi(int n, int m, int ori, int des, int aux, int* tor){ // função recursiva que resolve o problema
    if (n == 1){ // caso base, onde o disco 1 eh movido diretamente para a torre 3
        move(ori, des, tor, m);
        return;
    }
    auto_hanoi(n-1, m, ori, aux, des, tor); // passo recursivo que usa a torre auxiliar como destino e a de destino como auxiliar
    move(ori, des, tor, m); // move o ultimo disco da torre de origem para a de destino
    auto_hanoi(n-1, m, aux, des, ori, tor); // recursão que usa a auxiliar como origem, e a origem como auxiliar
}

int main(){
    

    while (1){
        apres("TORRES DE HANOI", 55);
        printf("\n");
        int x; // variável que guarda a quantidade de discos
        int ori, des; // variáveis de torres, ori: torre de origem; des: torre de destino; pec: peça a mexer
        int vtz; // variáveis verificadoras, vd: verifica disco na torre; vtz: verifica torres zeradas
        int vt, vr = 0; // variáveis verificadoras, vt: verifica possib. de transferencia; vr: verifica resposta
        int counter = 0; // contador de rodadas

        int menu;
        printf("1 - Jogar\n2 - Modo Automatico\n3 - Regras\n4 - Sair\n\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &menu);

        if(menu == 1 || menu == 2){
            Lerdisco: printf("Digite a quantidade de discos: ");
            scanf("%d", &x);
            if(x <= 0 || x > 20){
                printf("ALERTA: Limite de discos = 20\n\n");
                goto Lerdisco;
            }
        }
        int *torre = criarTorre(x); // ponteiro que guarda o array da torre

        switch(menu){
        case 1:
            
            printTorre(torre, x);

            while(vr == 0){ // enquanto a verificadora de resposta retornar 0, o jogador continua jogando
                counter++; // contador de rodadas
                printf("Rodada %d\n\n", counter);

                OriTorre: printf("Qual a torre de origem? "); // usuário informa a torre de origem
                scanf("%d", &ori);
                vtz = verifTorreZerada(torre, ori); // verificar se a torre possui discos
                if(ori < 1 || ori > 3 || vtz == 0){
                    printf("ALERTA: Escolha uma torre nao-nula: {1, 2, 3}\n");
                    goto OriTorre;
                }

                Des: printf("Qual a torre de destino? "); // usuário informa a torre de destino
                scanf("%d", &des);
                vt = verifTransf(torre, des, vtz); // verificar se o disco do topo da torre de destino é maior que o disco que se deseja transferir
                if(vt == 0 || des > 3 || des <= 0){
                    printf("Local de destino invalido\n");
                    goto Des;
                }

                move(ori, des, torre, x); // mover disco entre as torres de origem e destino

                vr = verifResposta(torre, x); // verificar a resposta
            }

            apres("PARABENS, VOCE GANHOU", 52);
            printf("Torres de hanoi com %d discos, completados em %d rodadas.\n", x, counter);
            getchar();
            getchar();
            clear();

            break;

        case 2:
            getchar();
            printTorre(torre, x);
            auto_hanoi(x, x, 1, 3, 2, torre);

            printf("Torres de hanoi com %d discos, completados em %.lf rodadas.\n", x, pow(2, x) - 1);
            
            
            getchar();
            clear();
            break;

        case 3:
            printf("\n\nA torre de Hanoi eh um jogo onde existem tres torres e n discos.\nO objetivo do jogo eh mover todos os discos da primeira para a\n"
            "ultima torre, utilizando a restante como torre auxiliar, seguindo as seguintes regras:\n"
            "   1. Apenas um disco pode ser movido de cada vez.\n"
            "   2. Cada movimento consiste de tirar o disco do topo\n"
            "      de uma das torres e posiciona-lo no topo de outra\n"
            "   3. Nenhum disco pode ser posicionado acima de um disco menor.\n\n");
            break;

        case 4:
            exit(1);
            break;
        }
    }

    return 0;
}
