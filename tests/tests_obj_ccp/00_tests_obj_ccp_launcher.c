#include "tests_rt.h"

static int tests_obj_ccp1(void)
{
	RUN_RT("tests_obj_ccp/ccp1", "pars: cylinder error\n", 0)
}
static int tests_obj_ccp2(void)
{
	RUN_RT("tests_obj_ccp/ccp2", "pars: cylinder error\n", 0)
}
static int tests_obj_ccp3(void)
{
	RUN_RT("tests_obj_ccp/ccp3", "pars: sphere error\n", 0)
}
static int tests_obj_ccp4(void)
{
	RUN_RT("tests_obj_ccp/ccp4", "pars: paraboloid error\n", 0)
}
static int tests_obj_ccp5(void)
{
	RUN_RT("tests_obj_ccp/ccp5", "pars: cone error\n", 0)
}
static int tests_obj_ccp6(void)
{
	RUN_RT("tests_obj_ccp/ccp6", "pars: plan error\n", 0)
}
static int tests_obj_ccp7(void)
{
	RUN_RT("tests_obj_ccp/ccp7", "pars: ellipsoid error\n", 0)
}
static int tests_obj_ccp8(void)
{
	RUN_RT("tests_obj_ccp/ccp8", "pars: name fun error\n", 0)
}
static int tests_obj_ccp9(void)
{
	RUN_RT("tests_obj_ccp/ccp9", "pars: transform error\n", 0)
}
static int tests_obj_ccp10(void)
{
	RUN_RT("tests_obj_ccp/ccp10", "pars: transform error\n", 0)
}
static int tests_obj_ccp11(void)
{
	RUN_RT("tests_obj_ccp/ccp11", "pars: transform error\n", 0)
}
static int tests_obj_ccp12(void)
{
	RUN_RT("tests_obj_ccp/ccp12", "pars: missing light\n", 0)
}
static int tests_obj_ccp13(void)
{
	RUN_RT("tests_obj_ccp/ccp13", "pars: transform error\n", 0)
}
static int tests_obj_ccp14(void)
{
	RUN_RT("tests_obj_ccp/ccp14", "pars: transform error\n", 0)
}
static int tests_obj_ccp15(void)
{
	RUN_RT("tests_obj_ccp/ccp15", "pars: transform error\n", 0)
}
static int tests_obj_ccp16(void)
{
	RUN_RT("tests_obj_ccp/ccp16", "pars: transform error\n", 0)
}
static int tests_obj_ccp17(void)
{
	RUN_RT("tests_obj_ccp/ccp17", "pars: transform error\n", 0)
}
static int tests_obj_ccp18(void)
{
	RUN_RT("tests_obj_ccp/ccp18", "pars: transform error\n", 0)
}
static int tests_obj_ccp19(void)
{
	RUN_RT("tests_obj_ccp/ccp19", "pars: transform error\n", 0)
}
static int tests_obj_ccp20(void)
{
	RUN_RT("tests_obj_ccp/ccp20", "pars: transform error\n", 0)
}
int	tests_obj_ccp_launcher(void)
{
	t_unit_test *testlist;

	testlist = NULL;
	write(2, "\033[36m===============[PARS CCP]==============>\033[0m\n",
			sizeof("\033[36m===============[PARS CCP]==============>\033[0m\n"));
	load_test(&testlist, "ccp1 cylinder only 6 param", 0, &tests_obj_ccp1);
	load_test(&testlist, "ccp2 two cylinder coll", 0, &tests_obj_ccp2);
	load_test(&testlist, "ccp3 sphere", 0, &tests_obj_ccp3);
	load_test(&testlist, "ccp4 paraboloid", 0, &tests_obj_ccp4);
	load_test(&testlist, "ccp5 cone", 0, &tests_obj_ccp5);
	load_test(&testlist, "ccp6 plan", 0, &tests_obj_ccp6);
	load_test(&testlist, "ccp7 ellipsoid", 0, &tests_obj_ccp7);
	load_test(&testlist, "ccp8 name error", 0, &tests_obj_ccp8);
	load_test(&testlist, "ccp9 transform 4arg", 0, &tests_obj_ccp9);
	load_test(&testlist, "ccp10 transform light", 0, &tests_obj_ccp10);
	load_test(&testlist, "ccp11 transform camera", 0, &tests_obj_ccp11);
	load_test(&testlist, "ccp12 missing light", 0, &tests_obj_ccp12);
	load_test(&testlist, "ccp13", 0, &tests_obj_ccp13);
	load_test(&testlist, "ccp14", 0, &tests_obj_ccp14);
	load_test(&testlist, "ccp15", 0, &tests_obj_ccp15);
	load_test(&testlist, "ccp16", 0, &tests_obj_ccp16);
	load_test(&testlist, "ccp17", 0, &tests_obj_ccp17);
	load_test(&testlist, "ccp18", 0, &tests_obj_ccp18);
	load_test(&testlist, "ccp19", 0, &tests_obj_ccp19);
	load_test(&testlist, "ccp20", 0, &tests_obj_ccp20);
	return (launch_tests(&testlist));
}
