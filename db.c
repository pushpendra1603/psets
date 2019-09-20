#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char code[] = "devoifc?, XyhICrW ";
	char key[] = "key";
	char *message = malloc(strlen(code));
	
	/**
	if(argc != 2)
	{
		printf("wrong input");
		return 1;
	}
	*/
	for(int i=0; i<strlen(code); i++)
	{
		printf("%d\n", code[i]);
		printf("%d\n", key[i%(strlen(key))]);
		int x = code[i] - key[i%(strlen(key))];
		if(code[i] >= 'a' && code[i] <= 'z')
		{
			if(x < 97)
				x = 122 - ((122 - x) % 26);
			message[i] = x;
		}
		else if(code[i] >= 'A' && code[i] <= 'Z')
		{
			if(x < 65)
				x = 90 - ((90 - x) % 26);
			message[i] = x;
		}
		else
			message[i] = code[i];
	
		printf("x = %d\n", x);
	}
	printf("%s\n", message);
}