#include "tests_rt.h"

static int tests_light1(void)
{
	RUN_RT("tests_light/light1", "pars: light error\n", 0)
}
static int tests_light2(void)
{
	RUN_RT("tests_light/light2", "pars: light error\n", 0)
}
static int tests_light3(void)
{
	RUN_RT("tests_light/light3", "pars: light error\n", 0)
}
static int tests_light4(void)
{
	RUN_RT("tests_light/light4", "pars: light error\n", 0)
}
static int tests_light5(void)
{
	RUN_RT("tests_light/light5", "pars: light error\n", 0)
}
static int tests_light6(void)
{
	RUN_RT("tests_light/light6", "pars: light error\n", 0)
}
static int tests_light7(void)
{
	RUN_RT("tests_light/light7", "pars: light error\n", 0)
}
static int tests_light8(void)
{
	RUN_RT("tests_light/light8", "pars: light error\n", 0)
}
static int tests_light9(void)
{
	RUN_RT("tests_light/light9", "pars: light error\n", 0)
}
static int tests_light10(void)
{
	RUN_RT("tests_light/light10", "pars: light error\n", 0)
}
int	tests_light_launcher(void)
{
	t_unit_test *testlist;

	testlist = NULL;
	write(2, "\033[36m===============[PARS LIGHT]==============>\033[0m\n",
			sizeof("\033[36m===============[PARS LIGHT]==============>\033[0m\n"));
	load_test(&testlist, "light1 void arg", 0, &tests_light1);
	load_test(&testlist, "light2 5 arg", 0, &tests_light2);
	load_test(&testlist, "light3 Space after fun", 0, &tests_light3);
	load_test(&testlist, "light4 2nd parameter false", 0, &tests_light4);
	load_test(&testlist, "light5 one virgul more", 0, &tests_light5);
	load_test(&testlist, "light6 SPHERE0.5", 0, &tests_light6);
	load_test(&testlist, "light7 light0.5", 0, &tests_light7);
	load_test(&testlist, "light8 EAFF arg 4", 0, &tests_light8);
	load_test(&testlist, "light9 (1,2,)3,4)", 0, &tests_light9);
	load_test(&testlist, "light10 (1,2,(3,4)", 0, &tests_light10);
	return (launch_tests(&testlist));
}
