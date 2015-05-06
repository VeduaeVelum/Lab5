# Lab5
#include "tree.h"

void printf_menu(void);
void check_flag(void);

int main(int argc, char** argv)
{
	printf_menu();
	return 0;
}
void printf_menu(void)
{
	puts("Choose the operation please:");
	puts("                             1 - create tree");
	puts("                             2 - add information to the tree");
	puts("                             3 - read tree from the file");
	puts("                             4 - display tree in console");
	puts("                             5 - print tree");
	puts("                             6 - determine number of nodes");
	puts("                             0 - stop the program");
	check_flag();
}
