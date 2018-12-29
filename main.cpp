#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include<time.h>
#include<windows.h>
#include <sys/time.h>

#include "Conio2.h";

struct TpArq
{
	int elem;
	char nome[60];
	char endereco[60];
	int status;
};


void criaArq(int qnt, char nome[])
{
	FILE *arq = fopen(nome,"wb");
	TpArq reg;
	
	for(int i = 0; i <qnt; i++)
	{
		reg.elem = i;
		strcpy(reg.endereco,"Endereco da casa do fernado");
		strcpy(reg.nome,"Fernando de almeira Noronha");
		reg.status = i;
		fwrite(&reg, sizeof(TpArq),1,arq);
	}
	fclose(arq);
}

void inserirDados(float vet[], int x, int y)
{
	float maior, menor, qnt, pos;
	
	maior = vet[0];
	
	for(int i =1; i< 4; i++)
	{
		if(vet[i] > maior)
			maior = vet[i];	
	}
	
	for(int i = 0, xini = x+5; i < 4; i++)
	{
		if(maior == 0)
		 qnt = 0;
		else
			qnt = (30 * vet[i]) / maior;
		pos = y+30;
		for(int j = 0; j <qnt; j++){
			TextColor(9,0);
			gotoxy(xini,pos);printf("%c",219);
			gotoxy(xini+1,pos);printf("%c",219);
			gotoxy(xini+2,pos);printf("%c",219);
			gotoxy(xini+3,pos);printf("%c",219);
			gotoxy(xini+4,pos--);printf("%c",219);
		}
		
		gotoxy(xini,pos);
		TextColor(7,0);
		printf("%0.2f",vet[i]);
		
		xini+= 15;
	}
}

void plotBase(int x, int y, char frase[])
{
	int w,h,f;
	f=0;
	h = 31;
	w = 60;
	//x
	for(int i=x;i<x+w;i++)
	{
		TextColor(7,0);
		gotoxy(i,y+h);printf("%c",219);
	}
	//y
	for(int i=y;i<=y+h;i++)
	{
		if(f < strlen(frase))
		{
			TextColor(2,0);
			gotoxy(x-3,i);printf("%c",frase[f++]);
		}
		TextColor(7,0);
		gotoxy(x,i);printf("%c",219);
		gotoxy(x,i);printf("%c",219);
		gotoxy(x+1,i);printf("%c",219);
	}
	
	TextColor(2,0);
	h++;
	gotoxy(x+5,y+h);printf("Exaustiva");
	gotoxy(x+20,y+h);printf("Sentinela");
	gotoxy(x+35,y+h);printf("Binaria");
	gotoxy(x+50,y+h);printf("Aleatoria");
}



void BuscaComSentinela (char arquivo[], float num[], int *min, int *med, int *max)
{
	TpArq sent;
	FILE *temp;
    int valor, i=0;
    int maior=0, menor=999999, medio=0;
    //TpInt sent;
    //srand(time(NULL));
    /*printf ("\n Consiste em inserir o elemento a ser encontrado após o último componente válido do arranjo e,");
    printf ("\n de forma sequencia, verificar a posição em que o mesmo se encontra."); getch(); system("cls")*/;
   int contador;
    
   for(i=0;i<100;i++)
	{
    	contador=0;
    
    	FILE *arq=fopen(arquivo, "rb+");
    	FILE *temp=fopen("temp.dat","wb");
    	rewind(arq);
		rewind(temp);
		
		sent.elem=num[i];
	
		fseek(arq,0,2);
		fwrite(&sent,sizeof(TpArq),1,arq);
		rewind(arq);
		fread(&sent,sizeof(TpArq),1,arq);
		contador++;
		while(sent.elem!=num[i])
		{
			fread(&sent,sizeof(TpArq),1,arq);
			contador++;
		}
		fread(&sent, sizeof(TpArq),1,arq);
		contador++;
	/*	if(!feof(arq))
			printf("\n numero %d encontrado" ,valor);
		else
			printf("\n numero %d nao encontrado" ,valor);*/
		
		//excluir
		
		
		fseek(arq,-sizeof(TpArq),2);
		sent.elem=-1;		
		fwrite(&sent,sizeof(TpArq),1,arq);
		rewind(temp);
		rewind(arq);
		fread(&sent,sizeof(TpArq),1,arq);
		contador++;
		while(sent.elem!=-1)
		{	
			fwrite(&sent,sizeof(TpArq),1,temp);
			fread(&sent,sizeof(TpArq),1,arq);
			contador++;
		}
		
		fclose(arq);
		fclose(temp);
		
		remove(arquivo);
		rename("temp.dat",arquivo);
		if(contador>maior)
			maior=contador;
		if(contador<menor)
			menor=contador;
		medio=medio+contador;
		
    }
    *max= maior;
	*med = medio/100;
	*min = menor;
}


int Busca_Exaustiva(char arquivo[], float num[], int *min, int *med, int *max)
{
   
    int valor, i=0, tempinicio, tempfinal, tempmedio, contador=0;
    int maior=0, menor=999999, medio=0;
   	FILE *arq=fopen(arquivo,"rb");
    			
    srand(time(NULL));
    tempinicio = GetTickCount();
    for(int i=0; i<100;i++)
    {
    
    	contador=0;
    
    	
    	rewind(arq);
    	fread (&valor, sizeof(int), 1, arq);
    	contador++;
	    while (!feof(arq)&& valor!=num[i])
	    {
	    	
	        fread (&valor, sizeof(int), 1, arq);
	        contador++;
	    }
	    if(contador>maior)
			maior=contador;
		if(contador<menor)
			menor=contador;
		medio=medio+contador;
		
	    /*if (valor==ex.elem)
	        printf ("\n Número %d encontrado!", ex.elem);
	    else
	        printf ("\n Número %d nao encontrado!", valor);*/
	        
	
    	
    }
    /*// finaliza o tempo
	tempfinal = GetTickCount();
	// tempo medio
	tempmedio = tempfinal - tempinicio;
	// resposta:
	printf("\n\n Tempo de execucao: %d milissegundos.",tempmedio);
	printf("\n Quantidade de iteracoes maxima: %d",maior);
	printf("\n Quantidade de iteracoes media: %d",medio/100);
	printf("\n Quantidade de iteracoes minima: %d",menor);*/
	
	tempfinal = GetTickCount();
	// tempo medio
	tempmedio = tempfinal - tempinicio;
	// resposta:
	*max= maior;
	*med = medio/100;
	*min = menor;
    
    fclose(arq);
}


void BuscaSeqIndexada(char arquivo[], float num[], int *min, int *med, int *max)
{
   
	int valor, i=0, tempinicio, tempfinal, tempmedio, contador=0, maior=0, menor=999999, medio=0;
    FILE *arq=fopen(arquivo,"rb");
    			
	tempinicio = GetTickCount();
     for(i=0;i<100;i++)
    {
    
    	contador=0;
    
    
    	rewind(arq);
    	fread(&valor, sizeof(int), 1, arq);
    	contador++;
	    while(!feof(arq) && valor>num[i])
	    {
	        fread(&valor, sizeof(int), 1, arq);
			contador++;
		}
		
	    if(contador>maior)
			maior=contador;
		if(contador<menor)
			menor=contador;
		medio=medio+contador;
	   /* if (!feof(arq) && valor==si.elem)
	    {
	        printf ("\n Número %d encontrado!", valor);
	    }
	    else
	    {
	    	printf ("\n Número %d nao encontrado.", valor);    
	    }*/
	    
    }
    // finaliza o tempo
	tempfinal = GetTickCount();
	// tempo medio
	tempmedio = tempfinal - tempinicio;
	// resposta:
	*max= maior;
	*med = medio/100;
	*min = menor;
    fclose(arq);
    
}


int BuscaBinaria (char arquivo[], float num[], int *min, int *med, int *max)
{
	//abre o arquivo 10000
	FILE *arq=fopen(arquivo,"rb");
	
	TpArq reg;
	
	int fimbase;
	int inicio, fim, meio, i=0, achou=0;
	int sorteado;
	//float t_inicio, t_fim, t_mili;
	int contador=0, contmin=0;
	int maior=0, menor=999999, medio=0;
	// o fim pode ser 999 para arquivos 1000, 9999 para 10000 e 99999 para 100000
	if(strcmp(arquivo,"arq1.dat") == 0)
		fimbase=999;
	if(strcmp(arquivo,"arq10.dat") == 0)
		fimbase=9999;
	if(strcmp(arquivo,"arq100.dat") == 0)
		fimbase=99999;

	//começa a contar o tempo
	//t_inicio = GetTickCount();
	//100 repetiçoes N=100
	for(int i = 0; i< 100; i++){
		
		inicio=0;
		fim = fimbase;
		//posiciona o ponteiro no inicio
		rewind(arq);
		//	fread(&numero,sizeof(TpInt),1,arq);
		meio=(inicio+fim)/2;
		//contador zera para cada numero procurado
		contador=0;
		//posiciona o ponteiro no meio e lê
		fseek(arq,sizeof(TpArq)*meio,0);
		fread(&reg,sizeof(TpArq),1,arq);
		contador++;
	
		while(inicio<fim && num[i]!=reg.elem)
		{
			if(num[i]>reg.elem)
			{
				inicio=meio+1;
				meio=(inicio+fim)/2;
				fseek(arq,sizeof(TpArq)*meio,0);
				fread(&reg,sizeof(TpArq),1,arq);
				contador++;
			}
			else
			{
				fim=meio;
				meio=(inicio+fim)/2;
				fseek(arq,sizeof(TpArq)*meio,0);
				fread(&reg,sizeof(TpArq),1,arq);
			    contador++;
			}
		}
		//calculo da quantidade de leitura media, maxima e minima
		if(contador>maior)
			maior=contador;
		if(contador<menor)
			menor=contador;
		medio=medio+contador;
		
		if(num[i] == meio)
			printf("");
		else
			printf("");
	}
	// finaliza o tempo
	//t_fim = GetTickCount();
	// tempo medio
	//t_mili = t_fim - t_inicio;
	// resposta:
	//*tempo = t_mili;
	*max= maior;
	*med = medio/100;
	*min = menor;
	
    fclose(arq);
}

void exeArq()
{
	criaArq(1000, "arq1.dat");
	criaArq(10000, "arq10.dat");
	criaArq(100000, "arq100.dat");
}

int main()
{  	
  	clock_t ini, fim;

	time_t t_inicio, t_fim, t_mili;
	int n = 1;
	float vetTempo[4], vetMin[4], vetMedio[4], vetMax[4], num[100];
	int min,med,max;
	
	for(int i =0; i< 4; i++)
	{
		vetTempo[i] =0;
		vetMin[i] =0;
		vetMedio[i] = 0;
		vetMax[i] = 0;
	}
	
	if(n == 1)
	{
		plotBase(5,3, "Tempo");
		
		for(int i = 0; i < 100; i++)
			num[i] = rand()%2000000;
			
		//sentinela
		ini = clock();
		BuscaComSentinela("arq1.dat",num,&min,&med,&max);
		fim = clock() - ini;
		
		vetMin[1]=min;
		vetMedio[1]=med;
		vetMax[1]=max;
		vetTempo[1]= fim;
		//exaustiva
		
		ini = clock();
		Busca_Exaustiva("arq1.dat",num, &min,&med,&max);
		fim = clock() - ini;
		
		vetMin[0]=min;
		vetMedio[0]=med;
		vetMax[0]=max;
		vetTempo[0]= fim;
		
		//t_inicio = GetTickCount();
		/// dados da busca binaria
		ini = clock();
		BuscaBinaria("arq1.dat", num, &min, &med, &max);
		fim = clock() - ini;
		
		vetMin[2] = min;
		vetMedio[2] = med;
		vetMax[2] = max;
		vetTempo[2]= fim;
		
		//sequencial
		ini = clock();
		BuscaSeqIndexada("arq1.dat", num, &min, &med, &max);
		fim = clock() - ini;
		
		vetMin[3] = min;
		vetMedio[3] = med;
		vetMax[3] = max;
		vetTempo[3]=fim;
		
		inserirDados(vetMax, 5,3);
	}
	if(n == 2)
	{
		//10000
	}
	getch();
}
