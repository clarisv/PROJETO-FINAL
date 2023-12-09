#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*estrutura do combustivel*/
typedef enum {
    ALCOOL,
    DIESEL,
    GASOLINA

} Combustivel;

/*estrutura do veiculo*/
typedef struct Veiculo{

    Combustivel combustivel;
    int ano;
    char proprietario[50], modelo[10], cor[10], chassi[30], placa[8];
    struct Veiculo *proximo;

} Veiculo;

/*valida o combustivel*/
Combustivel validaCombustivel(char combustivel) 
{

    switch (combustivel){
        case 'A':
            return ALCOOL;
        case 'D':
            return DIESEL;
        case 'G':
            return GASOLINA;
        default:
            printf("\ncombustivel invalido. \n");
            exit(EXIT_FAILURE);
    }

}

/*valida a placa*/
int validarPlaca(char placa[])
{

    if (strlen(placa) != 7) {
        printf("\na placa precisa ter 7 caracteres.");
        return 0;
    }

    for (int i = 0; i < 2; ++i) {
        if (!((placa[i] >= 'A' && placa[i] <= 'Z') || (placa[i] >= 'a' && placa[i] <= 'z'))) {
            printf("os tres primeiros caracteres precisam ser alfabeticos.\n");
            return 0;
        }
    }

    for (int i = 3; i < 7; ++i) {
        if (!(placa[i] >= '0' && placa[i] <= '9')) {
            printf("os tres ultimos caracteres precisam ser numericos.\n");
            return 0;
        }
    }

    printf("\nplaca valida!\n");
    return 1;

}

/*cria o veiculo*/
Veiculo *criarVeiculo(char proprietario[50], Combustivel combustivel, char modelo[10], char cor[10], char nChassi[30], int ano, char placa[8]) {
    Veiculo *novoVeiculo = (Veiculo *)malloc(sizeof(Veiculo));
    if (novoVeiculo == NULL) {
        perror("\nerro ao inserir veiculo");
        exit(EXIT_FAILURE);
    }

    strcpy(novoVeiculo->proprietario, proprietario);
    novoVeiculo->combustivel = combustivel;
    strcpy(novoVeiculo->modelo, modelo);
    strcpy(novoVeiculo->cor, cor);
    strcpy(novoVeiculo->chassi, nChassi);
    novoVeiculo->ano = ano;
    strcpy(novoVeiculo->placa, placa);
    novoVeiculo->proximo = NULL;

    return novoVeiculo;

}

/*adiciona o veiculo na lista*/
Veiculo* adicionarVeiculo(Veiculo *lista)
{
    Veiculo *novoVeiculo = (Veiculo*)malloc(sizeof(Veiculo));
    if (novoVeiculo == NULL)
    {
        perror("\nerro ao alocar memoria para o veiculo!");
        exit(EXIT_FAILURE);
    }

    printf("\nnome do proprietario: ");
    scanf("%s", novoVeiculo->proprietario);

    char tipoCombustivel;
    printf("qual o tipo de combustivel ( A - alcool/ D - diesel/ G - gasolina): ");
    scanf(" %c", &tipoCombustivel);
    novoVeiculo->combustivel = validaCombustivel(tipoCombustivel);

    printf("modelo do veiculo: ");
    scanf("%s", novoVeiculo->modelo);

    printf("cor do veiculo: ");
    scanf("%s", novoVeiculo->cor);

    printf("numero do chassi: ");
    scanf("%s", novoVeiculo->chassi);

    printf("ano do veiculo: ");
    scanf("%d", &novoVeiculo->ano);

    printf("placa do veiculo: ");

    int placaValida;

    do{

        printf("(a placa precisa ter 7 caracteres) ");
        scanf("%s", novoVeiculo->placa);
        placaValida = validarPlaca(novoVeiculo->placa);

    }while (!placaValida);

    printf("\nveiculo cadastrado com sucesso!\n");

    novoVeiculo->proximo = lista;
    return novoVeiculo;
}


/*imprime a lista*/
void imprimirLista(Veiculo *lista)
{

    Veiculo *atual = lista;
    while (atual != NULL)
    {
        printf("proprietario: %s\n", atual->proprietario);
        printf("combustivel: \n");
        switch (atual->combustivel)
        {
        case ALCOOL:
            printf("alcool\n");
            break;
        case DIESEL:
            printf("diesel\n");
            break;
        case GASOLINA:
            printf("gasolina\n");
            break;
        }
        printf("modelo: %s\n", atual->modelo);
        printf("cor: %s\n", atual->cor);
        printf("numero do Chassi: %.2s\n", atual->chassi); // Corrigido aqui
        printf("ano: %d\n", atual->ano);
        printf("placa: %s\n", atual->placa);
        printf("\n");

        atual = atual->proximo;
    }

}


/*imprime os proprietarios*/
void funcaoA(Veiculo *lista)
{

    Veiculo *atual = lista;
    printf("\nProprietarios cujos carros sao do ano de 2010 ou mais e que sejam movidos a diesel:\n");

    while (atual != NULL)
    {

        if (atual->ano >= 2010 && atual->combustivel == DIESEL)
        {
            printf("proprietario: %s\n", atual->proprietario);
            printf("combustivel: diesel\n");
            printf("modelo: %s\n", atual->modelo);
            printf("cor: %s\n", atual->cor);
            printf("numero do Chassi: %s\n", atual->chassi);
            printf("ano: %d\n", atual->ano);
            printf("placa: %s\n", atual->placa);
            printf("\n");
        }

        atual = atual->proximo;
    }

}

/*imprime as placas*/
void funcaoB(Veiculo *lista)
{

    Veiculo *atual = lista;
    printf("\nplacas que comecam com J e terminam com 0, 2, 4 ou 7: \n");

    while (atual != NULL)
    {
        if (atual->placa[0] == 'J' && (atual->placa[6] == '0' || atual->placa[6] == '2' || atual->placa[6] == '4' || atual->placa[6] == '7'))
        {
            // Liste a placa
            printf("placa: %s\n", atual->placa);
            printf("proprietario: %s\n", atual->proprietario);
            printf("\n");
        }
        atual = atual->proximo;
    }

}

/*imprime os veiculos*/
void funcaoC(Veiculo *lista)
{

    Veiculo *atual = lista;
    printf("\nmodelo e cor dos veículos que as placas possuem vogal no segundo caractere e a soma de valores numericos da placa seja numero par: \n");

    while (atual != NULL)
    {
        int somaN = 0;
        for (int i = 3; i < 7; i++)
        {

            somaN += atual->placa[i] - '0';

        }

        if ((atual->placa[1] == 'a' || atual->placa[1] == 'e' || atual->placa[1] == 'i' || atual->placa[1] == 'o' || atual->placa[1] == 'u') && somaN % 2 == 0)
        {

            printf("modelo: %s\n", atual->modelo);
            printf("cor: %s\n", atual->cor);
            printf("\n");

        }

        atual = atual->proximo;
    }

}

/*troca o proprietario*/
void funcaoD(Veiculo *lista, char chassi[])
{
    Veiculo *atual = lista;
    int encontrado = 0;

    while (atual != NULL)
    {
        int temZero = 0;
        for (int i = 0; i < 7; i++)
        {
            if (atual->placa[i] == '0')
            {
                temZero = 1;
                break;
            }
        }

        if (temZero == 0 && strcmp(atual->chassi, chassi) == 0)
        {
            printf("\nTroca de proprietario com o fornecimento do numero do chassi apenas para carros com placas que nao possuam nenhum digito igual a zero:\n");
            printf("Numero do Chassi: %s\n", atual->chassi);
            printf("Placa: %s\n", atual->placa);
            printf("Digite o novo proprietario: ");
            scanf("%s", atual->proprietario);
            printf("\nTroca de proprietario realizada com sucesso!\n");

            encontrado = 1;
            break;
        }

        atual = atual->proximo;
    }

    if (!encontrado)
    {
        printf("\nVeiculo com o numero do chassi fornecido nao encontrado! (ou placa possui digito igual a zero.)\n");
    }
}

/*funcao principal*/
int main(void)
{
    Veiculo *listaVeiculos = NULL;
    int opcao;

    do{
        printf("\nescolha uma opcao!\n");

        printf("1 para cadastrar veiculo.\n");
        printf("2 para imprimir lista.\n");
        printf("3 para - listar todos os proprietarios cujos carros são do ano de 2010 ou posterior e que sejam movidos a diesel -\n");
        printf("4 para - listar todas as placas que comecam com a letra J e terminam com 0, 2, 4 ou 7 e seus respectivos proprietários -\n");
        printf("5 para - listar modelo e cor dos veiculos cujas placas possuem vogal no segundo caractere e a soma de valores numericos da placa seja numero par -\n");
        printf("6 para - trocar proprietário com o fornecimento do numero do chassi apenas para carros com placas que nao possuam nenhum digito igual a zero -\n");
        printf("0 para sair.\n");

        printf("\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            listaVeiculos = adicionarVeiculo(listaVeiculos);
            break;
        case 2:
            imprimirLista(listaVeiculos);
            break;
        case 3:
            funcaoA(listaVeiculos);
            break;
        case 4:
            funcaoB(listaVeiculos);
            break;
        case 5:
            funcaoC(listaVeiculos);
            break;
        case 6:
            printf("digite o numero do chassi para a troca de proprietario: ");
            char nChassi[30];
            scanf("%s", nChassi);
            funcaoD(listaVeiculos, nChassi);
            break;
        default:
            break;
        }

    } while (opcao != 0);

    
    while (listaVeiculos != NULL) {
        Veiculo *temp = listaVeiculos->proximo;
        free(listaVeiculos);
        listaVeiculos = temp;
    }

    return 0;
}
