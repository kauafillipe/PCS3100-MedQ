#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define TAM 60

struct usuario
{
    char nome_usuario[TAM];
    char senha_usuario[TAM];
    char condicao[TAM];
};

int login(char* nome, char* senha);

int main (void)
{
    struct usuario user;

    char sintoma1[TAM],
         sintoma2[TAM],
         sintoma3[TAM];

    char a[] = "febre",
         b[] = "dor de cabeca",
         c[] = "dores no corpo",
         d[] = "mal-estar",
         e[] = "diarreia",
         f[] = "tosse",
         g[] = "cansaco",
         h[] = "calafrio";

    FILE *pa = fopen("infouser.txt", "w");

    /*assumimos que o usuario se cadastrou previamente*/

    strcpy(user.nome_usuario, "user1");
    strcpy(user.senha_usuario, "senha1");

    login (user.nome_usuario, user.senha_usuario);

    system("pause");

    printf("Ola! Meu nome e Dr.Tech.\n");

    int erro,
        i;

    do
    {
        erro = 0;
        printf("\nme diga tres sintomas que voce esta sentindo\n");

        gets(sintoma1);
        gets(sintoma2);
        gets(sintoma3);

        i = 0;

        printf("\n");

        /*previne erros de digitacao por letra minuscula e maiuscula*/

        while (sintoma1[i])
        {
            if (isalpha(sintoma1[i]) != 0)
            {
                sintoma1[i] = tolower(sintoma1[i]);
            }

            i++;
        }

        i = 0;

        while (sintoma2[i])
        {
            if (isalpha(sintoma1[i]) != 0)
            {
                sintoma2[i] = tolower(sintoma2[i]);
            }

            i++;
        }

        i = 0;

        while (sintoma3[i])
        {
            if (isalpha(sintoma1[i]) != 0)
            {
                sintoma3[i] = tolower(sintoma3[i]);
            }

            i++;
        }

        if(strcmp(b,sintoma1) == 0 || strcmp(b,sintoma2) == 0 || strcmp(b,sintoma3) == 0)
        {
            if (strcmp(a,sintoma1) == 0 || strcmp(a,sintoma2) == 0 || strcmp(a,sintoma3) == 0)
            {
                if (strcmp(c,sintoma1) == 0 || strcmp(c,sintoma2) == 0 || strcmp(c,sintoma3) == 0)
                {
                    strcpy (user.condicao , "dengue");
                    printf("Voce pode estar com dengue.\n Recomendamos que evite o consumo de aspirina e anti-inflamatorios e que fique de repouso.\n Hidrate-se regularmente.");
                }
                else if(strcmp(h,sintoma1) == 0 || strcmp(h,sintoma2) == 0 || strcmp(h,sintoma3) == 0)
                {
                    strcpy (user.condicao , "gripe comum");
                    printf("Voce pode estar com gripe comum.\n Recomendamos que fique de repouso e hidrate-se frequentemente.\n Usar um umidificador e lavar o nariz com soro tambem pode ajudar a amenizar os sintomas.");
                }
            }
            else if (strcmp(e,sintoma1) == 0 || strcmp(e,sintoma2) == 0 || strcmp(e,sintoma3) == 0)
            {
                if (strcmp(d,sintoma1) == 0 || strcmp(d,sintoma2) == 0 || strcmp(d,sintoma3) == 0)
                {
                    strcpy (user.condicao , "virose comum");
                    printf("Voce pode estar com uma viorose comum.\n Recomendamos que se hidrate constantemente e fique de repouso.\n Tente fazer refeicoes mais leves: evite alimentos gordurosos ou apimentados e de preferencia para frutas, legumes e carnes brancas ao inves da carne vermelha.");
                }
            }
        }
        else if (strcmp(a,sintoma1) == 0 || strcmp(a,sintoma2) == 0 || strcmp(a,sintoma3) == 0)
        {
            if (strcmp(f,sintoma1) == 0 || strcmp(f,sintoma2) == 0 || strcmp(f,sintoma3) == 0)
            {
                if (strcmp(g,sintoma1) == 0 || strcmp(g,sintoma2) == 0 || strcmp(g,sintoma3) == 0)
                {
                    strcpy (user.condicao , "covid-19");
                    printf("Voce pode estar infectado pelo covid-19.\n Recomendamos que voce se mantenha isolado por pelo menos uma semana para nao infectar outras pessoas.\n Tambem recomendamos que voce higienize as maos frequentemente e use mascara.\n Hidratacao frequente e repouso podem amenizar os sintomas.");
                }
            }
        }
        else
        {
            printf("Nao encontrei um ou mais dos seus sintomas no nosso banco de dados. Verifique se nao houve algum erro de digitacao e tente novamente.");
            erro = 1;
        }

    } while (erro != 0);

    printf("\n\tApesar das nossas recomendacoes, insistimos que um profissional da saude seja consultado.\n");

    system("pause");

    /*manda para a "nuvem" o diagnostico do usuario*/
    fprintf(pa,"%s : \n%s\n\n\n",user.nome_usuario, user.condicao);

    fclose(pa);



    return 0;
}

int login(char* nome, char* senha)
{
    /*supomos que o usu�rio j� est� cadastrado e seu nome � usuario e sua senha � senha*/

    /*dados digitados pelo usu�rio durante seu login*/

    char nome_digitado[TAM];
    char senha_digitada[TAM];

    /*vari�vel que permite o la�o e define se houve ou n�o sucesso no login*/

    int sucesso = 0;

    while (sucesso != 1)
    {
        printf("Nome:");
        gets(nome_digitado);

        printf("Senha:");
        gets(senha_digitada);

        if (strcmp(nome, nome_digitado) == 0 && strcmp(senha, senha_digitada) == 0) /*compara��o de strings com uso da biblioteca string.h*/
        {
            printf("Login efetuado com sucesso!\n");
            sucesso = 1;
        }
        else
        {
            printf("Dados incorretos. Por favor, digite novamente. \n");
        }
    }

    return 0;
}
