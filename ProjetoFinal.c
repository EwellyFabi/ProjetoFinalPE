#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*Definindo uma estrutura*/
typedef struct{
    int numero;
    int agencia;
    int numeroDaConta;
    int DV;
    char nome[50];
    float valor;
} Cheque ;

/*Fun��o que insere os valores na struct*/
void inserirValores(Cheque *c, int n){

        printf("Digite o numero da agencia: ");
        scanf("%d", &(c+n)->agencia);
        printf("Digite o numero da conta corrente: ");
        scanf("%d", &(c+n)->numeroDaConta);
        printf("Digite o digito verificador: ");
        scanf("%d", &(c+n)->DV);
        printf("Digite o nome: ");
        scanf("%s", &(c+n)->nome);
        printf("Digite o valor do cheque: ");
        scanf("%f", &(c+n)->valor);


}

void imprimirValores(Cheque *c, int n){
    int i=0;

    for(i=0;i<n;i++){
        printf("\n          Cheque 0%d          \n\n",i+1);
        printf("Numero do cheque: %d\n", c[i].numero);
        printf("Numero da agencia: %d\n", c[i].agencia);
        printf("Numero da conta corrente: %d\n", c[i].numeroDaConta);
        printf("Digito verificador: %d\n", c[i].DV);
        printf("Nome: %s\n", c[i].nome);
        printf("Valor do cheque: %.2f\n", c[i].valor);
    }
}

/*Fun��o que conta quantos digitos tem um numero inteiro e retorna essa quantidade*/
int contaDigitos(int numero){
    int cont=0;
    if (numero==0){
        cont=1;
	}else{
        while (numero!=0){
            numero = numero / 10;
            cont += 1;
        }
	}
	return(cont);
}

/*Fun��o para validar o Digito verificador*/
int validarDV(int nConta,int DV){
    int n=nConta;
    int i,d,nInverso=0, numDigitos;

    /*Chama a fun��o contaDigitos e atribui o valor retornado � numDigitos*/
    numDigitos = contaDigitos(n);

    int tam = numDigitos;
	int vetInverso[numDigitos];

    /*Eleva 10 pela quantidade de digitos do numero da conta*/
	d = 1;
    for (i=0; i<numDigitos-1;i++)
        d = d*10;
    /*Cria um vetor com o inverso do n�mero da conta*/
	for(i=0;i<numDigitos;i++){
        tam--;
        vetInverso[tam]=n/d;
        n=n%d;
        d=d/10;
	}

	d=1;
	tam=numDigitos;

	/*Converte o vetor para um n�mero*/
	for(i=0;i<numDigitos;i++){
        tam--;
        nInverso+=vetInverso[tam]*d;
        d=d*10;
	}

    int soma = nConta+nInverso;

    /*Chama a fun��o contaDigitos e atribui o valor retornado � numDigitos*/
    numDigitos = contaDigitos(soma);

	int vetSoma[numDigitos];

    /*Eleva 10 pela quantidade de digitos do numero da soma*/
	d = 1;
    for (i=0; i<numDigitos-1;i++)
        d = d*10;
    /*Cria um vetor inteiro com os n�meros da soma*/
	for(i=0;i<numDigitos;i++){
        vetSoma[i]=soma/d;
        soma=soma%d;
        d=d/10;
	}

    /*Soma i a cada um dos valores do vetor vetSoma[i] e guarda a soma total na vari�vel soma*/
    soma=0;
	for(i=0;i<numDigitos;i++){
        vetSoma[i]=vetSoma[i]*(i+1);
        soma+=vetSoma[i];
	}

	numDigitos = contaDigitos(soma);

	/*Eleva 10 pela quantidade de digitos do numero da soma*/
	d = 1;
    for (i=0; i<numDigitos-1;i++)
        d = d*10;

    /*Atribui a variavel soma o valor do ultimo digito que j� estava salvo na variavel soma*/
	for(i=0;i<(numDigitos-1);i++){
        soma=soma%d;
        d=d/10;
	}

	if(DV==soma){
        return 0;
	}
}

int main(){
    int n=0; /*posi��o do valor apontado por c*/
    int i=1; /*numero de cheques*/

    /*c *file = (Cheque *) malloc (i*sizeof(Cheque));*/

    Cheque *c = malloc (sizeof(Cheque));

    printf("\n          Cheque 0%d          \n\n",i);
    printf("Digite o numero do cheque: ");
    scanf("%d",&c[n].numero);

    while(c[n].numero!=0){

        inserirValores(c,n);/*Chama a fun��o inserir valores*/
        int nConta, DV;
        nConta=c[n].numeroDaConta;/*Salva na vari�vel nConta, o valor inserido na vari�vel c[n].numeroDaConta*/
        DV=c[n].DV;/*Salva na vari�vel DV, o valor inserido na vari�vel c[n].DV*/
        DV = validarDV(nConta,DV);/*Chama a fun��o validarDV*/
        /*Se o Digito Verificador for validado, a fun��o armazena o registro */
        if(DV==0){
            printf("Registro realizado com sucesso!");


            n++;
            i++;
            c = (Cheque *) realloc (c, i * sizeof(Cheque));/*Realoca mem�ria para c*/
        }else{
            printf("Desculpe-me! Digito verificador invalido, por favor realize a operacao novamente!");
        }

        printf("\n          Cheque 0%d          \n\n",i);
        printf("Digite o numero do cheque: ");
        scanf("%d",&c[n].numero);
    }

    imprimirValores(c,n);

    free(c);/*Limpa a mem�ria que havia sido alocada para o ponteiro c*/

    return 0;
}
