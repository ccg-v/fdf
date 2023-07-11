/* gcc -Wall -Wextra -Werror -I ./minilibx_macos  test_rectangle_put.c 
    -L ./minilibx_macos -lmlx -framework OpenGL -framework AppKit */

#include <stdlib.h>
#include <stdio.h>
#include "./minilibx_macos/mlx.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define MLX_ERROR 1

#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00
#define WHITE_PIXEL 0XFFFFFF

typedef struct s_data
{
    void	*mlx_ptr;
    void	*win_ptr;
}	t_data;

typedef struct s_rect
{
    int	x;
    int	y;
    int width;
    int height;
    int color;
}	t_rect;

int render_rect(t_data *data, t_rect rect)
{
    int	i;
    int j;

    if (data->win_ptr == NULL)
        return (1);
    i = rect.y;
    while (i < rect.y + rect.height)
    {
        j = rect.x;
        while (j < rect.x + rect.width)
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, rect.color);
        ++i;
    }
    return (0);
}

void	render_background(t_data *data, int color)
{
    int	i;
    int	j;

    if (data->win_ptr == NULL)
        return ;
    i = 0;
    while (i < WINDOW_HEIGHT)
    {
        j = 0;
        while (j < WINDOW_WIDTH)
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, color);
        ++i;
    }
}

int	render(t_data *data)
{
    render_background(data, WHITE_PIXEL);
    render_rect(data, (t_rect){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, GREEN_PIXEL});
    render_rect(data, (t_rect){0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, RED_PIXEL});

    return (0);
}

int	main(void)
{
    t_data	data;

    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (MLX_ERROR);
    data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
                                "my window");
    if (data.win_ptr == NULL)
    {
        free(data.win_ptr);
        return (MLX_ERROR);
    }

    /* Setup hooks */ 
    mlx_loop_hook(data.mlx_ptr, &render, &data);
    // mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

    mlx_loop(data.mlx_ptr);

    /* we will exit the loop if there's no window left, and execute this code */
    // mlx_destroy_display(data.mlx_ptr);
    free(data.mlx_ptr);
}