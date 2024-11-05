#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_ATAQUES 5
#define TAMANHO_MAXIMO_ENTRADA 20

typedef struct No {
    char ataque;
    struct No* proximo;
} No;

typedef struct {
    int vida;
    int estamina;
    int multiplicador;
    No* historico;
} Jogador;



void processarAltF4X(Jogador* jogador1, const char* comando) {
    int novaEstamina = atoi(comando); // Converte o comando para um número inteiro
    if (novaEstamina > 0) {
        jogador1->estamina += novaEstamina;
    } 
}

void processarNoodModeX(Jogador* jogador2, const char* comando) {
    int novaVIDA = atoi(comando); // Converte o comando para um número inteiro
    if (novaVIDA > 0) {
        jogador2->estamina += novaVIDA;
    } 
}



int tamanhoHistorico(No* historico) {
    int tamanho = 0;
    No* atual = historico;
    while (atual != NULL) {
        tamanho++;
        atual = atual->proximo;
    }
    return tamanho;
}



void adicionarAtaque(Jogador* jogador, char ataque) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro alocar memoria.\n");
        return;
    }
    novoNo->ataque = ataque;
    novoNo->proximo = NULL;

    if (jogador->historico == NULL) {
        jogador->historico = novoNo;
    } else {
        No* atual = jogador->historico;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }
}

void liberarHistorico(Jogador* jogador) {
    No* atual = jogador->historico;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    jogador->historico = NULL;
}

void reiniciarJogo(Jogador* jogador1, Jogador* jogador2) {
    jogador1->multiplicador = 1;
    jogador1->vida = 837;
    jogador1->estamina = 1091;
    liberarHistorico(jogador1);
    jogador1->historico = NULL;

    jogador2->multiplicador = 1;
    jogador2->vida = 837;
    jogador2->estamina = 1091;
    liberarHistorico(jogador2);
    jogador2->historico = NULL;

    char inicial[] = "ZPAETRCBOM";
    for (int i = 0; i < strlen(inicial); i++) {
        adicionarAtaque(jogador1, inicial[i]);
    }
}

void exibirHistorico(Jogador* jogador) {
    int tamanho = tamanhoHistorico(jogador->historico);
    No* atual = jogador->historico;

    for (int i = 0; i < tamanho - 17; i++) {
        if (atual != NULL) {
            atual = atual->proximo;
        }
    }

    printf("H: ");
    while (atual != NULL) {
        printf("%c", atual->ataque);
        atual = atual->proximo;
    }
    printf("\n");
}

void inicializarJogo(Jogador* jogador1, Jogador* jogador2) {
    jogador1->multiplicador = 1;
    jogador1->vida = 837;
    jogador1->estamina = 1091;
    jogador1->historico = NULL;

    jogador2->multiplicador = 1;
    jogador2->vida = 837;
    jogador2->estamina = 1091;
    jogador2->historico = NULL;


    char inicial[] = "ZPAETRCBOM";
    for (int i = 0; i < strlen(inicial); i++) {
        adicionarAtaque(jogador1, inicial[i]);
    }
}

void ver_limites_vida_e_estamina(Jogador *jogador1, Jogador *jogador2) {
  if (jogador1->vida > 999) {
    jogador1->vida = 999;
  } else if (jogador1->vida < 0) {
    jogador1->vida = 0;
  }

  if (jogador1->estamina > 1103) {
    jogador1->estamina = 1103;
  } else if (jogador1->estamina < 0) {
    jogador1->estamina = 0;
  }

  if (jogador2->vida > 999) {
    jogador2->vida = 999;
  } else if (jogador2->vida < 0) {
    jogador2->vida = 0;
  }

  if (jogador2->estamina > 1103) {
    jogador2->estamina = 1103;
  } else if (jogador2->estamina < 0) {
    jogador2->estamina = 0;
  }
}



void rodadaDeJogo(Jogador *jogador1, Jogador *jogador2, char *ataques) {
    char resultado[100] = ""; // Declarar e inicializar a variável resultado
    if (strlen(ataques) == 6 && strncmp(ataques, "DADBAD", 6) == 0 && jogador1->estamina > 750) {
        jogador1->estamina -= 400;
        jogador2->vida -= 400;
    } else if (strlen(ataques) == 7 && strncmp(ataques, "ARROZAO", 7) == 0 && jogador1->estamina > 750) {
        jogador2->vida -= 500;
        jogador1->estamina -= 500;
    } else if (strlen(ataques) == 8 && strncmp(ataques, "STTEACC", 8) == 0 && jogador1->estamina > 750) {
        jogador2->vida -= 300;
        jogador1->estamina -= 300;
    } else if (strlen(ataques) == 9 && strncmp(ataques, "TATAPAAA", 9) == 0 && jogador1->estamina > 750) {
        jogador2->vida -= 200;
        jogador1->estamina -= 200;
    } else {
        printf("Estamina Insuficiente\n");
    }

    ver_limites_vida_e_estamina(jogador1, jogador2);
}




bool verificarFimDeJogo(Jogador *jogador1, Jogador *jogador2) {
  if (jogador1->vida <= 0 || jogador2->vida <= 0) {
    return true;
  }
  return false;
}

bool verifica_letras_ataque_corretas(char *input) {
    // Lista de combos específicos válidos
    const char* combos_validos[] = {"DADBAD", "ARROZAO", "STTEACC", "TATAPAAA"};

    // Verifica se o input é um combo válido
    for (int i = 0; i < sizeof(combos_validos) / sizeof(combos_validos[0]); i++) {
        if (strcmp(input, combos_validos[i]) == 0) {
            return true;
        }
    }

    // Verifica se o input é composto apenas por letras válidas
    for (int i = 0; input[i] != '\0'; i++) {
        if (strchr("ZPAETRCBOMDS", input[i]) == NULL) {
            return false;
        }
    }

    return true;
}


void exibir_Estado_jogador1(Jogador* jogador1) {
    printf("P#1 [%d|%d] (x%d)\n", jogador1->vida, jogador1->estamina, jogador1->multiplicador);
    exibirHistorico(jogador1);
    printf("I: ");
}



void exibir_Estado_jogador2(Jogador* jogador2) {
    printf("P#2 [%d|%d] (x%d)\n", jogador2->vida, jogador2->estamina, jogador2->multiplicador);
    exibirHistorico(jogador2); 
    printf("I: ");
}

void matriz_valores_ataques(int matriz[12][12]) {
  int temp[12][12] = {{0, 4, 8, 12, 16, -20, -16, 12, -8, -4, 0, 20},
                      {-4, 0, 4, 8, 12, 16, -20, -16, -12, 16, 0, 20},
                      {-8, -4, 0, 4, 8, 12, 16, -20, -16, 12, 0, 20},
                      {-12, -8, -4, 0, 4, -8, 12, 16, 20, -16, 0, 20},
                      {-16, -12, -8, -4, 0, 4, -8, 12, 16, 20, 0, 20},
                      {20, -16, -12, 8, -4, 0, 4, 8, 12, -16, 0, 20},
                      {16, 20, -16, -12, 8, -4, 0, -8, -4, -8, 0, 20},
                      {-12, 16, 20, -16, -12, -8, 8, 0, 16, -20, 0, 20},
                      {8, 12, 16, -20, -16, -12, 4, -16, 0, 20, 0, 20},
                      {4, -16, -12, 16, -20, 16, 8, 20, -20, 0, 0, 20},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {-20, -20, -20, -20, -20, -20, -20, -20, -20, -20, 0, 0}};

  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 12; j++) {
      matriz[i][j] = temp[i][j];
    }
  }
}

int calcula_multiplicador(int estamina) {
    if (estamina <= 750 && estamina > 500) {
        return 2;
    } else if (estamina <= 500 && estamina > 250 ) {
        return 3;
    } else if (estamina <= 250) {
        return 4;
    } else {
        return 1;
    }
}

void realizar_ataque_jogadores(Jogador *jogador1, Jogador *jogador2, char *input_jogador1, char *input_jogador2) {
    int valor_dano;
    int index_ataque1;
    int index_ataque2;
    int matriz[12][12];

    matriz_valores_ataques(matriz);

    // Verifica se a entrada é um combo especial
    bool combo_jogador1 = strlen(input_jogador1) > 1 && (strcmp(input_jogador1, "DADBAD") == 0 ||
                                                          strcmp(input_jogador1, "ARROZAO") == 0 ||
                                                          strcmp(input_jogador1, "STTEACC") == 0 ||
                                                          strcmp(input_jogador1, "TATAPAAA") == 0);

    bool combo_jogador2 = strlen(input_jogador2) > 1 && (strcmp(input_jogador2, "DADBAD") == 0 ||
                                                          strcmp(input_jogador2, "ARROZAO") == 0 ||
                                                          strcmp(input_jogador2, "STTEACC") == 0 ||
                                                          strcmp(input_jogador2, "TATAPAAA") == 0);

    if (combo_jogador1) {
        if (strcmp(input_jogador1, "DADBAD") == 0 && jogador1->estamina > 750) {
            jogador1->estamina -= 400;
            jogador2->vida -= 400;
        } else if (strcmp(input_jogador1, "ARROZAO") == 0 && jogador1->estamina > 750) {
            jogador2->vida -= 500;
            jogador1->estamina -= 500;
        } else if (strcmp(input_jogador1, "STTEACC") == 0 && jogador1->estamina > 750) {
            jogador2->vida -= 300;
            jogador1->estamina -= 300;
        } else if (strcmp(input_jogador1, "TATAPAAA") == 0 && jogador1->estamina > 750) {
            jogador2->vida -= 200;
            jogador1->estamina -= 200;
        }
        ver_limites_vida_e_estamina(jogador1, jogador2);
        return; // Pular o processamento de ataque regular
    }

    // Ataques regulares
    switch (input_jogador1[0]) {
        case 'Z': index_ataque1 = 0; break;
        case 'P': index_ataque1 = 1; break;
        case 'A': index_ataque1 = 2; break;
        case 'E': index_ataque1 = 3; break;
        case 'T': index_ataque1 = 4; break;
        case 'R': index_ataque1 = 5; break;
        case 'C': index_ataque1 = 6; break;
        case 'B': index_ataque1 = 7; break;
        case 'O': index_ataque1 = 8; break;
        case 'M': index_ataque1 = 9; break;
        case 'D': index_ataque1 = 10; break;
        case ' ': index_ataque1 = 11; break;
        default: index_ataque1 = -1;
    }

    switch (input_jogador2[0]) {
        case 'Z': index_ataque2 = 0; break;
        case 'P': index_ataque2 = 1; break;
        case 'A': index_ataque2 = 2; break;
        case 'E': index_ataque2 = 3; break;
        case 'T': index_ataque2 = 4; break;
        case 'R': index_ataque2 = 5; break;
        case 'C': index_ataque2 = 6; break;
        case 'B': index_ataque2 = 7; break;
        case 'O': index_ataque2 = 8; break;
        case 'M': index_ataque2 = 9; break;
        case 'D': index_ataque2 = 10; break;
        case ' ': index_ataque2 = 11; break;
        default: index_ataque2 = -1;
    }

    valor_dano = matriz[index_ataque1][index_ataque2];

    if (input_jogador1[0] == 'D') {
        jogador1->estamina += 7;
    } else if (input_jogador1[0] == ' ') {
        jogador1->estamina += 25;
    } else {
        jogador1->estamina -= 23;
    }

    if (input_jogador2[0] == 'D') {
        jogador2->estamina += 7;
    } else if (input_jogador2[0] == ' ') {
        jogador2->estamina += 25;
    } else {
        jogador2->estamina -= 23;
    }

    if (valor_dano > 0) {
        jogador2->vida -= valor_dano * jogador2->multiplicador;
    } else {
        jogador1->vida += valor_dano * jogador1->multiplicador;
    }

    if (input_jogador1[0] == 'D') {
        jogador1->vida += 13 * jogador1->multiplicador;
    }
    if (input_jogador2[0] == 'D') {
        jogador2->vida += 13 * jogador2->multiplicador;
    }

    adicionarAtaque(jogador2, input_jogador2[0]);

    ver_limites_vida_e_estamina(jogador1, jogador2);
}







void determina_vencedor(Jogador *jogador1, Jogador *jogador2) {
  if (jogador1->vida <= 0 && jogador2->vida <= 0) {
    printf("Empate!\n");
  } else if (jogador1->vida <= 0) {
    printf("Jogador 2 venceu o jogo!\n");
  } else {
    printf("Jogador 1 venceu o jogo!\n");
  }
}





void atualiza_multiplicador(Jogador *jogador1, Jogador *jogador2) {
  jogador1->multiplicador = calcula_multiplicador(jogador1->estamina);
  jogador2->multiplicador = calcula_multiplicador(jogador2->estamina);
}



void atualizar_historico(Jogador* jogador, char* ataques, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        adicionarAtaque(jogador, ataques[i]);
    }
}





int main(int argc, char* argv[]) {
    unsigned int seed;
    bool modoSilencioso = false; // Variável para verificar o modo silencioso

    // Verifica e atribui o seed
    if (argc > 1) {
        seed = atoi(argv[1]);
    } else {
        seed = 1;
    }

    // Verifica o modo (Silencioso ou Verboso) e o nome do arquivo
    if (argc > 2) {
        if (strcmp(argv[2], "S") == 0) {
            modoSilencioso = true;
        } else if (strcmp(argv[2], "V") == 0) {
            modoSilencioso = false;
        } else {
            printf("Modo inválido.\n");
            return 1;
        }
    }

    srand(seed);

    Jogador jogador1, jogador2;
    char ataque_jogador1[TAMANHO_MAXIMO_ENTRADA];
    char ataque_jogador2[MAX_ATAQUES + 1];
    char resultado[100] = "";

    inicializarJogo(&jogador1, &jogador2);

    while (!verificarFimDeJogo(&jogador1, &jogador2)) {
        if (!modoSilencioso) {
            exibir_Estado_jogador1(&jogador1);
        }
        scanf("%s", ataque_jogador1);

        if (strcmp(ataque_jogador1, "Modo-Jesus") == 0) {
            reiniciarJogo(&jogador1, &jogador2);
            continue; // Volta para o início do loop e não processa o restante
        }

        if (strncmp(ataque_jogador1, "Alt-F4", 6) == 0) {
            const char* parametro = ataque_jogador1 + 6; // Ignora "Alt-F4"
            if (*parametro == '\0') {
                if (!modoSilencioso) {
                    printf("Comando incompleto. Utilize Alt-F4X onde X é um número positivo.\n");
                }
            } else {
                processarAltF4X(&jogador1, parametro);
            }
            continue; // Volta para o início do loop e não processa o restante
        }

        if (!verifica_letras_ataque_corretas(ataque_jogador1) || 
            (strlen(ataque_jogador1) > 5 && !strstr("DADBAD ARROZAO STTEACC TATAPAAA", ataque_jogador1))) {
            if (!modoSilencioso) {
                printf("Entrada invalida\n");
            } else {
                printf("Entrada invalida\n");
            }
            return 0;
        }

        for (int i = 0; i < MAX_ATAQUES; i++) {
            int index = rand() % tamanhoHistorico(jogador1.historico);
            No* atual = jogador1.historico;
            for (int j = 0; j < index; j++) {
                atual = atual->proximo;
            }
            ataque_jogador2[i] = atual->ataque;
        }
        ataque_jogador2[MAX_ATAQUES] = '\0';


        if (!modoSilencioso) {
            exibir_Estado_jogador2(&jogador2);
            printf("%s ", ataque_jogador2);
        }

        resultado[0] = '\0';
        if (strlen(ataque_jogador1) > 1 && 
            (strcmp(ataque_jogador1, "DADBAD") == 0 || 
             strcmp(ataque_jogador1, "ARROZAO") == 0 || 
             strcmp(ataque_jogador1, "STTEACC") == 0 || 
             strcmp(ataque_jogador1, "TATAPAAA") == 0)) {
            realizar_ataque_jogadores(&jogador1, &jogador2, ataque_jogador1, " ");
            sprintf(resultado, "[%s, ]", ataque_jogador1);
        } else {
            for (int i = 0; i < MAX_ATAQUES; i++) {
                char attack1[2] = {i < strlen(ataque_jogador1) ? ataque_jogador1[i] : ' ', '\0'};
                char attack2[2] = {ataque_jogador2[i], '\0'};

                realizar_ataque_jogadores(&jogador1, &jogador2, attack1, attack2);

                char buffer[10];
                sprintf(buffer, "[%c,%c]", attack1[0], attack2[0]);
                strcat(resultado, buffer);
            }
        }

        if (!modoSilencioso) {
            printf("%s\n", resultado);
        }

        jogador1.multiplicador = calcula_multiplicador(jogador1.estamina);
        jogador2.multiplicador = calcula_multiplicador(jogador2.estamina);

        atualizar_historico(&jogador1, ataque_jogador1, strlen(ataque_jogador1));

        atualiza_multiplicador(&jogador1, &jogador2);
    }

    if (modoSilencioso) {
        if (jogador1.vida <= 0 && jogador2.vida <= 0) {
            printf("Empate!\n");
        } else if (jogador1.vida <= 0) {
            printf("Jogador 2 venceu o jogo!\n");
        } else {
            printf("Jogador 1 venceu o jogo!\n");
        }
    } else {
        determina_vencedor(&jogador1, &jogador2);
    }

    liberarHistorico(&jogador1);
    liberarHistorico(&jogador2);

    return 0;
}