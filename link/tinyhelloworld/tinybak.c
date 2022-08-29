char *str = "Hello World!\n";

void print()
{
	asm(
		"movq $13, %%rdx \n\t" /* number of character*/
		"movq %0, %%rcx \n\t" /* address of str */
		"movq $0, %%rbx\n\t" /* 0 presents stdout */
		"movq $4, %%rax \n\t"
		"int $0x80 \n\t"
		:
		:"r"(str)
		:"rdx", "rcx", "rbx"
	   );

	
}

void exit()
{
	asm("movq $42, %rbx \n\t"
		"movq $1, %rax \n\t"
		"int $0x80 \n\t"
	   );

}


void nomain()
{
	print();
	exit();
}
