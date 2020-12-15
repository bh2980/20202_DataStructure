#include <stdio.h>
#include <string.h>

int main(void)
{	
	char name[50];
	int age;
	char sex;
	char *namep;

	namep = name;

	while(1){
		int i = 0, j = 0;
		char stop[5] = "stop";

		printf("Provide your special information\n");
		printf("¢º Name : ");
		gets(name);

		for(i=0; i<5; i++){
			if(tolower(name[i]) == stop[i]){
				j++;
			}
		}

		if(j==5) break;
	
		printf("¢º Age : ");
		scanf("%d", &age);
		getchar();
	
		printf("¢º Sex (M/F) : ");
		scanf("%c", &sex);
		getchar();
		sex = toupper(sex);

		
		for(i=0; i < strlen(name);i++){
			if(*(namep+i) == ' '){
				*(namep+i) = '\0';
				break;
			}
		}

		printf("Your name is %s %s, your age is %d, your sex is %c\n\n", namep+i+1, namep, age, sex);
	}

	return 0;
}