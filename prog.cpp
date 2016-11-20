#include <cstdio>
#include <cstdlib>

void resolve(int np, double* x, double* y, double* s)
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


	int nPontos=0; //Numero de pontos do problema;
	double x[99999], y[99999]; //Coordenadas x e y dos pontos;
	double s[99999]; //Valores calculados de s'';
	double z; //Ponto de teste;

	if(opc==1)
	{
		printf("Opcao 1 selecionada.\n\n");

		printf("Quantidade de pontos:");
		scanf("%d", &nPontos);

		if(nPontos < 3)
			encerra(1);

		printf("a lista de valores de x, separados por espaco:");
		for(int i=1; i<=nPontos; i++)
			scanf("%lf", &x[i]);


		printf("a lista de valores de y, separados por espaco:");
		for(int i=1; i<=nPontos; i++)
			scanf("%lf", &y[i]);

		printf("o valor de z:");
		scanf("%lf", &z);

		resolve(nPontos, x, y, s);
		
		//Debug
		for(int i=1; i<=nPontos; i++)
			printf("%lf ", s[i]);
		printf("\n");

		//imagem(z);
	}

	if(opc==2)
	{
		printf("Opcao 2 selecionada.\n\n");
		scanf("%d", &nPontos);

		for(int i=1; i<=nPontos; i++)
			scanf("%lf", &x[i]);

		for(int i=1; i<=nPontos; i++)
			scanf("%lf", &y[i]);

		scanf("%lf", &z);

		resolve(nPontos, x, y, s);
		//imagem(z);
	}

	if(opc==3)
		encerra(0);

	return 0;
}
