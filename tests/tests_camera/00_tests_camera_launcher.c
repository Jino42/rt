#include "tests_rt.h"

static int tests_camera1(void)
{
	RUN_RT("tests_camera/camera1", "pars: camera error\n", 0)
}
static int tests_camera2(void)
{
	RUN_RT("tests_camera/camera2", "pars: camera error\n", 0)
}
static int tests_camera3(void)
{
	RUN_RT("tests_camera/camera3", "pars: camera error\n", 0)
}
static int tests_camera4(void)
{
	RUN_RT("tests_camera/camera4", "pars: camera error\n", 0)
}
static int tests_camera5(void)
{
	RUN_RT("tests_camera/camera5", "pars: camera error\n", 0)
}
static int tests_camera6(void)
{
	RUN_RT("tests_camera/camera6", "pars: camera error\n", 0)
}
static int tests_camera8(void)
{
	RUN_RT("tests_camera/camera8", "pars: camera error\n", 0)
}
static int tests_camera9(void)
{
	RUN_RT("tests_camera/camera9", "pars: camera error\n", 0)
}

int	tests_camera_launcher(void)
{
	t_unit_test *testlist;

	testlist = NULL;
	write(2, "\033[36m===============[PARS CAMERA]==============>\033[0m\n",
			sizeof("\033[36m===============[PARS CAMERA]==============>\033[0m\n"));
	load_test(&testlist, "camera 3 basic param", 0, &tests_camera1);
	load_test(&testlist, "camera2 4 vec param", 0, &tests_camera2);
	load_test(&testlist, "camera3 2 vec param", 0, &tests_camera3);
	load_test(&testlist, "camera4 void", 0, &tests_camera4);
	load_test(&testlist, "camera5 4 vec param", 0, &tests_camera5);
	load_test(&testlist, "camera6 2 basic vec param", 0, &tests_camera6);
	load_test(&testlist, "camera8 space betwin cam & deb param", 0, &tests_camera8);
	load_test(&testlist, "camera9 space after vec.z", 0, &tests_camera9);
	return (launch_tests(&testlist));
}
