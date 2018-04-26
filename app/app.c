#include <stdio.h>

int main(void)
{
	void *str = get_new_page(NULL);
	void *str2 = get_new_page(str);
	return (0);
}