#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int **lecturaDatos(char* nombreArchivo){
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

	//reserve of memory
	int** data = (int**)malloc(sizeof(int*)*sizeData);
	for (int i = 0; i < sizeData; ++i){
		data[i]=(int *)malloc(sizeof(int)*2);
	}

	//reading data
	for(int i = 0; i<sizeData; i++){
        for(int j = 0 ; j<2; j++){
            fscanf(fp, "%i", &data[i][j]);
            printf("[%i]", data[i][j] );
        }
        printf("\n");
    }

    fclose(fp);
    return data;
}



int main(int argc, char const *argv[]){

	//LECTURA DE ARCHIVO

	char fileName[17];
	printf("Ingrese el nombre del archivo con extension '.txt' :\n");
	scanf("%s", fileName );
	printf("ingresado: %s\n", fileName);
	int** data = lecturaDatos(fileName);

	
	//PROCESO DE BUSQUEDA
	int maxElements = 6;
	int ponderationLimit = 500;
	int maxiumValue[2] = {0,0};
	int combinationSize = 1;
	int totalPermutation = 0;
	//int total = combinatoria(6,1) + combinatoria(6,2)+ combinatoria(6,3) +combinatoria(6,4) +combinatoria(6,5) +combinatoria(6,6);
	//printf("combinaciones totales: %i.\n", total);

	while (combinationSize < maxElements){
		printf("combinationSize=%i\n", combinationSize);
		if (combinationSize==1){
			for (int i = 0; i < maxElements; ++i){
				if (data[i][1]<= ponderationLimit && data[i][0] > maxiumValue[0]){
					maxiumValue[0]=data[i][0];
					maxiumValue[1]=data[i][1];
					totalPermutation++;
					printf("new maxiumValue found with values %i,%i.\n", data[i][0], data[i][1]);				
				}
			}
			//printf("combinations of size 1 finished.\n");
			combinationSize++;
		}
		if (combinationSize>1 && combinationSize<=maxElements){
			printf("In to combinationSize=%i -- condition\n", combinationSize);
			for (int i = 0; i < maxElements; ++i){				//to keep the first element of permutation
				int combination[2] = {data[i][0], data[i][1]}; //set first value
				printf("combination SET ON: %i,%i\n.", combination[0], combination[1]);
				int permutationCount = 0;						
				while (permutationCount <= maxElements){
					int count = combinationSize+i+permutationCount;
					//combination[0] = data[i][0];
					//combination[1] = data[i][1];
					for (int j = i+1+permutationCount; j < count; ++j){
						if (j<maxElements){
							combination[0] = combination[0] + data[j][0];
							combination[1] = combination[1] + data[j][1];
							totalPermutation++;
							printf("combination[%i][%i]= %i,%i\n", i, j, combination[0], combination[1] );
						}
						if (j==maxElements || i+1+permutationCount==maxElements){
							combination[0] = combination[0] + data[j][0];
							combination[1] = combination[1] + data[j][1];
							j=count;
							totalPermutation++;
							printf("combination[%i][%i]= %i,%i\n", i, j, combination[0], combination[1] );
						}
						else{
							j=count;
						}
					}
					if ( (combination[0]>maxiumValue[0]) && (combination[1]<ponderationLimit) ){  //evluation of permutation
						maxiumValue[0]=combination[0];
						maxiumValue[1]=combination[1];
						printf("new maxiumValue found with values %i,%i and combinationSize = %i, position: %i\n", maxiumValue[0], maxiumValue[1], combinationSize,i);	
					}
					combination[0] = data[i][0];
					combination[1] = data[i][1];
					permutationCount++;
				}	
			}
			combinationSize++;
		}
		else if (combinationSize==maxElements){							//for combination of every elements
			int combination[2] = {0,0};
			for (int i = 0; i < maxElements; ++i){
				combination[0]=combination[0] + data[i][0];
				combination[1]=combination[1] + data[i][1];
			}
			if ( (combination[0]>maxiumValue[0]) && (combination[1]<ponderationLimit) ){  //evluation of permutation
						maxiumValue[0]=combination[0];
						maxiumValue[1]=combination[1];
						//printf("new maxiumValue found with values %i,%i and combinationSize = %i, position: %i\n", maxiumValue[0], maxiumValue[1], combinationSize,i);	
			}
			combinationSize++;
		}
		//combinationSize++;
		printf("combinationSize: %i\n", combinationSize );



	}
	printf("programa finalizado.\n");


	return 0;
}