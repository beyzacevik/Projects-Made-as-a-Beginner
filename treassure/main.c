#include <stdio.h>
#include <stdlib.h>
#include<string.h>


int MatrixMultiplication(int **key, int **map, int keySize, int row, int col);
int search(int **key, int **map, int keySize, int rowNo , int colNo, int startRow, int endRow, int startCol, int endCol);

int main(int argc, char **argv)
{

    //TOKENIZING THE FIRST ARGUMENT OF COMMANDLINE FOR GETTING THE SIZE OF MAP

    char *token; token =strtok(argv[1],"x");


    int rowNoMap=atoi(token) , columnNoMap=0 ;

    while (token != NULL)
    {

        columnNoMap = atoi(token);
        token = strtok(NULL, "x");

    }

    // CREATING DYNAMICALLY ALLOCATED MAP
    FILE *mapFilePointer;
    mapFilePointer = fopen(argv[3], "r");

    int **map;
    int i,j;

    map = (int **)malloc( rowNoMap * sizeof(int *));

    for(i= 0 ; i < rowNoMap ; i++){

        map[i] = malloc( columnNoMap * sizeof(int));

    }
    // filling the map array
    for(i= 0 ; i<rowNoMap ; i++){

        for(j = 0; j<columnNoMap; j++){
            fscanf(mapFilePointer , "%d", &map[i][j]);
        }
    }

    //READING KEY FILE
    FILE *keyFilePointer;
    keyFilePointer = fopen(argv[4] , "r");

    int keyRowNo = atoi(argv[2]);

    //CREATING KEY MATRIX
    int **key;
    int m,n;
    key = (int **)malloc(keyRowNo * sizeof(int *));

    for(m =0; m<keyRowNo ; m++){

        key[m] = malloc(keyRowNo*sizeof(int));

    }

    //FILLING THE KEY MATRIX
    for(m = 0; m<keyRowNo ; m++){

        for(n = 0; n<keyRowNo ; n++){

            fscanf(keyFilePointer , "%d" , &key[m][n]);
        }
    }
    //printf("%d", key[0][1]);

    //OPENING THE OUTPUT FILE TO WRITE
        FILE *outputFilePointer = fopen(argv[5], "w");
    if (outputFilePointer == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }



    int MatrixMultiplication(int **key, int **map, int keySize, int row, int col){

        int multiplication=0;
        int i, j;
        int keyVar=0 , mapVar=0;

        for(i = 0 ; i<keySize; i++){

            for(j=0 ; j<keySize ; j++){
                keyVar=key[i][j];
                mapVar=map[row+j][col+i];
                //printf("i=%d j=%d key %d map %d \n ",i,j,keyvar, mapvar);
                multiplication += keyVar*mapVar;
                //printf(" multiplication %d \n", multiplication);
            }

        }
            return multiplication;

    }

    printf("MATRIX MULTIPLICATION %d\n",MatrixMultiplication(key, map, keyRowNo, 0,0 ));

    //CREATING RECURSIVE SEARCH FUNCTION

    int search(int **key, int **map, int keySize, int rowNo, int colNo, int startRow, int endRow, int startCol, int endCol){

        int multiplication = MatrixMultiplication(key, map, keySize, startRow, startCol );

        fprintf( outputFilePointer, "%d,%d : %d\n", (startRow+endRow)/2, (startCol+endCol)/2, multiplication);

        //Base case. When the treassure found. Command 1
        if( multiplication%5 == 0){
            return 1;
        }

        //MOVE UP
        else if( multiplication%5 == 1){

            if(startRow - keySize < 0)//if on the bound it goes int the opposite direction. MOVE DOWN
                return search(key, map, keySize, rowNo,colNo,startRow+keySize,endRow+keySize,startCol,endCol);

            else{
                return search(key, map, keySize, rowNo, colNo, startRow-keySize, endRow-keySize, startCol, endCol);
            } //to MOVE UP


        }

        //MOVE DOWN
        else if( multiplication%5 == 2){

            if( endRow + keySize > rowNo)//if on the bound, it goes in the opposite direction. MOVE UP
                return search(key, map, keySize, rowNo,colNo, startRow-keySize, endRow-keySize, startCol, endCol);

            else{//to MOVE DOWN
                    return search(key, map, keySize, rowNo, colNo, startRow+keySize, endRow+keySize, startCol, endCol);
            }
        }

        //MOVE RIGHT
        else if( multiplication%5 == 3){

            if( endCol + keySize > colNo) //if on the bound it goes in the opposite direction. MOVE LEFT
                return search(key, map, keySize, rowNo,colNo, startRow, endRow, startCol-keySize ,endCol-keySize);

            else{// toMOVE RIGHT
                return search(key, map, keySize, rowNo, colNo, startRow, endRow, startCol+keySize, endCol+keySize);
            }
        }

        //MOVE LEFT
        else if( multiplication%5 == 4){

            if(startCol-keySize < 0)//if on the bound it goes in opposite direction. MOVE RIGHT
                return search(key, map, keySize, rowNo,colNo, startRow, endRow, startCol+keySize, endCol+keySize);
            else{
                    return search(key, map, keySize, rowNo, colNo, startRow, endRow, startCol-keySize, endCol-keySize);
            }
        }
    }

    search(key, map, keyRowNo, rowNoMap, columnNoMap,0, keyRowNo, 0, keyRowNo );


    free(map);
    free(key);
    return 0;
}
