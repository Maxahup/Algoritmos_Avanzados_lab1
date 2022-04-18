#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


int factorial( int n){									//funcion para obtener el factorial de un numero
	if (n==0){
		return 1;
	}
	else{
		return (n*factorial(n-1));
	}
}

int combination(int n, int m){							//funcion para obtener la combinatoria de dos valores
	if (n<=0 || m<=0){
		return 0;
	}
	else{
		int value = (factorial(n) / (factorial(m)*factorial(n-m)));
		return value;
	}
}

int **getData(char* nombreArchivo){						//funcion para la lectura del archivo de entrada
	char fileName[20];
	int largo=strlen(nombreArchivo);
	strcpy(fileName,nombreArchivo);
	char* trash=strtok(fileName,"_");
	char* charMaxPonderation=strtok(NULL,"_");
	int sizeData=atoi(charMaxPonderation);
	char* ponderation=strtok(NULL,"_");
	char* ponderationFinal=strtok(ponderation,".");
	int ponderationData=atoi(ponderationFinal);

	FILE * fp=fopen(nombreArchivo, "r");
	if (fp==NULL){
		printf("fallo lectura archivo.\nFinalizando el programa...");
		exit(-1);
	}
	else{
		//reserva de memoria
		int** data = (int**)malloc(sizeof(int*)*sizeData);
		for (int i = 0; i < sizeData; ++i){
			data[i]=(int *)malloc(sizeof(int)*2);
		}
		//lectura de datos
		for(int i = 0; i<sizeData; i++){
	        for(int j = 0 ; j<2; j++){
	            fscanf(fp, "%i", &data[i][j]);
	        }
	    }
	    fclose(fp);
	    return data;
	}
}

bool breaker(int* combinations,int dataSize){					//funcion complementaria para detener ciclo de busqueda
	for(int i=0; i < dataSize; i++){
		if(combinations[i] == 0){
			return false;
		}
	}
	return true;
}		

void getMaxiumValue(int** data, int dataSize, int maxPonderation){

	int maxiumValues[2] ={0,0};				//arreglo para guardar el valor maximo y la ponderacion
	int* combinationValues = (int *)malloc(sizeof(int)*dataSize);	//arreglo para guardar el valor de los datos en binario
	int* combinationPonderation = (int *)malloc(sizeof(int)*dataSize);	//arreglo para guardar la ponderacion de la combinacion
	for(int i = 0 ; i < dataSize ; i++){		//asignacion de valor 0 a los arreglos
		combinationValues[i] = 0;
		combinationPonderation[i] = 0;
	}
	while(!breaker(combinationValues, dataSize)){		//proceso para fijar valores a los arreglos en binario y evaluarlos con los datos leidos
		bool keep = true;
		int CombinationSize = dataSize-1;
		int actualValues[2] ={0,0};						//arreglo con el valor y la ponderacion de la combinacion actual

		while(keep){
			if(combinationValues[CombinationSize] == 0){
				combinationValues[CombinationSize] = 1;
				keep = false;
			}
			else{
				combinationValues[CombinationSize] = 0;
				CombinationSize--; 
			}
		}
		for (int i = 0; i < dataSize; ++i){			//recorre la combinacion binaria creada y suma el valor de las posiciones con un valor 1
			if (combinationValues[i]==1){
				actualValues[0]=actualValues[0]+data[i][0];
				actualValues[1]=actualValues[1]+data[i][1];
			}
		}
		if(actualValues[0] > maxiumValues[0] && actualValues[1] <= maxPonderation){		//comparacion para verificar si el valor encontrado en la combinacion es el nuevo maximo
			maxiumValues[0]=actualValues[0];
			maxiumValues[1]=actualValues[1];
		}
	}

	free(combinationValues);
	printf("maximo valor encontrado: %i con ponderacion: %i\n", maxiumValues[0], maxiumValues[1] );
}

int getAmountData(char *fileName){					//funcion para obtener desde el nombre del archivo la cantidad de datos
	char* trash=strtok(fileName,"_");
	char* charAmountData=strtok(NULL,"_");
	int amountData=atoi(charAmountData);
	return amountData;
}

int getMaxPonderation(char *nombreArchivo){			//funcion para obtener desde el nombre del archivo la ponderacion maxima
	char fileName[20];
	int largo=strlen(nombreArchivo);
	strcpy(fileName,nombreArchivo);
	char* trash=strtok(fileName,"_");
	char* charMaxPonderation=strtok(NULL,"_");
	int sizeData=atoi(charMaxPonderation);
	char* ponderation=strtok(NULL,"_");
	char* ponderationFinal=strtok(ponderation,".");
	int ponderationData=atoi(ponderationFinal);

	return ponderationData;
}

int main(int argc, char const *argv[]){
	
	//PROCESO DE DECLARACION DE VARIABLES
	time_t start, end;				//valores para el conteo del tiempo de ejecucion del algoritmo
	char name[20];
	char copyName[20];
	printf("Ingrese el nombre del archivo con extension '.txt': \n");
	scanf("%s", name);
	strcpy(copyName,name);

	//PROCESO DE OBTENCION DE DATOS
	int** data=getData(name);
	int amountData = getAmountData(name);
	int maxPonderation=getMaxPonderation(copyName);
	
	//PROCESO DE BUSQUEDA DE VALOR MAXIMO 
	start = time(NULL);						//fijacion de tiempo de inicio 
	getMaxiumValue(data,amountData,maxPonderation);
	end = time(NULL);						//detencion de la medicion del tiempo
	printf("Tiempo de ejecucion algoritmo: %f[s].\n",  difftime(end, start));

	return 0;
}