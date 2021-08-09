#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void imprime(float m[3][7], int linhas, int colunas, char l[3][3], int tipo){
	int i, j;
	printf ("   | x1\t\tx2\t\tf1\t\tf2\t\ta1\t\ta2\t\t\tcoef");
	printf("\n");
	for ( i=0; i<linhas; i++ ){
		printf ("%s | ", l[i]);
		for ( j = 0; j<colunas; j++ ){
			if(tipo == 1){
				printf("%.2f\t\t", m[i][j]);
			}else{
				printf("%.2e\t", m[i][j]);	
			}
		}
		printf("\n");
	}
	printf("\n\n");
}

int main(){
	
	float simplex[3][7], totfert, totdef, ferta, fertb, defa, defb, precoa, precob;
	float x1, x2, f1, f2, a1, a2, bigM, pp[2], menor, divisor0, divisor1, divisor2;
	int i, j, k, tipoMatriz, colunaMenor;
	char continua, futuroNome[3];
	char nomeLinha[3][3];
	
	
	printf ("\nUma empresa de agronegocio usa avioes para pulverizar defensivos agricolas e fertilizantes.");
	printf ("\nExistem dois modelos distintos de avioes que possuem dois tanques cada.");
	printf ("\nAvioes das marcas A e B com capacidades especificas dos tanques de defensivos e fertilizantes.");
	printf ("\nDefensivos e fertilizantes sao pulverizados ao mesmo tempo em uma mesma viagem.");
	printf ("\nCada aviao possui um custo especifico por viagem.");
	printf ("\nA empresa deseja pulverizar quantidades determinadas de defensivos e de fertilizantes a um custo minimo.\n\n");
	
	printf ("\nAvioes da marca A : tanques de defensivos -> 600 litros; Tanque de fertilizantes -> 900 litros;");
	printf ("\nAvioes da marca B : tanques de defensivos -> 600 litros; Tanque de fertilizantes -> 300 litros;");
	printf ("\nE necessario pulverizar 4800 litros de defensivos e 3600 litros de fertilizantes.");
	printf ("\nCusto de cada voo dos avioes A e B:");
	printf ("\nAvioes da marca A : R$ 1650,00");
	printf ("\nAvioes da marca B : R$ 1125,00");
	
	printf ("\nQuantos voos de cada um dos avioes serao necessarios para minimizar");
	printf ("\na funcao custo e executar a tarefa desejada pela empresa de agronegocio?\n\n");


	printf ("\nDeseja modificar os valores acima?(s/n)\n");
	scanf("%c", &continua);
	if(continua=='s'||continua=='S'){
		printf ("\nInforme o total de defensivos a ser pulverizado:");
		scanf("%f", &totdef);
		printf ("\nInforme o total de fertilizantes a ser pulverizado:");
		scanf("%f", &totfert);

		printf ("\nInforme a capacidade do tanque de defensivos do aviao A:");
		scanf("%f", &defa);		
		printf ("\nInforme a capacidade do tanque de fertilizantes do aviao A:");
		scanf("%f", &ferta);
		
		printf ("\nInforme a capacidade do tanque de defensivos do aviao B:");
		scanf("%f", &defb);
		printf ("\nInforme a capacidade do tanque de fertilizantes do aviao B:");
		scanf("%f", &fertb);
		
		printf ("\nInforme o custo total de cada viagem do aviao A:");
		scanf("%f", &precoa);
		printf ("\nInforme o custo total de cada viagem do aviao B:");
		scanf("%f", &precob);
	}else{
		totdef = 4800;
		totfert = 3600;
		defa = 600;
		ferta = 900;
		defb = 600;
		fertb = 300;
		precoa = 1650;
		precob = 1125;
	}
	
	printf("\nVizualizacao da matriz : 1 para matriz com decimais OU 2 para matriz com notacao cientifica.\n");
	scanf("%d", &tipoMatriz);
	
	printf("\nA seguir, as funcoes que modelam o problema : \n");
	
	printf("\nZmin = %.1f X1 + %.1f X2\n", precoa, precob);
	printf("\n%.1f X1 + %.1f X2 >= %.1f", defa, defb, totdef);
	printf("\n%.1f X1 + %.1f X2 >= %.1f\n", ferta, fertb, totfert);
	printf("\nO M adotado para a resolucao do metodo sera sempre a soma dos precos dos avioes A e B.");
	printf("\nQue neste caso resultara em %.2f.\n\n", precoa+precob);
	
// x1 e x2 são a quantidade de viagens que cada um dos aviões a e b farão, respectivamente.

//Construção da matriz:
	k = 1;
	
	strcpy(nomeLinha[0], "a1");
	strcpy(nomeLinha[1], "a2");
	strcpy(nomeLinha[2], "Z ");
	
	bigM = (precoa + precob);
	
	simplex[0][0] = defa;
	simplex[0][1] = defb;
	simplex[0][2] = -1;
	simplex[0][3] = 0;
	simplex[0][4] = 1;
	simplex[0][5] = 0;
	simplex[0][6] = totdef;
	simplex[1][0] = ferta;
	simplex[1][1] = fertb;
	simplex[1][2] = 0;
	simplex[1][3] = -1;
	simplex[1][4] = 0;
	simplex[1][5] = 1;
	simplex[1][6] = totfert;
	simplex[2][0] = precoa;
	simplex[2][1] = precob;
	simplex[2][2] = 0;
	simplex[2][3] = 0;
	simplex[2][4] = bigM;
	simplex[2][5] = bigM;
	simplex[2][6] = 0;
	
	imprime(simplex, 3, 7, nomeLinha, tipoMatriz);

	printf("Tirar o M das colunas das variaveis artificiais na linha do Z.\n\n");

//Tirar o M das colunas das variaveis artificiais na linha do Z	
	for(i=0;i<7;i++){
		simplex[2][i] = simplex[2][i] - (simplex[1][i])*bigM;
		simplex[2][i] = simplex[2][i] - (simplex[0][i])*bigM;
	}
	
	imprime(simplex, 3, 7, nomeLinha, tipoMatriz);

//Início de um ciclo aqui!!!	
	while (1){
//Verifica se já não há mais variáveis artificiais na solução	
		if(strcmp(nomeLinha[0], "a1") != 0 && strcmp(nomeLinha[1], "a2") != 0){
			for(i=0; i<4; i++){
				if(simplex[2][i] < 0){
					break;
				}
			}
			if(i == 4){
//Com i igual a 4, obtemos o quadro ótimo, pois não há coeficiente negativo em nenhuma variavel não artificial da linha Z.		
				break;
			}
		}
//Fazer o processo de produção para cada linha
		menor = bigM;
		for(i=0;i<4;i++){
			if(menor > simplex[2][i]){
				menor = simplex[2][i];
				colunaMenor = i;
			}
		}

//A seguir será atribuido o nome da variável que tomará uma posição na coluna da eaquerda, inicialmente contendo as variáveis artificiais
		switch (colunaMenor){
			case 0:
				strcpy(futuroNome, "x1");
				break;
			case 1:
				strcpy(futuroNome, "x2");
				break;
			case 2:
				strcpy(futuroNome, "f1");
				break;
			case 3:
				strcpy(futuroNome, "f2");
				break;
		}

		printf("\n Coluna menor : %d\t\t Iteracao numero : %d\n\n", colunaMenor, k++);

//Obtendo o pp de cada uma das linhas	
		for(i=0;i<2;i++){
			if (simplex[i][colunaMenor] == 0){
				pp[i] = bigM;
			}else{
				pp[i] = simplex[i][6] / simplex[i][colunaMenor];
			}
		}
		
//Dividir a linha por um valor específico obtendo o número 1
		if(pp[0] < pp[1]){
			strcpy(nomeLinha[0], futuroNome);
			divisor0 = simplex[0][colunaMenor];
			for(i=0;i<7;i++){
				simplex[0][i] = simplex[0][i] / divisor0;
			}
			divisor1 = simplex[1][colunaMenor];
			for(i=0;i<7;i++){
				simplex[1][i] = simplex[1][i] - simplex[0][i]*divisor1;
			}
			divisor2 = simplex[2][colunaMenor];
			for(i=0;i<7;i++){
				simplex[2][i] = simplex[2][i] - simplex[0][i]*divisor2;
			}
		}else{
			strcpy(nomeLinha[1], futuroNome);
			divisor0 = simplex[1][colunaMenor];
			for(i=0;i<7;i++){
				simplex[1][i] = simplex[1][i] / divisor0;
			}		
			divisor1 = simplex[0][colunaMenor];
			for(i=0;i<7;i++){
				simplex[0][i] = simplex[0][i] - simplex[1][i]*divisor1;
			}
			divisor2 = simplex[2][colunaMenor];	
			for(i=0;i<7;i++){
				simplex[2][i] = simplex[2][i] - simplex[1][i]*divisor2;
			}
		}
	
		imprime(simplex, 3, 7, nomeLinha, tipoMatriz);
		system ("pause");
	}
	
	printf("\nSolucoes obtidas atraves da analise do quadro otimo obtido : ");
	printf("\nA variavel %s assume o valor %.2f correspondente a %.f avioes do tipo A", nomeLinha[0], simplex[0][6], ceil(simplex[0][6]));
	printf("\nA variavel %s assume o valor %.2f correspondente a %.f avioes do tipo B", nomeLinha[1], simplex[1][6], ceil(simplex[1][6]));
	printf("\nO Valor final de Z no quadro otimo : %.2f", simplex[2][6]);
	printf("\nLogo o valor final do objetivo (Zmin) : %.2f", -1*simplex[2][6]);
	printf("\n\nSOLUCAO : Foi obtido um custo minimo de R$ %.2f ,\n", -1*simplex[2][6]);
	printf("com o aviao A fazendo %.f viagens e o aviao B fazendo %.f viagens.\n\n\n\n\n\n", ceil(simplex[0][6]), ceil(simplex[1][6]));
}
