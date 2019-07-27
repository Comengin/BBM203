#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void findtreasure(FILE *output, int sizekey,int row,int column,int **map,int **key,int i,int j)
{
    int k,p;
    int result=0;
    //the loop for finding multiplication of matrices
    for(k=0;k<sizekey;k++)
    {
        for(p=0;p<sizekey;p++)
        {
            result+=map[i][j]*key[k][p];
            j++;
        }
        j-=sizekey;
        i++;
    }
    fprintf(output,"%d,%d:%d\n",i-(sizekey/2+1),j+sizekey/2,result);//writing output to file
    printf("%d,%d:%d\n",i-(sizekey/2+1),j+sizekey/2,result);//writing output on screen
    result%=5;//finding mod 5
    j+=sizekey;

    if(result!=0)//keep going while our result different from zero
    {
        if(result==1)//condition for going up
        {
            if(i-sizekey!=0)
                i-=sizekey*2;
            j-=sizekey;
        }
        else if(result==2)//condition for going down
        {
            if(i==row)
                i-=sizekey*2;
            j-=sizekey;
        }
        else if(result==3)//condition for going right
        {
            if(j==column)
                j-=sizekey*2;
            i-=sizekey;
        }
        else //condition for going left
        {
            if(j-sizekey!=0)
                j-=sizekey*2;
            i-=sizekey;
        }

    findtreasure(output, sizekey, row, column, map,key, i, j);//recursive function
    }
    else
	{
		printf("\n----Treasure found----");
		fclose(output);
	}

}
void main(int argc, char *argv[])
{
  int **mapptr,**keyptr;  // dimensional arrays for map matrix and key matrix
  int i, j, row, column,sizekey=atoi(argv[2]);
  char *token;
  FILE *map;
  FILE *key;
  FILE *output;

  token = strtok(argv[1],"x");
  row = atoi(token);
  token = strtok(NULL, "x");
  column = atoi(token);

	// memory allocation for map matrix
  mapptr = (int**)malloc(row * sizeof(int*));
  for (i = 0; i<row; i++)
    mapptr[i] = (int*)malloc(column * sizeof(int));

  printf("\n");

	// memory allocation for key matrix
  keyptr = (int**)malloc(sizekey * sizeof(int*));
  for (i = 0; i<sizekey; i++)
    keyptr[i] = (int*)malloc(sizekey * sizeof(int));

  printf("\n");

  map=fopen(argv[3],"r");
  key=fopen(argv[4],"r");
  output=fopen(argv[5],"w");
  fprintf(output,"All output: \n");

  //reading map matrix elements from file
  for (i = 0; i < row; i++)  // loop for row
  {
    for (j = 0; j < column; j++)  // loop for column
      fscanf(map,"%d ",&mapptr[i][j]);
  }
  //reading key matrix elements from file
  for (i = 0; i < sizekey; i++)
  {
    for (j = 0; j < sizekey; j++)
      fscanf(key,"%d ",&keyptr[i][j]);
  }
  //loop for writing map matrix elements on screen
  printf("Map matrix: \n");
  for (i = 0; i<row; i++)
  {
    for (j = 0; j<column; j++)
    {
		printf("%d  ", mapptr[i][j]);
	}
		printf("\n");
  }

  printf("\n");
  //loop for writing key matrix elements on screen
  printf("Key matrix: \n");
  for (i = 0; i<sizekey; i++)
  {
    for (j = 0; j<sizekey; j++)
    {
		printf("%d  ", keyptr[i][j]);
	}
		printf("\n");
  }
  fclose(map);
  fclose(key);
  printf("\n");
  i=0;j=0;
  findtreasure(output, sizekey, row, column, mapptr, keyptr, i, j);

	//free memory allocation of map matrix
  for (i = 0; i < row; i++)
	free(mapptr[i]);
  free(mapptr);
	//free memory allocation of key matrix
  for (i = 0; i < sizekey; i++)
	free(keyptr[i]);
  free(keyptr);
}
