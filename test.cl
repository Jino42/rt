__kernel void test(__global int *img)
{
	int w = 1280;
	int x = get_global_id(0) % w;
	int y = get_global_id(0) / w;

	img[x + y * w] = 0xFF00FF;
}
