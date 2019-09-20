#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char code[] = "apl  ABZ abz? abcABC";
	int key = 80;
	char *message = malloc(strlen(code));
	for(int i=0; i<strlen(code); i++)
	{
		int x = code[i] - key;
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
		
	}
	printf("%s\n", message);
}
