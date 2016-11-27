//Dupla: Gilmarllen P Miotto e Rhuan Caetano

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

void calcDerivadaDois(int np, double* x, double* y, double* s)
{
	double e[np], d[np];
	
	double hA = x[2] - x[1], hB;
	double deltaA = (y[2] - y[1])/hA, deltaB;

	/*Montando o sistema tridiagonal simetrico*/
	for(int i=1; i<= np-2; i++)
	{
		hB = x[i+2] - x[i+1]; //Distancia entre dois pontos adjacentes;
		deltaB = (y[i+2] - y[i+1])/hB; //Inclinação entre os pontos adjacentes;

		e[i] = hB;
		d[i] = 2*(hA + hB);
		s[i+1] = 6*(deltaB - deltaA);

		/*Atualiza os valores para o próximo passo*/
		hA = hB;
		deltaA = deltaB;
	}

	
	double t;
	/*Eliminação de Gauss para o sistema tridiagonal simetrico montado*/
	for(int i=2; i<= np-2; i++)
	{
		t = e[i-1]/d[i-1];
		d[i] -= t * e[i-1];
		s[i+1] -= t * s[i];
	}

	/*Executando substituicoes retroativas*/
	s[np-1] /= d[np-2];
	for(int i=np-2; i>=2; i--)
		s[i] = (s[i] - e[i-1] * s[i+1]) / d[i-1];

	s[1] = 0;
	s[np] = 0;	
}

double m[5][9999]; // matriz com os parametros a,b,c,d
void achandoParametros( int np, double* x, double* y, double* s)
{
	for( int i = 1; i<=np; i++){
		m[1][i] = (s[i+1]-s[i])/(6*(x[i+1]-x[i]));
		m[2][i] = s[i]/2;
		m[3][i] = (y[i+1] - y[i])/(x[i+1]-x[i]) - ((s[i+1] + 2*s[i])/6)*(x[i+1]-x[i]);
		m[4][i] = y[i];
	}
	
}

void encerra(int opc)
{
	if(opc==0)
		printf("Programa encerrado.\n");

	if(opc==1)
		printf("Numero de pontos deve ser no minimo 3.\n");

	exit(opc);
}

int main()
{
	printf("Digite uma opcao:\n");
	printf("1 - Ler dados via teclado\n2 - Ler dados via arquivo\n3 - Sair\n\nEscolha:");

	int opc=0;
	scanf("%d", &opc);

	if(opc==3)
		encerra(0);

	int nPontos=0; //Numero de pontos do problema;
	double x[9999], y[9999]; //Coordenadas x e y dos pontos;
	double s[9999]; //Valores calculados de s'';
	double z; //Ponto de teste;

	//Leitura dos dados
	if(opc==1)
	{
		printf("Opcao 1 selecionada.\n\n");

		printf("Quantidade de pontos:\n");
		scanf("%d", &nPontos);

		if(nPontos < 3)
			encerra(1);

		printf("a lista de valores de x, separados por espaco:\n");
		for(int i=1; i<=nPontos; i++)
			scanf("%lf", &x[i]);


		printf("a lista de valores de y, separados por espaco:\n");
		for(int i=1; i<=nPontos; i++)
			scanf("%lf", &y[i]);

		printf("o valor de z:\n");
		scanf("%lf", &z);
	}

	if(opc==2)
	{
		printf("Opcao 2 selecionada.\n\n");

		printf("Digite uma opção:\n1 - Ler arquivo dados1.txt\n2 - Ler arquivo dados2.txt\n3 - Ler arquivo dados3.txt\n4 - Sair\n");
		int opc2=0;
		scanf("%d", &opc2);

		if(opc2==4)
			encerra(0);

		char arquivo[10] = "dados", aux[3];
		aux[0] = opc2 + '0';
		aux[1] = '\0';
		strcat(arquivo, aux);
		strcat(arquivo, ".txt");

		FILE* farq = fopen(arquivo, "r");

		fscanf(farq, "%d", &nPontos);

		for(int i=1; i<=nPontos; i++)
			fscanf(farq, "%lf", &x[i]);

		for(int i=1; i<=nPontos; i++)
			fscanf(farq, "%lf", &y[i]);

		fscanf(farq, "%lf", &z);
	}

	
	calcDerivadaDois(nPontos, x, y, s);
	achandoParametros(nPontos, x, y, s);
	
	if(z>=x[1] && z<x[2]){
		double spline = m[1][1]*pow((z-x[1]),3) + m[2][1]*pow((z-x[1]),2) + m[3][1]*(z-x[1]) + m[4][1];
		printf("\n\n\ns(z) = %lf\n", spline);
	}else{
		for(int i=2; i<=nPontos; i++){
			if(z>=x[i]){
				double spline = m[1][i]*pow((z-x[i]),3) + m[2][i]*pow((z-x[i]),2) + m[3][i]*(z-x[i]) + m[4][i];
				printf("\n\n\ns(z) =  %lf\n", spline);
				break;
			}
		}
	}
	
	int amostragemM = 50; //Numero de pontos de amostragem para gerar o grafico

	//Escrita no arquivo grafico.txt para geracao do grafico com o MatLab
	ofstream file;
	file.open ("grafico.txt");
	double pulo = (fabs(x[nPontos]-x[1]))/amostragemM;
	double var = x[1];
	int i=1;
	while(var <= x[nPontos]){
		if(var>=x[i+1]) i++;
		double spline = m[1][i]*pow((var-x[i]),3) + m[2][i]*pow((var-x[i]),2) + m[3][i]*(var-x[i]) + m[4][i];
		file << var << " " << spline << endl;
		var+=pulo;
	} 
	file.close();

	return 0;
}
