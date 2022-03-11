#include "a1.h"

void main(){
	load_menu("menu.txt");
}
Menu *load_menu(char *fname)
{

	Menu *men = malloc(sizeof(Menu));
	FILE *f;

	f = fopen(fname, "r");

	// char str1[40];
	// char str2[30];
	// char str3[30];
	// char ch;
	int max_line_len = ITEM_CODE_LENGTH + MAX_ITEM_NAME_LENGTH;
	char line[256];
	
	int linesCount = 0; // pretty sus way of doing this cuz like since the last line end on the EOF need to add one extra
	char **lines = (char**)malloc(sizeof(char*));

	while (fgets(line, sizeof(line), f))
	{

		if (strlen(line) >= 3)
		{
			// printf("%s\n", line);
			// printf("%d\n", strlen(line));
			
			lines = (char **)realloc(lines, (linesCount+1) * sizeof(char *));
			// printf("h1ello\n");
			lines[linesCount] = (char *)malloc((strlen(line) + 1) * sizeof(char)); // array of all the lines
			strcpy(lines[linesCount], line);
			printf("%s",lines[linesCount]);
			linesCount++;
		}
		// printf("helaaaaaaaaaaaaaaaaa2lo\n");
	}
	// printf("hello\n");
	printf("%d", linesCount);
	fclose(f);
	f = fopen(fname, "r");
	char **codes = malloc(sizeof(char *) * linesCount);
	double *prices = malloc(sizeof(double) * linesCount);
	char **names = malloc(sizeof(char *) * linesCount);

	for (int i = 0; i < linesCount; i++)
	{
		codes[i] = malloc(sizeof(char) * ITEM_CODE_LENGTH);
		names[i] = malloc(sizeof(char) * MAX_ITEM_NAME_LENGTH);

		char* token = strtok(lines[i], MENU_DELIM);

		int start_ind;
		for(start_ind = 0; start_ind < strlen(token);){
			if(token[start_ind] == ' ' && token[start_ind] == '\t' && token[start_ind] == '\n'){
				start_ind++;
			}else{
				break;
			}
		}

		codes[i] = (char*)malloc(strlen(token) - start_ind + 1);
		for(int x = 0; x<2;x++){
			codes[i][x] = token[start_ind+x];
		}
		codes[i][2] = '\0';

		token = strtok(NULL, MENU_DELIM);
		names[i] = malloc(sizeof(char) * strlen(token) +1);
		// for(int x =0; x<strlen(token);i++){
		// 	names[i][x] = token[x];
		// }
		strcpy(names[i], token);
		// printf("%s", names[i]);
		token = strtok(NULL, MENU_DELIM);
		char* num;
		memmove(token, token+1, strlen(token));
		printf(token);

		prices[i] =  atof(token);


	}
	fclose(f);
	men->num_items = linesCount;
	men->item_codes = codes;
	men->item_names = names;
	men->item_cost_per_unit = prices;
}