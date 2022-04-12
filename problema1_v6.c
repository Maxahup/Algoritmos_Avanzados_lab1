#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


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
	//printf("largo nombreArchivo: %i\n", largo );
	strcpy(fileName,nombreArchivo);
	//printf("fileName: %s\n", fileName);
	char* trash=strtok(fileName,"_");
	//printf("trash %s\n", trash);
	//printf("fileName: %s\n", fileName);
	char* charMaxPonderation=strtok(NULL,"_");
	int sizeData=atoi(charMaxPonderation);
	//printf("sizeData: %i\n", sizeData );
	char* ponderation=strtok(NULL,"_");
	char* ponderationFinal=strtok(ponderation,".");
	int ponderationData=atoi(ponderationFinal);
	//printf("ponderationData: %i\n", ponderationData);

	//int Maxponderation=ponderation;
	//int dataSize=sizeDataRead;
	FILE * fp=fopen(nombreArchivo, "r");
	if (fp==NULL){
		printf("fallo lectura archivo.\n");
	}
	//printf("lectura realizada\n");

	//reserve of memory
	int** data = (int**)malloc(sizeof(int*)*sizeData);
	for (int i = 0; i < sizeData; ++i){
		data[i]=(int *)malloc(sizeof(int)*2);
	}
	//printf("reserva de memoria realizada\n");

	//reading data
	for(int i = 0; i<sizeData; i++){
		//printf("%i\n",i );
        for(int j = 0 ; j<2; j++){
            fscanf(fp, "%i", &data[i][j]);
            printf("[%i]", data[i][j] );
        }
        printf("\n");
    }
    printf("lectura de datos realizada.\n");
    fclose(fp);
    return data;
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

	int maxiumValues[2] ={0,0};
	int* combinationValues = (int *)malloc(sizeof(int)*dataSize);
	int* combinationPonderation = (int *)malloc(sizeof(int)*dataSize);
	for(int i = 0 ; i < dataSize ; i++){
		combinationValues[i] = 0;
		combinationPonderation[i] = 0;
	}
	//break(combinationValues,dataSize) != 0
	while(!breaker(combinationValues, dataSize)){
		int keep = 1;
		int CombinationSize = dataSize-1;
		int actualValues[2] ={0,0};

		while(keep == 1){
			if(combinationValues[CombinationSize] == 0){
				combinationValues[CombinationSize] = 1;
				keep = 0;
			}

			else{
				combinationValues[CombinationSize] = 0;
				CombinationSize--; 
			}
		}

		for (int i = 0; i < dataSize; ++i){
			if (combinationValues[i]==1){
				actualValues[0]=actualValues[0]+data[i][0];
				actualValues[1]=actualValues[1]+data[i][1];
			}
		}

		if(actualValues[0] > maxiumValues[0] && actualValues[1] <= maxPonderation){
			maxiumValues[0]=actualValues[0];
			maxiumValues[1]=actualValues[1];
		}
	}

	free(combinationValues);
	printf("max value found:%i with ponderation: %i\n", maxiumValues[0], maxiumValues[1] );
	//return combinationValues;	
}

int getAmountData(char *fileName){
	char* trash=strtok(fileName,"_");
	char* charAmountData=strtok(NULL,"_");
	//printf("cantidad de Datos: %s\n", charAmountData );
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
	
	char name[20];
	char copyName[20];
	printf("Ingrese el nombre del archivo con extension '.txt': \n");
	scanf("%s", name);
	strcpy(copyName,name);

	//DATA COLLECTION PROCESS
	int** data=getData(name);
	int amountData = getAmountData(name);
	int maxPonderation=getMaxPonderation(copyName);
	//printf("valor con getAmountData(name): %i\n", amountData );
	//printf("name in main: %s\n", name );
	//printf("valor con getMaxPonderation(copyName): %i\n", maxPonderation);


	//NUMBER OF POSSIBLE COMBINATIONS
	int fullyCombinations=0;
	for (int i = 1; i <= amountData; ++i){
		fullyCombinations=fullyCombinations+combination(amountData,i);
	}
	printf("combinaciones posibles: %i\n", fullyCombinations );



	//MAXIUM VALUE SEARCH PROCESS

	int valueFound[2];
	getMaxiumValue(data,amountData,maxPonderation);





	return 0;
}