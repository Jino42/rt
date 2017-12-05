#include "tests_rt.h"

static int	tests_gen_no_file(void)
{
	RUN_RT("np_file", "Votre fichier me pose problème.\n", 0)
}
static int tests_gen_null_file(void)
{
	RUN_RT(NULL, "Votre fichier me pose problème.\n", 0)
}
static int tests_gen_void_file(void)
{
	RUN_RT("void_file", "pars: name error\n", 0)
}
static int tests_gen_ret_file(void)
{
	RUN_RT("ret_file", "pars: name error\n", 0)
}
static int tests_gen_name_error(void)
{
	RUN_RT("name_error_1", "pars: name error\n", 0)
}
static int tests_gen_name_error2(void)
{
	RUN_RT("name_error_2", "pars: name error\n", 0)
}
static int tests_gen_name_error3(void)
{
	RUN_RT("name_error_3", "pars: name error\n", 0)
}
static int tests_gen_name_error4(void)
{
	RUN_RT("name_error_4", "pars: name error\n", 0)
}
static int tests_gen_name_error5(void)
{
	RUN_RT("name_error_4", "pars: name error\n", 0)
}
static int tests_gen_camera1(void)
{
	RUN_RT("camera1", "pars: camera error\n", 0)
}
static int tests_gen_camera2(void)
{
	RUN_RT("camera2", "pars: camera error\n", 0)
}
static int tests_gen_camera3(void)
{
	RUN_RT("camera3", "pars: camera error\n", 0)
}
static int tests_gen_camera4(void)
{
	RUN_RT("camera4", "pars: camera error\n", 0)
}
static int tests_gen_camera5(void)
{
	RUN_RT("camera5", "pars: camera error\n", 0)
}
static int tests_gen_camera6(void)
{
	RUN_RT("camera6", "pars: camera error\n", 0)
}
static int tests_gen_camera7(void)
{
	RUN_RT("camera7", "pars: camera error\n", 0)
}
static int tests_gen_camera8(void)
{
	RUN_RT("camera8", "pars: camera error\n", 0)
}

int	tests_gen_launcher(void)
{
	t_unit_test *testlist;

	testlist = NULL;
	write(2, "\033[36m===============[GEN]==============>\033[0m\n",
			sizeof("\033[36m===============[GEN]==============>\033[0m\n"));
	load_test(&testlist, "no file", 0, &tests_gen_no_file);
	load_test(&testlist, "null file", 0, &tests_gen_null_file);
	load_test(&testlist, "void file", 0, &tests_gen_void_file);
	load_test(&testlist, "ret file", 0, &tests_gen_ret_file);
	load_test(&testlist, "name_error_1", 0, &tests_gen_name_error);
	load_test(&testlist, "name_error_2", 0, &tests_gen_name_error2);
	load_test(&testlist, "name_error_3", 0, &tests_gen_name_error3);
	load_test(&testlist, "name_error_4", 0, &tests_gen_name_error4);
	load_test(&testlist, "name_error_5", 0, &tests_gen_name_error5);
	load_test(&testlist, "camera1", 0, &tests_gen_camera1);
	load_test(&testlist, "camera2", 0, &tests_gen_camera2);
	load_test(&testlist, "camera3", 0, &tests_gen_camera3);
	load_test(&testlist, "camera4", 0, &tests_gen_camera4);
	load_test(&testlist, "camera5", 0, &tests_gen_camera5);
	load_test(&testlist, "camera6", 0, &tests_gen_camera6);
	load_test(&testlist, "camera7", 0, &tests_gen_camera7);
	load_test(&testlist, "camera8", 0, &tests_gen_camera8);
	return (launch_tests(&testlist));
}
