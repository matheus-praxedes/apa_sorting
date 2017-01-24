/****************************************************************
*
* Trabalho da disciplina de Análise de Projeto de Algoritmos
* Áluno: Matheus Maranhão Rêgo Praxedes
* Matrícula : 11403744
* Data de entrega : 25 / 01 / 2017
*
****************************************************************/

#include <stdio.h>
#include <stdlib.h>

// Selection Sort
void selectionSort(int *V, int n){

	int i, j, menor, troca;

	for(i = 0; i < n-1; i++){

		menor = i;
		for(j = i+1; j<n; j++){
			if(V[j] < V[menor]){
				menor = j;
			}
		}
		if(i != menor){
			troca = V[i];
			V[i] = V[menor];
			V[menor] = troca;
		}
	}
}

// Insertion Sort
void insertionSort(int *V, int n){

	int i, j, aux;

	for(i = 1; i < n; i++){

		aux = V[i];
		
		for( j = i; (j>0) && (aux < V[j-1]); j--){
			V[j] = V[j-1]; 
		}
		V[j] = aux;
	}

}

//Merge Sort
int  merge(int *V, int inicio, int meio, int fim){

	int *temp, p1, p2, tamanho, i, j, k;
	int fim1 = 0, fim2 = 0;
	tamanho = fim-inicio+1;
	p1 = inicio;
	p2 = meio + 1;
	temp = (int*) malloc(tamanho*sizeof(int));

	if(temp != NULL){

		for(i = 0; i < tamanho; i++){

			if(!fim1 && !fim2){

				if(V[p1] < V[p2]){
					temp[i] = V[p1++];
				}else{
					temp[i] = V[p2++];
				}
				if(p1 > meio){
					fim1 = 1;
				}
				if(p2 > fim){
					fim2 = 1;
				}

			}else{
				if(!fim1){
					temp[i] = V[p1++];
				}else{
					temp[i] = V[p2++];	
				}
			}
		}
		for(j=0, k = inicio; j<tamanho; j++, k++){
			V[k] = temp[j];
		}

	}
	free(temp); 
}
void mergeSort(int *V, int inicio, int fim){
	
	int meio;
	if(inicio < fim){

		meio = (inicio + fim)/2;
		mergeSort(V, inicio, meio);
		mergeSort(V, meio+1, fim);
		merge(V,inicio, meio, fim);		
	}
}

// Quicksort  
int particiona(int *V, int inicio, int fim){

	int esquerda, direita, pivo, aux;
	esquerda = inicio;
	direita = fim;
	pivo = V[inicio];

	while(esquerda<direita){

		while(V[esquerda] <= pivo){
			esquerda++;
		}
		while(V[direita] > pivo){
			direita--;
		}
		if(esquerda < direita){
			aux = V[esquerda];
			V[esquerda] = V[direita];
			V[direita] = aux;
		}
	}
	V[inicio] = V[direita];
	V[direita] = pivo;
	return direita;

}
void quickSort(int *V, int inicio, int fim){
	
	int pivo;
	if(fim > inicio){

		pivo = particiona(V,inicio,fim);
		quickSort(V,inicio,pivo-1);
		quickSort(V,pivo+1,fim);
	}
}
// Heapsort
//void heapSort(int *V, int n){
	
//}


void display( int *V, int n ){

	for(int i = 0; i < n; i++){

		printf("\n %d", V[i]);
	}
	printf("\n");
}	
int main(int argc, char * argv[]){

	int  numero = 0;
	int  vetor[7]; 
	int  contador = 0;

	
	printf("\n 1 - Selection sort");
	printf("\n 2 - Insertion sort");
	printf("\n 3 - Merge sort");
	printf("\n 4 - Quicksort");
	printf("\n 5 - Heapsort");
	printf("\n Escolha uma das opcoes acima: \n");
	scanf("%d", &numero);


	for(int i = 1; i < argc; i++){

		//printf("\nargc: %d");
		contador++;
		vetor[i-1] = atoi(argv[i]);
		//printf("\nvetor[%d]: %d",i,vetor[i]);
	}

	switch(numero){

		case 1:
			printf("\n\nVoce escolheu o  Selection sort");
			selectionSort(vetor,contador);
		break;
		
		case 2:
			printf("\n\nVoce escolheu o  Insertion sort");
			insertionSort(vetor,contador);
		break;
		
		case 3:
			printf("\n\nVoce escolheu o  Merge sort");
			mergeSort(vetor,0,6);
		break;

		case 4:
			printf("\n\nVoce escolheu o  Quicksort");
			quickSort(vetor,0,6);
		break;

		case 5:
			printf("\n\nVoce escolheu o  Heapsort");
			//heapSort(vetor,contador);
		break;

		default:
			printf("\n\nValor invalido !!");

	}

	printf("\n\n<<<Vetor ordenado>>>");
	display(vetor,contador);
	printf("\n\nFim do programa. Obrigado !");

	return 0;
}



// Falta : QUIT / MAKE / GENERALIZAR 
