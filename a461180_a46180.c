#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define N 150 // 150 para existir sempre um espaço em branco no final

char *questao[9] = {"Questão 1","Questão 2","Questão 3","Questão 4","Questão 5","Questão 6","Questão 7","Questão 8","Questão 9",};
char *dificuldade[3] = {"Fácil", "Médio", "Difícil"};
char *quantia[9] = {"100€", "300€", "500€", "2000€", "3500€", "5000€", "10000€", "15000€", "20000€"};

void limpaInput()
{
    while (getchar() != '\n');
}

// Abre o ficheiro
FILE *abreFicheiro(char *file, char *modo)
{
    FILE *f = fopen(file, modo);

    if (f == NULL)
    {
        fprintf(stderr, "Falhou abertura de %s.\n", file);
        exit(EXIT_FAILURE);
    }

    return f;
}

// Fecho do ficheiro
void fechaFicheiro(FILE *f, char *file)
{
    if (fclose(f) == EOF)
    {
        fprintf(stderr, "Falhou o fecho de %s.\n", file);
        exit(EXIT_FAILURE);
    }
}

// Estrutura simplificada que representa uma pergunta e as respetivas respostas
typedef struct
{
    char pergunta[256];
    char resposta1[256];
    char resposta2[256];
    char resposta3[256];
    char resposta4[256];

} PERGUNTA;

// Lê o array de perguntas de um ficheiro de texto
void leTXT(PERGUNTA *ps, char *file)
{
    FILE *f = abreFicheiro(file, "r");

    int i = 0;
    while (fscanf(f, "Pergunta: %[^#]#A: %[^#]#B: %[^#]#C: %[^#]#D: %[^\n]\n", ps[i].pergunta, ps[i].resposta1, ps[i].resposta2, ps[i].resposta3, ps[i].resposta4) == 5)
    {
        i++;
    }

    fechaFicheiro(f, file);
}

// Grava o array de perguntas num ficheiro de texto
void gravaTXT(PERGUNTA *ps, char *file)
{
    FILE *f = abreFicheiro(file, "w");

    for (int i = 0; i < N && strlen(ps[i].pergunta) > 0; i++)
    {
        fprintf(f, "Pergunta: %s#A: %s#B: %s#C: %s#D: %s\n", ps[i].pergunta, ps[i].resposta1, ps[i].resposta2, ps[i].resposta3, ps[i].resposta4);
    }

    fechaFicheiro(f, file);
}

// Lê o array de perguntas de um ficheiro binário
void leBin(PERGUNTA *ps, char *file)
{
    FILE *f = abreFicheiro(file, "rb");

    fread(ps, sizeof(PERGUNTA), N, f);

    fechaFicheiro(f, file);
}

// Grava o array de perguntas num ficheiro binário
void gravaBin(PERGUNTA *ps, char *file)
{
    FILE *f = abreFicheiro(file, "wb");

    fwrite(ps, sizeof(PERGUNTA), N, f);

    fechaFicheiro(f, file);
}

// Cria uma pergunta
// Recebe do utilizador a informação e devolve PERGUNTA
PERGUNTA criaPergunta()
{
    int per, res1, res2, res3, res4;
    char *pos;
    PERGUNTA p;
    printf("\t****************\n");
    printf("\t*****AVISO!*****\n");
    printf("\t****************\n");
    printf("Não se esqueça, a primeira resposta inserida deve ser a correta.\n\n");

    /* O do/while serve para obrigar o utilador a preencher cada dependência
    e evitar que a mesma fique em branco*/
    do
    {
        printf("Insira a sua Pergunta:\n");
        fgets(p.pergunta, 256, stdin);
        pos = strchr(p.pergunta, '\n');
        *pos = '\0';
        per = strlen(p.pergunta);
        if (per == 0)
        {
            printf("Pergunta vazia. Por favor, insira uma pergunta.\n");
        }
    } while (per == 0);

    do
    {
        printf("Insira a resposta CORRETA: ");
        fgets(p.resposta1, 256, stdin);
        pos = strchr(p.resposta1, '\n');
        *pos = '\0';
        res1 = strlen(p.resposta1);
        if (res1 == 0)
        {
            printf("Resposta vazia. Por favor, insira uma resposta.\n");
        }
    } while (res1 == 0);

    do
    {
        printf("Insira outra opção de resposta: ");
        fgets(p.resposta2, 256, stdin);
        pos = strchr(p.resposta2, '\n');
        *pos = '\0';
        res2 = strlen(p.resposta2);
        if (res2 == 0)
        {
            printf("Resposta vazia. Por favor, insira uma resposta.\n");
        }
    } while (res2 == 0);

    do
    {
        printf("Insira outra opção de resposta: ");
        fgets(p.resposta3, 256, stdin);
        pos = strchr(p.resposta3, '\n');
        *pos = '\0';
        res3 = strlen(p.resposta3);
        if (res3 == 0)
        {
            printf("Resposta vazia. Por favor, insira uma resposta.\n");
        }
    } while (res3 == 0);

    do
    {
        printf("Insira outra opção de resposta: ");
        fgets(p.resposta4, 256, stdin);
        pos = strchr(p.resposta4, '\n');
        *pos = '\0';
        res4 = strlen(p.resposta4);
        if (res4 == 0)
        {
            printf("Resposta vazia. Por favor, insira uma resposta.\n");
        }
    } while (res4 == 0);
    return p;
}

// Adiciona pergunta ao array de perguntas
void adicionaPergunta(PERGUNTA *ps)
{
    PERGUNTA p;
    int ret = -1;
    int nivel;
    int i = 0;
    char facil[] = "Que companhia produziu o filme 'Up! Altamente !'?";
    char media[] = "Qual era o nome do café na sitcom Friends?";
    char dificil[] = "Quantas teclas tem um piano clássico?";

    do
    {
        while (i < N && strlen(ps[i].pergunta) > 0)
        {
            i++;
        }
        //Estou na primeira posição vazia
        if (i == N)
        {
            printf("Array está cheio. Não é possível adicionar mais nenhuma pergunta.\n");
            break;
        }
        p = criaPergunta();
        do
        {
            printf("\nPertende adicionar esta pergunta a que nível de dificuldade?\n\n");
            printf("1. Fácil\n");
            printf("2. Médio\n");
            printf("3. Díficil\n\n");
            printf("---> ");
            if (scanf("%d", &nivel) != 1) //Para evitar aceitar letras
            {
                limpaInput();
            }
            switch (nivel)
            {
            case 1:
                do
                { // i vai ser igual à primeira posição vazia.
                    ps[i] = ps[i - 1];
                    i--;
                } while (i >= 0 && strcmp(ps[i].pergunta, facil) != 0); /* Vou andar todas as perguntas
                uma posição para a frente até encontrar a primeira pergunta facíl.*/
                i++;                                                    /* Vou andar uma casa para a frente e essa posição vai estar vazia, pois andei todas
                as "anteriores" uma para trás.*/
                ps[i] = p;                                              // Onde coloco a pergunta criada.
                break;
            case 2:
                do
                {
                    ps[i] = ps[i - 1];
                    i--;
                } while (i >= 0 && strcmp(ps[i].pergunta, media) != 0);
                i++;
                ps[i] = p;
                break;
            case 3:
                do
                { // i = 72
                    ps[i] = ps[i - 1];
                    i--;
                } while (i >= 0 && strcmp(ps[i].pergunta, dificil) != 0);
                i++;
                ps[i] = p;
                break;
            default:
                printf("Opção inválida! Por favor, insira um valor correto.\n\n");
                break;
            }
        } while (nivel != 1 && nivel != 2 && nivel != 3);

        printf("\nPrima 1 para adicionar uma nova pergunta ou qualquer outro número para sair.\n");
        while (scanf("%d", &ret) != 1)
        {
            limpaInput();
            printf("\nPrima 1 para adicionar uma nova pergunta ou qualquer outro número para sair.\n");
        }
    } while (ret == 1);
}

// Imprime no ecrã a informação de uma pergunta
void mostraPergunta(PERGUNTA p)
{
    printf("Pergunta: %s\n", p.pergunta);
    printf("A: %s\n", p.resposta1);
    printf("B: %s\n", p.resposta2);
    printf("C: %s\n", p.resposta3);
    printf("D: %s\n", p.resposta4);
}

// Imprime no ecrã a informação de todas as perguntas
void mostraArray(PERGUNTA *ps, int n)
{
    char quit = quit;
    int ch;

    for (int i = 0; i < n && strlen(ps[i].pergunta) > 0; i++)
    {
        mostraPergunta(ps[i]);
        printf("\n");

        // Mostra apenas 5 perguntas de cada vez
        if ((i + 1) % 5 == 0)
        {
            printf("Prima enter para ver as próximas perguntas.\n");
            printf("Digite quit ou apenas q, se o utilizador pretende interromper a visualização das questões.\n");
            ch = getchar();
            if ((ch == 'q') || (ch == quit))
            {
                break;
            }
        }
    }
}

// Transforma as strings em minúsculas
void minusculas(char *orig, char *final)
{
    int i;
    for (i = 0; orig[i] != '\0'; i++)
    {
        final[i] = tolower(orig[i]);
    }
    final[i] = '\0';
}

int listaQuestao(char *pnome, PERGUNTA *ps)
{
    int ret = 1;
    int i = 0;
    char minP[256], min[256], minR1[256], minR2[256], minR3[256], minR4[256];
    char quit = quit;
    int ch;
    int num = 0;

    while (i < N && strlen(ps[i].pergunta) > 0)
    {
        minusculas(ps[i].pergunta, minP);
        minusculas(pnome, min);
        minusculas(ps[i].resposta1, minR1);
        minusculas(ps[i].resposta2, minR2);
        minusculas(ps[i].resposta3, minR3);
        minusculas(ps[i].resposta4, minR4);
        // Verifico se a string se encontra em perguntas ou respostas
        if ((strstr(minP, min) != NULL) || (strstr(minR1, min) != NULL) || (strstr(minR2, min) != NULL) || (strstr(minR3, min) != NULL) || (strstr(minR4, min) != NULL))
        {
            ret = 0;
            mostraPergunta(ps[i]);
            printf("\n");
            num++; //Usado para fazer a contagem de leituras
            if (num % 5 == 0)
            {
                printf("Prima enter para ver as próximas perguntas.\n");
                printf("Digite quit ou apenas q, se o utilizador pretende interromper a visualização das questões.\n");
                ch = getchar();
                if ((ch == 'q') || (ch == quit))
                {
                    break;
                }
            }
        }
        i++;
    }
    return ret;
}

// É usado pela removeQuestaoprocess
int indicePergunta(char *pnome, PERGUNTA *ps)
{
    int i = 0;
    int res = -1;
    char min1[256], min2[256];

    while (i < N && strlen(ps[i].pergunta) > 0)
    {
        minusculas(ps[i].pergunta, min1);
        minusculas(pnome, min2);

        if (strcmp(min1, min2) == 0)
        {
            res = i;
            break;
        }
        i++;
    }
    return res;
}

int removeQuestaoprocess(char *pnome, PERGUNTA *ps)
{
    int ret = 0;

    int i = indicePergunta(pnome, ps);

    if (i >= 0)
    {
        /*Encontrada a pergunta. Move todas as posicoes à sua frente uma posição para trás.*/
        while (i < N - 1 && strlen(ps[i].pergunta) > 0)
        {
            ps[i] = ps[i + 1];
            i++;
        }
        PERGUNTA p = {}; //Coloca stuct "vazia"
        ps[i] = p;
    }
    else
    {
        ret = 1;
    }
    return ret;
}

// Remove perguntas do array de perguntas 'ps'
void removeQuestao(PERGUNTA *ps)
{
    int rem = 0, ind = 0;
    char pnome[256];
    char *pos;

    do
    {
        printf("Digite a pergunta da questão que pretende remover:\n");
        fgets(pnome, 100, stdin);
        pos = strchr(pnome, '\n');
        *pos = '\0';
        if (removeQuestaoprocess(pnome, ps) == 1)
        {
            printf("Pergunta Inexistente.\n");
            ind = -1;
        }
        else
        {
            printf("A pergunta '%s' removida com sucesso.\n", pnome);
            ind = -1;
        }
        printf("Prima 1 para remover outra pergunta ou qualquer outro número para sair.\n");
        while (scanf("%d", &rem) != 1)
        {
            limpaInput();
            printf("Prima 1 para remover nova pergunta ou qualquer outro numero para sair.\n");
        }
        limpaInput();
    } while (rem == 1 && ind == -1);
}

// "Inicia" o negrito
void bold()
{
    printf("\033[1;30m");
}

// Retira o negrito
void voltar()
{
    printf("\033[0m");
}

void mostraTabela()
{
    printf("\t$                          $\n");
    printf("\t|%s  %s      %s|\n", questao[0], dificuldade[0], quantia[0]);
    printf("\t|%s  %s      %s|\n", questao[1], dificuldade[0], quantia[1]);
    bold();
    printf("\t|%s  %s      %s|\n", questao[2], dificuldade[0], quantia[2]);
    voltar();
    printf("\t|%s  %s     %s|\n", questao[3], dificuldade[1], quantia[3]);
    printf("\t|%s  %s     %s|\n", questao[4], dificuldade[1], quantia[4]);
    bold();
    printf("\t|%s  %s     %s|\n", questao[5], dificuldade[1], quantia[5]);
    voltar();
    printf("\t|%s  %s  %s|\n", questao[6], dificuldade[2], quantia[6]);
    printf("\t|%s  %s  %s|\n", questao[7], dificuldade[2], quantia[7]);
    printf("\t|%s  %s  %s|\n", questao[8], dificuldade[2], quantia[8]);
    printf("\t$                          $\n");
}

void gerirQuestao(int question, PERGUNTA *ps)
{
    int i = 0, primeira, ultima;
    //char facil[] = "Que companhia produziu o filme 'Up! Altamente !'?";
    char media[] = "Qual era o nome do café na sitcom Friends?";
    char dificil[] = "Quantas teclas tem um piano clássico?";

    if(question == 1 || question == 2 || question == 3)
    {
        do
        {
            i++;
        }while (strcmp(ps[i].pergunta, media) != 0);
        //Estou na posição da última questão facil
        srand(time(0));
        i = rand() % i;
        mostraPergunta(ps[i]);
    }
    
    if(question == 4 || question == 5 || question == 6)
    {
        do
        {
            i++;
        }while (strcmp(ps[i].pergunta, media) != 0);
        //Estou na posição da última questão facil
        i++;
        //Estou na posição da primeira questão média
        primeira = i;
        do
        {
            i++;
        }while (strcmp(ps[i].pergunta, dificil) != 0);
        //Estou na posição da última questão media
        ultima = i;
        srand(time(0));
        i = 0;
        do{
        i = rand() % ultima;
        }while(i > ultima || i < primeira);

        mostraPergunta(ps[i]);
    }

    if(question == 7 || question == 8 || question == 9)
    {
        do
        {
            i++;
        }while (strcmp(ps[i].pergunta, dificil) != 0);
        //Estou na posição da última questão media
        i++;
        primeira = i;

        do
        {
            i++;
        } while (strlen(ps[i].pergunta) > 0);
        //Está na última pergunta dificil
        ultima = i;
        srand(time(0));
        i = 0;
        do{
        i = rand() % ultima;
        }while(i > ultima || i < primeira);

        mostraPergunta(ps[i]);
    }

}

int verificaresp()
{
    char x;
    printf("Por favor, introduza a resposta que acha correta:");
    scanf("%c", &x);
    if (x != 'A' && x != 'B' && x != 'C' && x != 'D')
    {
        printf("A sua resposta é inválida. Por favor tente outra vez...\n");
        return 1;
    }
    /*else
    {

    }*/
}

int main(void)
{
    char nome[50], *pos;
    char pnome[256];
    int op_ficheiro, op = -1, op_gestao = -1;
    PERGUNTA ps[N] = {};
    int le, grav, question = 1;

    printf("\t\t\t$$$$----------->  Bem Vindo ao 'QUEM QUER SER MILIONÁRIO'!  <-----------$$$$\n\t$$$------->  Está disposto/a a colocar o seu conhecimento à prova e a ganhar muito dinheiro?  <-------$$$\n\t\t\t$$$$------------------>  Então está no sítio certo!  <------------------$$$$\n\n\t\t\t\t\t\t");

    do
    {
        printf("Pretende ler a informação sobre as questões em modo texto ou binário?\n\n");
        printf("1- Texto\n2- Binário\n\n");
        printf("Introduzam a opção desejada: ");

        if (scanf("%d", &op_ficheiro) != 1) //Para evitar aceitar letras
        {
            limpaInput();
            printf("Opção inválida! Por favor, insira um valor correto.\n\n");
            continue;
        }

        switch (op_ficheiro)
        {
        case 1:
            le = 1;
            if (le == 1)
            {
                char file[] = "db.txt";
                leTXT(ps, file);
            }
            break;
        case 2:
            le = 2;
            if (le == 2)
            {
                char file[] = "db.bin";
                leBin(ps, file);
            }
            break;
        default:
            printf("Opção inválida! Por favor, insira um valor correto.\n\n\n");
            break;
        }
    } while ((op_ficheiro != 1) && (op_ficheiro != 2));

    do
    {
        printf("\n\t\t\t$$$$-----------> Menu Principal <-----------$$$$\n");
        printf("Escolha uma das seguintes opções:\n\n");
        printf("1- Gerir Concurso.\n2- Iniciar Concurso.\n\n0- Sair.\n\n");
        printf("---> ");
        if (scanf("%d", &op) != 1) //Para evitar aceitar letras
        {
            while (getchar() != '\n') //Para consumir o lixo
                continue;
        }

        switch (op)
        {
        case 1:
            do
            {
                op = -1;
                printf("\nEncontra-se em 'Gerir Concurso', escolha a opção que pretende:");
                printf("\n\n1- Listar Questões.\n2- Procurar Questões.\n3- Adicionar Questão.\n4- Remover Questão.\n\n0- Sair.\n\n");
                printf("---> ");
                if (scanf("%d", &op_gestao) != 1) //Para evitar aceitar letras
                {
                    while (getchar() != '\n') //Para consumir o lixo
                        continue;
                }

                switch (op_gestao)
                {
                case 1: //Listar questões
                    limpaInput();
                    mostraArray(ps, N);
                    break;
                case 2: //Listar conteúdo relacionado com a palavra, ou frase, mencionada
                    limpaInput();
                    printf("ATENÇÃO! Após digitar a palavra ou frase que procura, se a mesma existir, será listado a/as questão/ões onde a pergunta ou as respostas estão relacionadas.\n");
                    printf("Por favor, indique a para palavra, ou frase, que pretende procurar: ");
                    fgets(pnome, 100, stdin);
                    pos = strchr(pnome, '\n');
                    *pos = '\0';
                    if (listaQuestao(pnome, ps) == 1)
                    {
                        printf("Desculpe, mas '%s' não consta neste jogo.\n", pnome);
                    }
                    break;
                case 3: //Adicionar questão
                    limpaInput();
                    adicionaPergunta(ps);
                    grav = 1;
                    if (grav == 1)
                    {
                        char file[] = "db.txt";
                        gravaTXT(ps, file);
                        grav = 0;

                        if (grav == 0)
                        {
                            char file[] = "db.bin";
                            gravaBin(ps, file);

                            printf("As alterações foram guardadas com sucesso!\n");
                        }
                    }
                    break;
                case 4: //Remover questão
                    limpaInput();
                    removeQuestao(ps);
                    grav = 1;
                    if (grav == 1)
                    {
                        char file[] = "db.txt";
                        gravaTXT(ps, file);
                        grav = 0;

                        if (grav == 0)
                        {
                            char file[] = "db.bin";
                            gravaBin(ps, file);
                        }

                        printf("As alterações foram guardadas com sucesso!\n");
                    }
                    break;
                case 0: // Volta ao Menu Principal
                    break;
                default:
                    printf("Opção inválida! Por favor, insira um valor correto.\n\n\n");
                    break;
                }
            } while (op_gestao != 0); //Volta ao Menu Principal
            break;
        case 2:
            op = -1;
            printf("Por favor, introduza o seu nome (primeiro e último):\n");
            limpaInput();
            printf("---> ");
            fgets(nome, 50, stdin);
            printf("\nVamos iniciar o concurso 'QUEM QUER SER MILIONÀRIO'!\nBoa sorte %s\n", nome);
            printf("$$$ Terá 9 questões distintas. A dificuldade das questões vai aumentando ao longo do concurso, sendo as 3 primeiras de nível fácil,\nas 3 seguintes de nível médio e as últimas 3 de nível difícil.\n");
            printf("$$$ Em baixo será apresentado o valor correspondente a cada questão e o seu nível de dificuldade associado.\n\n");
            printf("\t$____________________________$\n");
            printf("\t|___________REGRAS___________|\n");
            printf("\t$                            $\n\n");
            printf("----$ Se o participante acertar todas as questões ganha o valor total de 20 000€).\n");
            printf("----$ Se errar uma questão perde toda a quantia acumulada até aquele ponto, excepto nos casos em que ultrapassou um patamar\nde segurança.\n");
            printf("----$ Os patamares de segurança garantem uma determinada quantia mesmo que o concorrente erre uma questão após ter\nultrapassado esse patamar.\n");
            printf("----$ Existem dois patamares de segurança. O primeiro corresponde a responder corretamente a todas as questões de nível fácil.\nO segundo corresponde a responder correctamente a todas as questões de nível fácil e médio.\n");
            printf("----$ Na Tabela 1 os patamares de segurança encontram-se identificados a negrito.\n\n");
            mostraTabela();
            printf("\nTabela 1: Quantia e nível de dificuldade associado com cada questão.\n");

            do
            {
               printf("Encontra-se na Questão %d\n\n", question);
               limpaInput();
               gerirQuestao(question, ps);
               
                
            } while (question != 0);
            

            //break;
        case 0:
            printf("Obrigado e até à proxima!\n");
        default:
            printf("Opção inválida! Por favor, insira um valor correto.\n\n\n");
            break;
        }
    } while (op != 0);

    return 0;
}