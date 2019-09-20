#define _XOPEN_SOURCE
#include <stdio.h>
#include <crypt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
/**	if(argc != 1){
		printf("wrong input");
		return 1;
	}*/

	char hash[] = "50cI2vYkF0YU2";
	char salt[2];
	strncpy(salt, hash, 2);
	// char letters[] = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char letters[] = "\0LOLlol";

	char pswd[] = "\0\0\0\0\0\0";
	for(int i0=0; i0<8; i0++){
		for(int i1=0; i1<8; i1++){
			for(int i2=0; i2<8; i2++){
				for(int i3=0; i3<8; i3++){
					for(int i4=0; i4<8; i4++){
							pswd[0] = letters[i0];
							pswd[1] = letters[i1];
							pswd[2] = letters[i2];
							pswd[3] = letters[i3];
							pswd[4] = letters[i4];
							if(strcmp(crypt(pswd,salt), hash) == 0){
								printf("%s\n", pswd);
								return 0;
							}
					}
				}
			}
		}
	}
	printf("couldnt crack the password\n");
	return 1;
}
