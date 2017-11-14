#include "matrix.hl"
#include "rt.hl"

__kernel void test(__global int *img,
					__global void *objj,
					unsigned long long mem_size_obj)
{

	(void)mem_size_obj;
	int w = 1280;
	int x = get_global_id(0) % w;
	int y = get_global_id(0) / w;

	if (x == 0 && y == 0)
	{
		__global t_obj *o = (__global t_obj *)objj;
		t_vector v = o->position;
		printf("Vector position id : %i : %.2f %.2f %.2f\n",
			   o->id,
			   v.x, v.y, v.z);
		int i = 0;
		printf("Mem_obj : \n");
//		while (i++ < 100)
//			printf("[%i]", *((char *)(obj+i)));
		printf("\nMem img : \n");
		i = 0;
		while (i++ < 20)
			printf("[%x]", img[i + 1280 * 700]);
		printf("\n%llu\n", mem_size_obj);
	}
	img[x + y * w] = 0xFF00FF;
}
