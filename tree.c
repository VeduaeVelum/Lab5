#include "tree.h"

struct tree *root = { NULL };

void check_flag(void)
{
	int element = 0, element1;
	bool flag;
	do
	{
		do
		{
			printf("\t\t\tYour choice: ");
			element1 = scanf("%d", &element);
			__fpurge(stdin);
			if (element < 0 || element > NUMBER_OF_COMANDS || element1 != MIN_TREE_SIZE)
			{
				printf("\n\tInvalid input! Try again, look to the hint\n");
			}
		} while (element < 0 || element > NUMBER_OF_COMANDS || element1 != MIN_TREE_SIZE);
		switch (element)
		{
		case 1:
			flag = create_tree();
			break;
		case 2:
			flag = adding_nodes();
			break;
		case 3:
			flag = read_tree_from_file();
			if (flag == true) printf("\tFile was successfully read\n");
			break;
		case 4:
			flag = show_tree(root, 0);
			break;
		case 5:
			flag = print_tree(root);
			if (flag == true) printf("\tFile was successfully created\n");
			break;
		case 6:
			determine_number_of_nodes();
			break;
		case 0:
			flag = delete_tree(root);
			element1 = -1;
			printf("\nThanks for work with us\n");
			break;
		}
	} while (element1 != -1);
}
bool create_tree(void)
{
	bool flag;
	if (root != NULL)
	{
		printf("\tTree has been already created, do you want to create new?(Y/N): ");
		flag = check_letter();
		if (flag == true) delete_tree(root);
		else
		{
			printf("\tChoose another operation\n");
			return false;
		}
	}
	if (!(root = (struct tree*)calloc(1, sizeof(struct tree))) ||
		!(root->information = (char*)calloc((STRING_LENGTH + 1), sizeof(char))))
	{
		printf("\tMemory isn't allocated\n");
		exit(-1);
	}
	printf("\tInput information into the tree's root: ");
	input_string(root->information);
	return true;
}
bool adding_nodes(void)
{
	int nodes_number, i;
	char *string;
	if (root == NULL)
	{
		printf("\tTree didn't created, choose the first operation please\n");
		return false;
	}
	if (!(string = (char*)calloc((STRING_LENGTH + 1), sizeof(char))))
	{
		printf("Memory isn't allocated\n");
		delete_tree(root);
		exit(-1);
	}
	printf("\tInput a number of nodes to add: ");
	nodes_number = input_number_nodes();
	for (i = 0; i < nodes_number; i++)
	{
		printf("\tInput an information to add to the tree: ");
		input_string(string);
		insert_node(string, &root);
	}
	free(string);
	return true;
}
bool read_tree_from_file(void)
{
	FILE *f;
	char *string;
	if (root != NULL)
	{
		printf("\tYou have already input information to the tree earlier\n");
		return false;
	}
	if (!(f = fopen("tree.txt", "r+t")))
	{
		printf("\tFile couldn't be opened, maybe it didn't exist\n");
		return false;
	}
	if (!(string = (char*)calloc(STRING_LENGTH, sizeof(char))))
	{
		printf("Memory isn't allocated\n");
		delete_tree(root);
		exit(-1);
	}
	while (fgets(string, STRING_LENGTH, f))	insert_node(string, &root);
	fclose(f);
	free(string);
	return true;
}
bool show_tree(struct tree *root, int temp)
{
	int i;
	if (root == NULL)	return true;
	else
	{
		show_tree(root->left_node, ++temp);
		for (i = 0; i < temp; ++i) printf("|");
		printf("%s\n", root->information);
		temp--;
	}
	show_tree(root->right_node, ++temp);
	return true;
}
bool print_tree(struct tree *root)
{
	if (root == NULL)	return true;
	else
	{
		static FILE *f;
		if (!(f = fopen("tree.txt", "a+t")))
		{
			printf("\tFile couldn't be opened\n");
			return false;
		}
		fputs(root->information, f);
		fclose(f);
		print_tree(root->left_node);
		print_tree(root->right_node);
	}
	return true;
}
bool determine_number_of_nodes(void)
{
	int nodes_number = 0, tree_level;
	static int element = 0;
	if (root == NULL)
	{
		printf("\tTree didn't create\n");
		return false;
	}
	define_tree_levels(root, MIN_TREE_SIZE);
	printf("\tInput level of the tree: ");
	tree_level = input_number_nodes();
	nodes_number = calculate_nodes(root, tree_level);
	if ((nodes_number - element) == 0) printf("\tThere are not nodes with %d level\n", tree_level);
	else printf("\tNumber of nodes on %d level are %d\n", tree_level, (nodes_number - element));
	element = nodes_number;
	return true;
}
int calculate_nodes(struct tree *root, int tree_level)
{
	static int nodes_number = 0;
	if (root == NULL)	return nodes_number;
	else
	{
		if (root->key == tree_level)
		{
			nodes_number++;
		}
		calculate_nodes(root->left_node, tree_level);
		calculate_nodes(root->right_node, tree_level);
	}
}
bool insert_node(char *string, struct tree **root)
{
	int compare_result;
	if ((*root) == NULL)
	{
		if (!((*root) = (struct tree*)calloc(1, sizeof(struct tree))) || 
			!((*root)->information = (char*)calloc(STRING_LENGTH, sizeof(char))))
		{
			printf("Memory isn't allocated\n");
			delete_tree(*root);
			exit(-1);
		}
		strcpy((*root)->information, string);
		(*root)->left_node = (*root)->right_node = NULL;
		return true;
	}
	compare_result = strcmp((*root)->information, string);
	(compare_result > 0) ? insert_node(string, &(*root)->right_node) : insert_node(string, &(*root)->left_node);
	return true;
}
int define_tree_levels(struct tree *root, int temp)
{
	if (root == NULL)	return 0;
	else
	{
		root->key = temp++;
		define_tree_levels(root->left_node, temp);
		define_tree_levels(root->right_node, temp);
		return temp;
	}
}
bool delete_tree(struct tree *root)
{
	if (root == NULL) return true;
	delete_tree(root->left_node);
	delete_tree(root->right_node);
	free(root->information);
	free(root);
	return true;
}
bool check_letter(void)
{
	char c;
	do
	{
		scanf("%c", &c);
		__fpurge(stdin);
		if (c == 'Y' || c == 'y') return true;
		else if (c == 'N' || c == 'n') return false;
		else printf("\tIncorrect input, try again: ");
	} while (1);
}
void input_string(char *string)
{
	int j, n, temp = NULL;
	do
	{
		fgets(string, STRING_LENGTH, stdin);
		__fpurge(stdin);
		n = (strlen(string) - 1);
		if (string[0] == '\n' || string[0] == '\0')
		{
			printf("\tEmpty input is forbidden, try again: ");
			continue;
		}
		for (j = 0; j < n; j++)
		{
			if (string[j] == ' ') temp++;
		}
		if (temp == n)
		{
			printf("\tEmpty input is forbidden, try again: ");
			continue;
		}
		else break;
	} while (1);
}
int input_number_nodes(void)
{
	int element, element1;
	do
	{
		element1 = scanf("%d", &element);
		__fpurge(stdin);
		if (element1 != 1 || element < MIN_TREE_SIZE || element > MAX_TREE_SIZE)
		{
			printf("\tIncorrect input! Use one number from %d to %d: ", MIN_TREE_SIZE, MAX_TREE_SIZE);
		}
	} while (element1 != 1 || element < MIN_TREE_SIZE || element > MAX_TREE_SIZE);
	return element;
}
