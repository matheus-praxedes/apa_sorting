/****************************************************************
*
* Trabalho da disciplina de Análise de Projeto de Algoritmos
* Áluno: Matheus Maranhão Rêgo Praxedes
* Matrícula : 11403744
* Data de entrega : 25 / 01 / 2017
* Data de atualização : 07 / 02 / 2017
*
*Observações: As atualizações incluem a adição dos seguintes al-
*goritmos: counting sort, radix sort e bucket sort para o ter-
*ceriro trabralho de ordenação da disciplina. 
* 
*
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
//#define  RANGE 9918 // max - min + 1


// Funções auxiliares 
void display( int *V, int n ){

	for(int i = 0; i < n; i++){

		printf("\n %d", V[i]);
	}
	printf("\n");
}	

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int elementMax(int *V, int n){
	
	int max = V[0];

	for(int i = 1; i < n; i++)
		if(V[i] > max)
			max = V[i];

	return max;
}	

int elementMin(int *V, int n){
	
	int min = V[0];

	for(int i = 1; i < n; i++)
		if(V[i] < min)
			min = V[i];

	return min;
}
//

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


void maxHeapify(int* v, int n){
	for(int i = n/2; i >= 0; i--){
		heapify(i, n, v);
	}
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

// Counting sort
void countingSort(int *V, int n){

	
    int output[n];
    int range, min, max;
    min = elementMin(V,n);
    max = elementMax(V,n);
    range = max - min + 1;

    int count[range] = {0}, i;
 
    
    for(i = 0; i < n; i++)
        ++count[V[i]-min];
 
    for (i = 1; i < range; i++)
        count[i] += count[i-1];
 
    for (i = 0; i < n; i++)
    {
        output[ count[ V[i] -min]-1] = V[i];
        --count[V[i] - min];
    }
 
    for (i = 0; i < n; i++)
        V[i] = output[i];
    	
    	
    	
}

//Bucket sort
void bucketSort(int *V, int n)
{
 	
    int max = elementMax(V,n); 
    int min = elementMin(V,n);
    int range = max - min + 1;

	int num_buckets = n;
	float bucket_size = float(range)/num_buckets;

	vector<int> * buckets = new vector<int>[num_buckets];

	for(int i = 0; i < n; i++){
		int index = int((V[i]-min)/bucket_size);
		buckets[index].push_back(V[i]);
	}

	for(int i = 0; i < n; i++)
		sort(buckets[i].begin(), buckets[i].end());

	int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < buckets[i].size(); j++)
          V[index++] = buckets[i][j];

	delete[] buckets;
}
    

//Radix sort 
void countSort(int *V, int n, int exp)
{
    int output[n]; 
    int i, count[10] = {0};
 
    
    for (i = 0; i < n; i++)
        count[ (V[i]/exp)%10 ]++;
 
    
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    
    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (V[i]/exp)%10 ] - 1] = V[i];
        count[ (V[i]/exp)%10 ]--;
    }
 
    
    for (i = 0; i < n; i++)
        V[i] = output[i];
}


int getMax(int *V, int n)
{
    int max = V[0];
    for (int i = 1; i < n; i++)
        if (V[i] > max)
            max = V[i];
    return max;
}

void radixSort(int *V, int n)
{
    
    int m = getMax(V, n);
 
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(V, n, exp);
}



// Função principal
int main(int argc, char * argv[]){

	int numero = 0;
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

		case 6:
			qsort (vetor, tamanho, sizeof(int), compare);
		break;

		case 7:
			countingSort(vetor, tamanho);
		break;

		case 8:
			bucketSort(vetor, tamanho);
		break;

		case 9:
			radixSort(vetor, tamanho);
		break;

		default:
			printf("\n\nValor invalido !!");
			break;

	}

	display(vetor,tamanho);
	free(vetor);

	return 0;
}




