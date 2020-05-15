#include <stdio.h>
#include <string.h>
#include <stdint.h>

void stack_overflows_here();

const char* buffer_long = "This is a long long string";

void stack_overflows_here()
{
	char buffer_short[20];

	strcpy(buffer_short, buffer_long);

	printf("Overflow case run.\n");
}

int main(void)
{
	extern uintptr_t __stack_chk_guard;
	printf("Running stack overflow test program. Canary value: 0x%p\n", __stack_chk_guard);

	stack_overflows_here();

	return 0;
}