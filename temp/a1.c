#include "a1.h"

Restaurant *initialize_restaurant(char *name)
{
	int i = 0;
	for (i = 0; i != '\0'; i++)
	{
		i++;
	}
	Restaurant *rest = malloc(sizeof(Restaurant));

	char *temp = (char *)(malloc(sizeof(char) * (strlen(name) + 1)));

	strcpy(temp, name);
	// for(int j=0;j<i;j++){
	// 	temp[j] = name[j];
	// }
	// temp[i] = '\0';

	// printf("%s", temp);
	Queue *tempQ = (Queue *)malloc(sizeof(Queue));
	tempQ->head = NULL;
	tempQ->tail = NULL;

	// Menu *men = (Menu *)malloc(sizeof(Menu));
	Menu *men = load_menu(MENU_FNAME);

	rest->name = temp;
	rest->menu = men;
	rest->pending_orders = tempQ;
	rest->num_completed_orders = 0;
	rest->num_pending_orders = 0;

	return rest;
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
			// printf("%s",lines[linesCount]);
			linesCount++;
		}
		// printf("helaaaaaaaaaaaaaaaaa2lo\n");
	}
	// printf("hello\n");
	// printf("%d", linesCount);
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
		// printf(token);

		prices[i] =  atof(token);


	}
	fclose(f);
	men->num_items = linesCount;
	men->item_codes = codes;
	men->item_names = names;
	men->item_cost_per_unit = prices;
	for(int y=0; y<linesCount;y++){
		free(lines[y]);
	}
	free(lines);
	return men;
}
Order *build_order(char *items, char *quantities)
{
	Order *order = malloc(sizeof(Order));
	int num_items = 1;
	for (int i = 0; quantities[i] != '\0'; i++)
	{
		// count the number of commas
		if (quantities[i] == ',')
		{
			num_items++;
		}
	}
	char **codes = (char **)malloc(sizeof(char *) * num_items);
	int *quants = (int *)malloc(sizeof(int) * num_items);
	int j = 0;
	for (int i = 0; i < strlen(items); i += 2)
	{
		codes[j] = malloc(sizeof(char) * ITEM_CODE_LENGTH);
		codes[j][0] = items[i];
		codes[j][1] = items[(i + 1)];
		codes[j][2] = '\0';
		j++;
		// printf("%s", codes[i]);
	}
	// to use the strtok function i need a char[] so i cast my char* to a char[]
	char quanttys[strlen(quantities) + 1];
	strcpy(quanttys, quantities);
	int i = 0;
	char *p = strtok(quanttys, ",");

	while (p != NULL)
	{

		quants[i] = atoi(p);
		// printf("%d\n", atoi(p));
		p = strtok(NULL, ",");
		i++;
	}

	// for (i = 0; i < num_items; i++)
	// {

	//     printf("%d\n", quants[i]);
	//     printf("%s\n", (codes[i]));

	// }
	order->item_codes = codes;
	order->item_quantities = quants;
	order->num_items = num_items;
	return order;

}

double get_item_cost(char *item_code, Menu *menu)
{
	int count = 0;
	for (int i = 0; strcmp(item_code, menu->item_codes[i]) != 0; i++)
	{
		count++;
	}
	return menu->item_cost_per_unit[count];
}
double get_order_subtotal(Order *order, Menu *menu)
{
	// go through all the codes in order then find the prince of them using menu and get_item_cost then multiply by the number of them
	int num_items = order->num_items;
	double total = 0;
	for (int i = 0; i < num_items; i++)
	{
		double item_cost = get_item_cost(order->item_codes[i], menu);
		total += item_cost * (order->item_quantities[i]);
	}
	return total;
}

double get_order_total(Order *order, Menu *menu)
{
	double total = get_order_subtotal(order, menu);
	total += get_order_subtotal(order, menu) * (TAX_RATE / 100.0);
	return total;
}
void enqueue_order(Order *order, Restaurant *restaurant)
{
	QueueNode *qn = (QueueNode *)malloc(sizeof(QueueNode));
	qn->order = order;
	qn->next = NULL;

	QueueNode *q_tail = restaurant->pending_orders->tail;
	QueueNode *q_head = restaurant->pending_orders->head;
	if (q_tail == NULL)
	{
		restaurant->pending_orders->head = restaurant->pending_orders->tail = qn;
	}
	else
	{
		restaurant->pending_orders->tail->next = qn;
		restaurant->pending_orders->tail = qn;
	}
	restaurant->num_pending_orders++;
}
Order *dequeue_order(Restaurant *restaurant)
{
	// given that queue will always have a head and tail
	QueueNode *node = restaurant->pending_orders->head;
	Order *order = node->order;
	if (restaurant->pending_orders->head == restaurant->pending_orders->tail)
	{
		restaurant->pending_orders->head = restaurant->pending_orders->tail = NULL;
		free(node);
	}
	else
	{
		restaurant->pending_orders->head = node->next;
		free(node);
	}
	restaurant->num_completed_orders++;
	restaurant->num_pending_orders--;
	return order;
}

int get_num_completed_orders(Restaurant *restaurant)
{
	return restaurant->num_completed_orders;
}
int get_num_pending_orders(Restaurant *restaurant)
{
	return restaurant->num_pending_orders;
}

void clear_order(Order **order)
{
	// need to clear item_codes which is an array of char arrays so need to clear each of those
	// item quantites need only one clear

	int num_elements = (*order)->num_items;

	for (int i = 0; i < num_elements; i++)
	{
		free((*order)->item_codes[i]);
		(*order)->item_codes[i] = NULL;
	}
	free((*order)->item_codes);
	(*order)->item_codes = NULL;
	free((*order)->item_quantities);
	(*order)->item_quantities = NULL;
	free(*order);
	*order = NULL;
}
void clear_menu(Menu **menu)
{
	int num_itemss = (*menu)->num_items;
	for (int i = 0; i < num_itemss; i++)
	{
		free((*menu)->item_codes[i]);
		(*menu)->item_codes[i] = NULL;
		free((*menu)->item_names[i]);
		(*menu)->item_names[i] = NULL;
	}
	free((*menu)->item_codes);
	(*menu)->item_codes = NULL;
	free((*menu)->item_names);
	(*menu)->item_names = NULL;

	free((*menu)->item_cost_per_unit);
	(*menu)->item_cost_per_unit = NULL;
	free(*menu);
	// (*menu)->num_items = NULL;
}

void close_restaurant(Restaurant **restaurant)
{

	clear_menu(&((*restaurant)->menu));

	free((*restaurant)->name);
	// free((*restaurant)->menu);

	// while there are still elements in the pending orders queue
	while ((*restaurant)->pending_orders->head != NULL)
	{
		QueueNode *node = (*restaurant)->pending_orders->head;
		Order **order = &(node->order);

		(*restaurant)->pending_orders->head = node->next;

		// clear the order inside of the queue nodes
		clear_order(order);
		free(node);
	}
	// set the pending orders to zero just in case
	(*restaurant)->num_pending_orders = 0;

	// free the pending orders queue
	free((*restaurant)->pending_orders);
	free((*restaurant));
}

void print_menu(Menu *menu)
{
	fprintf(stdout, "--- Menu ---\n");
	for (int i = 0; i < menu->num_items; i++)
	{
		fprintf(stdout, "(%s) %s: %.2f\n",
				menu->item_codes[i],
				menu->item_names[i],
				menu->item_cost_per_unit[i]);
	}
}

void print_order(Order *order)
{
	for (int i = 0; i < order->num_items; i++)
	{
		fprintf(
			stdout,
			"%d x (%s)\n",
			order->item_quantities[i],
			order->item_codes[i]);
	}
}

void print_receipt(Order *order, Menu *menu)
{
	for (int i = 0; i < order->num_items; i++)
	{
		double item_cost = get_item_cost(order->item_codes[i], menu);
		fprintf(
			stdout,
			"%d x (%s)\n @$%.2f ea \t %.2f\n",
			order->item_quantities[i],
			order->item_codes[i],
			item_cost,
			item_cost * order->item_quantities[i]);
	}
	double order_subtotal = get_order_subtotal(order, menu);
	double order_total = get_order_total(order, menu);

	fprintf(stdout, "Subtotal: \t %.2f\n", order_subtotal);
	fprintf(stdout, "               -------\n");
	fprintf(stdout, "Tax %d%%: \t$%.2f\n", TAX_RATE, order_total);
	fprintf(stdout, "              ========\n");
}
