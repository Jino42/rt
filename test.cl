#include "matrix.hl"
#include "rt.hl"

__kernel void test(__global int *img,
					__global void *obj,
					unsigned long long mem_size_obj)
{

	(void)obj;
	(void)mem_size_obj;
	int w = 1280;
	int x = get_global_id(0) % w;
	int y = get_global_id(0) / w;

	if (x == 0 && y == 0)
	{
		t_obj *obj = obj;
		t_vector v = obj->position;
		printf("Vector position id : %i : %.2f %.2f %.2f\n",
			   obj->id,
			   v.x, v.y, v.z);
		int i = 0;
		printf("Mem_obj : \n");
		while (i++ < 100)
			printf("[%i]", *((int*)obj+i));
		printf("\nMem img : \n");
		i = 0;
		while (i++ < 20)
			printf("[%x]", img[i + 1280 * 700]);
		printf("\n%llu\n", mem_size_obj);
	}
	img[x + y * w] = 0xFF00FF;
}
