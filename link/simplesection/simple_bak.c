/*
 * Linux:
 *		gcc -c simple_section.c
 */
int printf (const char * format, ...);
__attribute__((section("FOO"))) int global_init_var = 84;
double global_uninit_var;

void func1 ( int i)
{

	printf("%d\n", i);
}

int main(void)
{
	static int static_var = 45;
	static int static_var2;
	int a= 1;
	int b;
	func1(static_var + static_var2 + a + b);
	return a;

}
