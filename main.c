#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int somatorio(int *dados,int i){
	if(i>=0){
		return dados[i]+somatorio(dados,i-1);
	}else{
		return 0;
	}
}
float media(int *dados,int i){
	return (float)(somatorio(dados,i)/i);
}
int mediana(int *dados,int i){
	int me=i/2;
	if(i%2==0){
		return(dados[i/2]);
	}else{
		return ((dados[me]+dados[me+1])/2);
	}
}
int frequencia(int n,FILE *fp){
	int f=0,a;
	fp=fopen("dados.dat","r");
	while(fscanf(fp,"%d",&a)!=EOF){
		if(a==n){
			f++;
		}
	}
	return f;
}
char* color(){
	int i=rand()%5;
	switch(i){
		case 1:
			return "#EE3B3B";
		case 2:
			return "#D2691E";
		case 3:
			return "#CFCFCF";
		case 4:
			return "#FFDEAD";
		case 5:
			return "#228B22";
		default:
			return "#FF4040";
	}
	return "#228B22";
}
void limpa_Html(){
	FILE *f;
	f=fopen("graph.html","w");
	fprintf(f," ");
	fclose(f);
	
	
}
void gera_Html(FILE *fp,int *dados,int i){
	FILE *f;
	//static int j;
	float a;
	//j=i;
	f=fopen("graph.html","a");
	fprintf(f,"<html><head><title>Meu grafico</title></head>");
	
	
	if(i!=-1){
		a=((100*frequencia(dados[i],fp))/(10));
		fprintf(f,"<div style='width:%f\%%; height:30px;background:%s'>",a,color());
		fprintf(f,"%d<br>",dados[i]);
		fprintf(f,"</div>");
		gera_Html(fp,dados,i-1);
	}else{
		fclose(f);
	}
	
	
	
}
void ordena(int *e,int k){
	int aux;
	static int i;
	static int j;
	if(i<=k){
		if(e[i]>=e[j]){
			aux=e[i];
			e[i]=e[j];
			e[j]=aux;
			i++;
			ordena(e,k);
			
			
		}else{
			i++;
			ordena(e,k);
		}
	}else 
		if(j<=k){
				j++;
				i=0;
				ordena(e,k);
		}else{
			i=0;
			j=i;
		}
	
}
float variancia(int *dados,int i){
	int j;
	float soma=0;
	printf("%d \n",i);
	for(j=0;j<i;j++){
		soma=soma+pow(dados[j],2);
		
	}
	printf("%f \n",soma);
	return (float)((soma-(pow(somatorio((int*)dados,i),2)/i))/(i-1));
}
float desvio_padrao(int *dados,int i){
	return sqrt(variancia(dados,i));
}
int main(){
	int *dados;
	int n,ult,op;
	FILE *fp;
	int i=0;
	printf("quantos dados vao ser inseridos?");
	scanf("%d",&n);
	dados=(int *)malloc(n*sizeof(int));
	ult=0;
	limpa_Html();
	do{
		printf(	"0-Sair do programa\n"
				"1-Inserir dados\n"
				"2-Remover dados\n"
				"3-Calcular media\n"
				"4-Calcular mediana\n"
				"5-Calcular variancia\n"
				"6-Calcular desvio padrao\n"
				"7-Calcular somatorio\n"
				"8-Importar dados\n"
				"9-Gerar Grafico\n"
				"10-Calcular Somatorio\n"
				"11-Apagar Dados\n");
		scanf("%d",&op);
		
		switch(op){
			case 1:
				fp=fopen("dados.dat","a+");
				if(!(ult>=n)){
					printf("digite o valor");
					scanf("%d",&dados[ult]);
					fprintf(fp,"%d\n",dados[ult-1]);
					ult++;
					
				}
				fclose(fp);
				break;
			case 2:
				for(i=0;i<ult;i++){
					printf("%d\n",dados[i]);
				}
				break;
			case 3:
				//ordena(dados,ult);
				printf("A MEDIA E: %f\n",media(dados,ult));
				break;
			case 4:
				printf("A MEDIANA E: %d\n",mediana(dados,ult));
				break;
			case 5:
				printf("A VARIANCIA E: %.2f\n",variancia(dados,ult));
				break;
			case 6:
				printf("O DESVIO PADRAO E: %.2f\n",desvio_padrao(dados,ult));
				break;
			case 7:
				printf("O SOMATORIO E: %d\n",somatorio(dados,ult));
				break;
			case 8:
				fp=fopen("dados.dat","r");
				
				gera_Html(fp,dados,ult);
				while((fscanf(fp,"%d",&dados[ult]))!=EOF){
					ult++;
					
					
				}
				
				break;
			case 9:
				fp=fopen("dados.dat","r");
				
				gera_Html(fp,dados,ult);
				
				break;
			case 10:
				printf("SOMATORIO :%d\n",somatorio(dados,ult));
				break;
			case 11:
				fp=fopen("dados.dat","w");
				fprintf(fp," ");
				break;
			case 0:
				
				break;
		}
	}while(op!=0);
	return 0;
	
	
}
