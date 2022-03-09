#include "assignment1/a1.h"

int main()
{
   Menu* menu = load_menu("assignment1/menu.txt");
}

Menu *load_menu(char *fname)
{

	Menu *men = malloc(sizeof(Menu));
	FILE *f;

	f = fopen(fname, "r");

	char str1[40];
	char str2[30];
	char str3[30];
	char ch;

	int linesCount = 1; // pretty sus way of doing this cuz like since the last line end on the EOF need to add one extra
	while ((ch = fgetc(f)) != EOF)
	{
		if (ch == '\n')
			linesCount++;
	}
	fclose(f);
	f = fopen(fname, "r");
	char **codes = malloc(sizeof(char *) * linesCount);
	double *prices = malloc(sizeof(double) * linesCount);
	char **names = malloc(sizeof(char *) * linesCount);
	for (int i = 0; i < linesCount; i++)
	{
		codes[i] = malloc(sizeof(char) * ITEM_CODE_LENGTH);
		names[i] = malloc(sizeof(char) * MAX_ITEM_NAME_LENGTH);
	
		fscanf(f, "%[^, ],%[^,],%*c%lf ", codes[i], names[i], &prices[i]); // pretty much goes through and like stops when it sees chars after the ^
		printf("Read String1 |%s|\n", codes[i]);
		printf("Read String2 |%s|\n", names[i]);
		printf("Read String3 |%f|\n", prices[i]);
		// temp[i][0] = 'd';
		codes[i][ITEM_CODE_LENGTH] = '\0';
		names[i][MAX_ITEM_NAME_LENGTH] = '\0';
	}

	men->num_items = linesCount;
	men->item_codes = codes;
	men->item_names = names;
	men->item_cost_per_unit = prices;
}