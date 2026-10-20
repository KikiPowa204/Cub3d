#include <stdlib.h>
#include <mlx.h>
#include <unistd.h>

int main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	//validity checker part 1
	//parsing
	//validity checker part 2
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "cub3D");
	usleep(1000000);
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
}
