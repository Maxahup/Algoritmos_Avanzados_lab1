#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


int factorial( int n){
	if (n==0){
		return 1;
	}
	else{
		return (n*factorial(n-1));
	}
}

int combination(int n, int m){
	if (n<=0 || m<=0){
		return 0;
	}
	else{
		int value = (factorial(n) / (factorial(m)*factorial(n-m)));
		return value;
	}
}

int **getData(char* nombreArchivo){
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
		//reserve of memory
		int** data = (int**)malloc(sizeof(int*)*sizeData);
		for (int i = 0; i < sizeData; ++i){
			data[i]=(int *)malloc(sizeof(int)*2);
		}
		//reading data
		for(int i = 0; i<sizeData; i++){
	        for(int j = 0 ; j<2; j++){
	            fscanf(fp, "%i", &data[i][j]);
	        }
	    }
	    fclose(fp);
	    return data;
	}
}

bool breaker(int* combinations,int dataSize){
	for(int i=0; i < dataSize; i++){
		if(combinations[i] == 0){
			return false;
		}
	}
	return true;
}		

void getMaxiumValue(int** data, int dataSize, int maxPonderation){

	int maxiumValues[2] ={0,0};				//save the max value and ponderation found
	int* combinationValues = (int *)malloc(sizeof(int)*dataSize);	//create an array to save combinations, always of data´s size
	int* combinationPonderation = (int *)malloc(sizeof(int)*dataSize);	//analogous to the above
	for(int i = 0 ; i < dataSize ; i++){		//initialize arrays with value 0 
		combinationValues[i] = 0;
		combinationPonderation[i] = 0;
	}
	while(!breaker(combinationValues, dataSize)){		//process to set values to arrays with binary values and then evaluate them with values of the original data
		bool keep = true;
		int CombinationSize = dataSize-1;
		int actualValues[2] ={0,0};						//array that save the value of the combination observed

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
		for (int i = 0; i < dataSize; ++i){			//collect the values comparing the position of the combination created and the data
			if (combinationValues[i]==1){
				actualValues[0]=actualValues[0]+data[i][0];
				actualValues[1]=actualValues[1]+data[i][1];
			}
		}
		if(actualValues[0] > maxiumValues[0] && actualValues[1] <= maxPonderation){		//check if the actual combination it's a new max value and replace if this is true
			maxiumValues[0]=actualValues[0];
			maxiumValues[1]=actualValues[1];
		}
	}

	free(combinationValues);
	printf("max value found: %i with ponderation: %i\n", maxiumValues[0], maxiumValues[1] );
}

int getAmountData(char *fileName){		
	char* trash=strtok(fileName,"_");
	char* charAmountData=strtok(NULL,"_");
	int amountData=atoi(charAmountData);
	return amountData;
}

int getMaxPonderation(char *nombreArchivo){
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
	
	time_t start, end;
	char name[20];
	char copyName[20];
	printf("Ingrese el nombre del archivo con extension '.txt': \n");
	scanf("%s", name);
	strcpy(copyName,name);

	//DATA COLLECTION PROCESS
	int** data=getData(name);
	int amountData = getAmountData(name);
	int maxPonderation=getMaxPonderation(copyName);
	
	//MAXIUM VALUE SEARCH PROCESS
	start = time(NULL);
	getMaxiumValue(data,amountData,maxPonderation);
	end = time(NULL);
	printf("Tiempo de ejecucion algoritmo: %f[s].\n",  difftime(end, start));

	return 0;
}