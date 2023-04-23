#include "minirt.h"
#include <stdio.h>

int	main()
{
	// Image

	const int image_width = 256;
	const int image_height = 256;

	// Render
	printf("P3\n%d %d\n255\n", image_width, image_height);

	for (int j = 0; j < image_height; j++)
	{
		for (int i = 0; i < image_width; i++)
		{
			float r = (float)(i) / (float)(image_width-1);
			float g = (float)(j) / (float)(image_height-1);
			float b = (float)0.25f;

			int ir = (255.999f * (float)r);
			int ig = (255.999f * (float)g);
			int ib = (255.999f * (float)b);

			printf("%d %d %d\n", ir, ig, ib);
		}
	}
}
