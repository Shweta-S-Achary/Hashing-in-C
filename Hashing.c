/* Shweta Selvaraj Achary	cs610 2684 prp */

#include<stdio.h>
#include<string.h>
#include <stdlib.h>

int count = 0, N;
char *A;
char *B;
int *T;

int Doubling()
{
	int i,j=0,length=0,bcount=0,k;
	char C[200];
	N = 2 * N;
	for (i = 0; i < count; i++)
	{
		B[i] = A[i];
		bcount++;
	}
	
	A = (char *)realloc(A, sizeof(char) * 15 * N); 
	T = (int *)realloc(T, sizeof(int) * N); 
	if(A == NULL)
	{
		printf("Could not allocate memory for A\n");
		return -1;
	}
	if(T == NULL)
	{
		printf("Could not allocate memory for T\n");
		return -1;
	}
	for (i = 0; i < 15*N; i++)
	{
		A[i] = ' ';
	}
	for (i = 0; i < N; i++)
	{
		T[i] = -1;
	}
		
	count = 0;

	j=0;
	for(i = 0; i<bcount; i++)
	{
		if(B[i] != '\0')
		{
			C[j] = B[i];
			length++;
			j++;
		}
		C[j] = '\0';
		if(B[i] == '\0')
		{
			char word[length];
			for(k=0;k<=length;k++)
			{
				word[k] = C[k];
			}
			j=0;
			Insert(word);
		}
	}
	
	B = (char *)realloc(B, sizeof(char) * 15 * N); 
	for (i = 0; i < 15*N; i++)
	{
		B[i] = ' ';
	}
	if(B == NULL)
	{
		printf("Could not allocate memory for B\n");
		return -1;
	}
	
	return 0;
}

int Create(int N)
{
	int i;

	A = (char *)realloc(A, sizeof(char) * 15 * N);
	B = (char *)realloc(B, sizeof(char) * 15 * N); 
	T = (int *)realloc(T, sizeof(int) * N); 
	if(A == NULL)
	{
		printf("Could not allocate memory for A\n");
		return -1;
	}
	if(B == NULL)
	{
		printf("Could not allocate memory for B\n");
		return -1;
	}
	if(T == NULL)
	{
		printf("Could not allocate memory for T\n");
		return -1;
	}

	for (i = 0; i < 15*N; i++)
	{
		A[i] = ' ';
	}
	for (i = 0; i < 15*N; i++)
	{
		B[i] = ' ';
	}
	for (i = 0; i < N; i++)
	{
		T[i] = -1;
	}
	return 0;
}

int Insert(char insert_word[])
{	
	int i, ascii, hash, index, flag, hash_new,val,dflag=0;
	
	hash = 0;
	index = count;
	ascii = 0;
	flag = 0;
	for (i = 0; i < strlen(insert_word); i++)
	{
		ascii += (int)insert_word[i];
		A[count] = insert_word[i];
		count++;
	}
	A[count] = '\0';
	count++;
	if(insert_word[0] == '*')
		dflag = 1;

	if(dflag == 1)// no need to insert deleted word in hash table
		return 0;

	else
	{
		val = FullTable();
		if(val == 1)
		{
			printf("Table is full, Doubling N\n");
			Doubling();
			return 0;
		}

		hash = ascii % N;
		
		for (i = 0; i < N; i++)
		{
			hash_new = (hash + i*i) % N;
			if (T[hash_new] == -1)
			{
				T[hash_new] = index;
				flag = 1;
				break;
			}
		}

		if (flag == 0)
		{
			printf("Could not insert %s into Hash Table T due to open addressing, so doubling N\n", insert_word);
			Doubling();
		}
		
	}
	return 0;
}

int Delete(char word[], int pos)
{
	int i = 0, ascii = 0, hash = 0, hash_new = 0, flag = 0;
	while(word[i] != '\0')
	{
		ascii += (int)word[i];
		i++;
	}
	hash = ascii % N;
	if(T[hash] == pos)
	{
		T[hash] = -1;
		flag = 1;
	}
	else
	{
		for (i = 0; i < N; i++)
		{
			hash_new = (hash + i*i) % N;
			if (T[hash_new] == pos)
			{
				T[hash_new] = -1;
				flag = 1;
				break;
			}
		}
	}
	if (flag == 0)
	{
		printf("Could not find hash of %s in hash table\n", word);
		return 1;
	}
	if(pos != -1)
	{
		while(A[pos] != '\0')
		{
			A[pos] = '*';
			pos++;
		}
		return 0;
	}
}

int Search(char word[])
{
	int i = 0, j = 0, k = 0, flag=1, wordcount = 0, ascii = 0, hash = 0, hash_new = 0, pos = 0;
	while(word[i] != '\0')
	{
		ascii += (int)word[i];
		i++;
		wordcount++;
	}
	word[i] = '\0';

	hash = ascii % N;
	i = T[hash];
    while(i <= count && k < N)
    {
    	flag = 0;
    	pos = i;
    	for(j = 0; j <= wordcount; j++)
    	{
	    	if(A[i] == word[j])
	    	{
	    		i++;
	    	}
	    	else if(A[i] == '\0')
	    	{
	    		flag = 1;
	    		break;
	    	}
	    	else if(A[i] != word[j])
	    	{
	    		flag = 1;
	    		break;
	    	}
	    }
	    if(flag == 0)
	    	break;
	    else
	    {
	    	hash_new = (hash + k*k) % N;
	    	i = T[hash_new];
	    	k++;
	    }
    }
    if (flag == 0)
    {
    	return pos;
    }
    else
    {
    	return -1;
    }

}

int Print()
{
	printf("\nA: ");
	int i = 0;
	
	while (i <= count)
		{
			if(A[i] != '\0')
				printf("%c", A[i]);
			else
				printf("\\");	
			i++;
		}

	printf("\n\nT:\n");
	for (i = 0; i < N; i++)
	{
		if(T[i] != -1)
			printf("%d: %d\n", i, T[i]);
		else
			printf("%d: -\n", i);
	}
	return 0;
}

int EmptyArray()
{
	if (A[0] == ' ')
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

int EmptyTable()
{
	int flag,i;
	for (i = 0; i < N; i++)
	{
		if (T[i] == -1)
		{
			flag = 1;
		}
		else
		{
			flag = 0;
			return 0;
			break;
		}
	}
	if (flag == 1)
	{
		return 1;
	}
}

int FullTable()
{
	int i,flag;
	for (i = 0; i < N; i++)
	{
		if (T[i] != -1)
		{
			flag = 1;
		}
		else
		{
			flag = 0;
			return 0;
			break;
		}
	}
	if (flag == 1)
	{
		return 1;
	}
}

int FullArray()
{
	if (count == 15*N)
	{
		return 1;
	}
	else
	{		
		return 0;
	}
}

int Batch(char f[])
{
	int val,value,position,left;
	char line[200],insert_word[200],word[200];
	FILE *fp;
	fp = fopen(f,"r");
	if(fp == NULL)
	{
		printf("Error opening file");
		return(-1);
	}
	while (fgets(line, sizeof(line), fp) != NULL)
    {
        const char* val1 = strtok(line, " ");
        const char* val2 = strtok(NULL, " ");
        value = atoi(val1);  

	    if(value == 10)
	    {
	    	sscanf(val2,"%s", &insert_word);
	    	left = 15*N - strlen(insert_word);
	    	val = FullArray();
			if (val == 1 || count >= left)
			{
				printf("Array A is full, Doubling size of N\n");
				Doubling();
			}
			Insert(insert_word);
		}
	    else if(value == 11)
	    {
	    	val = EmptyArray();
			if (val == 1)
			{
				printf("Array A is empty, no more words to delete\n");
			}
			else
			{
				sscanf(val2,"%s", &word);
				position = Search(word);
				if(position != -1)	
					val = Delete(word,position);
				if(val == 0 && position != -1)
					printf("%s deleted from slot %d\n", word, position);
				else
					printf("%s not found\n", word);
			}
	    }
	    else if(value == 12)
	    {
	    	sscanf(val2,"%s", &word);
			position = Search(word);
			if(position != -1)
				printf("%s found at slot %d\n", word, position);
			else
				printf("%s not found\n", word);
	    }
	    else if(value == 13)
	    	Print();
	    else if(value == 14)
	    {
	    	N = atoi(val2);
	    	Create(N);
	    }
	    else if(value == 15)
	    	printf("");

	}
	
    if (feof(fp))
    	printf("\nEnd of file reached\n"); 
    else
    	printf("\nSomething went wrong\n");
    fclose(fp);

	return 0;
}

int main(int argc, char *argv[])
{	
	// Command for Batch Processing 10:Insert 11:Delete 12:Search 13:Print 14:Create 15:Comment
	int i,key,mainkey,val,val2,sflag = 0,position,left;
	char ans,word[200],f[50];
	char insert_word[200];

	A = (char *)malloc(sizeof(char) * 100);
	B = (char *)malloc(sizeof(char) * 100);
	T = (int *)malloc(sizeof(int) * 20);
	if(A == NULL)
	{
		printf("Could not allocate memory for A\n");
		return -1;
	}
	if(B == NULL)
	{
		printf("Could not allocate memory for B\n");
		return -1;
	}
	if(T == NULL)
	{
		printf("Could not allocate memory for T\n");
		return -1;
	}

	printf("Select an option:-\n 1) Batch Processing \n 2) Individual Functions\n");
	scanf("%d", &mainkey);
	if(mainkey == 1)
	{
		sscanf(argv[1],"%s",&f);
		sflag = 1;
		Batch(f);
	}
	else if(mainkey == 2)
	{
		
		do
		{
			printf("Select an option between 1-7:-\n 1) Create \n 2) Insert \n 3) Delete \n 4) Search \n 5) Print \n 6) Empty \n 7) Full \n");
			scanf("%d", &key);
			
			if(sflag == 0 && key != 1)
			{
				printf("ERROR: Array and Table not yet created. Use option '1' to create the Array and Table. \n");
			}
			else
			{
				switch(key)
				{
					case 1: printf("Enter value for N: ");
							scanf("%d", &N);
							Create(N);
							sflag = 1;
							break;
					case 2: printf("Enter word to be inserted: ");
							scanf("%s", &insert_word);
							left = 15*N - strlen(insert_word);
							val = FullArray();
							if (val == 1 || count >= left)
							{
								printf("Array A is full, Doubling size of N\n");
								Doubling();
							}
							Insert(insert_word);
							break;
					case 3: val = EmptyArray();
							if (val == 1)
							{
								printf("Array A is empty, no more words to delete\n");
							}
							else
							{	printf("Enter word to be deleted:");
								scanf("%s", &word);
								position = Search(word);
								if(position != -1)	
									val2 = Delete(word,position);
								if(val2 == 0 && position != -1)
									printf("%s deleted from slot %d\n", word, position);
								else
									printf("%s not found\n", word);
								break;
							}

					case 4: printf("Enter word to be searched:");
							scanf("%s", &word);
							position = Search(word);
							if(position != -1)
								printf("%s found at slot %d\n", word, position);
							else
								printf("%s not found\n", word);
							break;
					case 5: Print();
							break;
					case 6: val = EmptyArray();
							if (val == 1)
							{
								printf("Array A is Empty\n");
							}
							else
							{
								printf("Array A is Not Empty\n");
							}
							val2 = EmptyTable();
							if (val2 == 1)
							{
								printf("Table T is Empty\n");
							}
							else
							{
								printf("Table T is Not Empty\n");
							}
							break;
					case 7: val = FullArray(); //Check this function condition
							if (val == 1)
							{
								printf("Array A is Full\n");
							}
							else
							{
								printf("Array A is Not Full\n");
							}
							val2 = FullTable();
							if (val2 == 1)
							{
								printf("Table T is Full\n");
							}
							else
							{
								printf("Table T is Not Full\n");
							}
							break;
					default: break;
				}
			}
			printf("Do you want to continue, Y/y or N/n? : ");
			scanf("%s", &ans);		
		}while(ans == 'Y' || ans == 'y');
	}

	else
	{
		printf("You Entered Incorrect value\n");
	}
	free(A);
	free(B);
	free(T);
	return 0;
}