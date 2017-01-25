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
		for(j = i+1; j < n; j++){
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
/*
void criaHeap(int *v, int i, int f){

	int aux = v[i];
	int j = i*2+1;
	while(j<=f){

		if(j<f){
			if(v[j] < v[j+1]){
				j = j+1;
			}
			if(aux < v[j]){
				v[i] = v[j];
				i = j;
				j = 2*i+1;
			}
			else{
				j = f+1;
			}

		}
	}
	v[i] = aux;
}
void heapSort(int *V, int n){
	
	int i, aux;
	for(i = (n-1)/2; i>=0; i--){
		criaHeap(V, i, n-1);
	}
	for( i = n-1; i >=1; i--){
		aux = V[0];
		V[0] = V[i];
		V[i] = aux;
		criaHeap(V,0,i-1);
	}	
}*/
void maxHeapify(int* v, int n){
	for(int i = n/2; i >= 0; i--){
		heapify(i, n, v);
	}
}

void heapify(int head, int size, int* list){
	
	int max = head;
	int left = head*2 + 1;
	int right = head*2 + 2;
	int aux;

	if(left > size-1)
		left = head;

	if(right > size-1)
		right = head;	

	if(list[max] < list[left])
		max = left;

	if(list[max] < list[right])
		max = right;

	aux = list[max];
	list[max] = list[head];
	list[head] = aux;

	if(max != head)
		heapify(max, size, list);
}

void heapSort(int* v, int n){
	
	maxHeapify(v,n);
	int aux;
	for(int i = n-1; i > 0; i--){
		heapify(0, i+1, v);
		aux = v[0];
		v[0] = v[i];
		v[i] = aux;
	}
}
void display( int *V, int n ){

	for(int i = 0; i < n; i++){

		printf("\n %d", V[i]);
	}
	printf("\n");
}	


int main(int argc, char * argv[]){

	int  numero = 0;
	int tamanho;

	scanf("%d",&tamanho);
	int* vetor = (int*)calloc(tamanho,sizeof(int));

	for(int i = 0; i < tamanho; i++){
		
		int el;
		scanf("%d",&el);
		vetor[i] = el;
	}

	
	numero = atoi(argv[1]);
	int i = 0;

	switch(numero){

		case 1:
			selectionSort(vetor,tamanho);
		break;
		
		case 2:
			insertionSort(vetor,tamanho);
		break;
		
		case 3:
			mergeSort(vetor,0,tamanho-1);
		break;

		case 4:
			quickSort(vetor,0,tamanho-1);
		break;

		case 5:
			heapSort(vetor,tamanho);
		break;

		default:
			printf("\n\nValor invalido !!");
			break;

	}

	display(vetor,tamanho);
	free(vetor);

	return 0;
}




