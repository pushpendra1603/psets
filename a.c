#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char message[] = "ok";
	int key = 1;
	char *code = malloc(strlen(message));
	for(int i=0; i<strlen(message); i++)
	{
		int x = message[i] + key;
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
		{
			code[i] = message[i];
		}
		
	}
	printf("%s\n", code);
}
