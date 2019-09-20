#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char message[] = "ahelloz?, AheLLoZ";
	char key[] = "key";
	char *code = malloc(strlen(message));
	
	/**
	if(argc != 2)
	{
		printf("wrong input");
		return 1;
	}
	*/
	for(int i=0; i<strlen(message); i++)
	{
		printf("%d\n", message[i]);
		printf("%d\n", key[i%(strlen(key))]);
		int x = message[i] + key[i%(strlen(key))];
		if(message[i] >= 'a' && message[i] <= 'z')
		{
			if(x > 122)
				x = 97 + ((x - 97) % 26);
			code[i] = x;
		}
		else if(message[i] >= 'A' && message[i] <= 'Z')
		{
			if(x > 90)
				x = 65 + ((x - 65) % 26);
			code[i] = x;
		}
		else
			code[i] = message[i];
		printf("x = %d\n", x);
	}
	printf("%s\n", code);
}
