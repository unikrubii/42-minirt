#include "minirt.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->img.addr + (y * mlx->img.line_length + x * (mlx->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	put_bg(t_mlx mlx)
{
	// Image

	// const int image_width = 256;
	// const int image_height = 256;

	// Render
	printf("P3\n%d %d\n255\n", WIDTH, HEIGHT);

	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			float r = (float)(i) / (float)(WIDTH - 1);
			float g = (float)(j) / (float)(HEIGHT - 1);
			float b = (float)0.25f;

			int ir = (255.999f * (float)r);
			int ig = (255.999f * (float)g);
			int ib = (255.999f * (float)b);

			// printf("%d %d %d\n", ir, ig, ib);
			my_mlx_pixel_put(&mlx, i, j, ir << 16 | ig << 8 | ib);
		}
	}
}

int	main2()
{
	t_mlx	mlx;
	
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 800, 600, "RT");
	mlx.img.img = mlx_new_image(mlx.mlx, 800, 600);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bits_per_pixel, &mlx.img.line_length, &mlx.img.endian);
	put_bg(mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_loop(mlx.mlx);
	return (0);
}
