
#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define WINDOW_TITLE "Sudoku"
#define IMG_WiDTH 100
#define IMG_HEIGHT 100

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
    int     life;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    char	**sudoku;
	void	*img_1;
	void	*img_1s;
	void	*img_2;
	void	*img_2s;
	void	*img_3;
	void	*img_3s;
	void	*img_4;
	void	*img_4s;
	void	*img_5;
	void	*img_5s;
	void	*img_6;
	void	*img_6s;
	void	*img_7;
	void	*img_7s;
	void	*img_8;
	void	*img_8s;
	void	*img_9;
	void	*img_9s;
	void	*img_background;
	void	*img_backgroundtile;
	void	*img_backgroundtiles;
    int     selected_x;
    int     selected_y;
}			t_data;

// function to creat the images
void	creat_images(t_data *data)
{
	int	i;
	int	j;

	i = IMG_HEIGHT;
	j = IMG_WiDTH;
	data->img_1 = mlx_xpm_file_to_image(data->mlx_ptr, "images/1.xpm", &i, &j);
	data->img_1s = mlx_xpm_file_to_image(data->mlx_ptr, "images/1s.xpm", &i,
		&j);
	data->img_2 = mlx_xpm_file_to_image(data->mlx_ptr, "images/2.xpm", &i, &j);
	data->img_2s = mlx_xpm_file_to_image(data->mlx_ptr, "images/2s.xpm", &i,
		&j);
	data->img_3 = mlx_xpm_file_to_image(data->mlx_ptr, "images/3.xpm", &i, &j);
	data->img_3s = mlx_xpm_file_to_image(data->mlx_ptr, "images/3s.xpm", &i,
		&j);
	data->img_4 = mlx_xpm_file_to_image(data->mlx_ptr, "images/4.xpm", &i, &j);
	data->img_4s = mlx_xpm_file_to_image(data->mlx_ptr, "images/4s.xpm", &i,
		&j);
	data->img_5 = mlx_xpm_file_to_image(data->mlx_ptr, "images/5.xpm", &i, &j);
	data->img_5s = mlx_xpm_file_to_image(data->mlx_ptr, "images/5s.xpm", &i,
		&j);
	data->img_6 = mlx_xpm_file_to_image(data->mlx_ptr, "images/6.xpm", &i, &j);
	data->img_6s = mlx_xpm_file_to_image(data->mlx_ptr, "images/6s.xpm", &i,
		&j);
	data->img_7 = mlx_xpm_file_to_image(data->mlx_ptr, "images/7.xpm", &i, &j);
	data->img_7s = mlx_xpm_file_to_image(data->mlx_ptr, "images/7s.xpm", &i,
		&j);
	data->img_8 = mlx_xpm_file_to_image(data->mlx_ptr, "images/8.xpm", &i, &j);
	data->img_8s = mlx_xpm_file_to_image(data->mlx_ptr, "images/8s.xpm", &i,
		&j);
	data->img_9 = mlx_xpm_file_to_image(data->mlx_ptr, "images/9.xpm", &i, &j);
	data->img_9s = mlx_xpm_file_to_image(data->mlx_ptr, "images/9s.xpm", &i,
		&j);
	data->img_backgroundtile = mlx_xpm_file_to_image(data->mlx_ptr,
		"images/backgroundtile.xpm", &i, &j);
	data->img_backgroundtiles = mlx_xpm_file_to_image(data->mlx_ptr,
		"images/backgroundtiles.xpm", &i, &j);
	i = WINDOW_HEIGHT;
	j = WINDOW_WIDTH;
	data->img_background = mlx_xpm_file_to_image(data->mlx_ptr,
		"images/sudoku.xpm", &i, &j);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_check(char **sudoku, int row, int col, char c)
{
	int	i;
	int	j;

	i = 0;
	while (i < 9)
	{
		if (sudoku[row][i] == c)
			return (0);
		i++;
	}
	i = 0;
	while (i < 9)
	{
		if (sudoku[i][col] == c)
			return (0);
		i++;
	}
	i = (row / 3) * 3;
	while (i < (row / 3) * 3 + 3)
	{
		j = (col / 3) * 3;
		while (j < (col / 3) * 3 + 3)
		{
			if (sudoku[i][j] == c)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_print_sudoku(char **sudoku)
{
	int	i;
	int	j;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			if ((j % 3 == 0 || j % 3 == 0) && j != 0)
			{
				ft_putchar('|');
				ft_putchar(' ');
			}
			ft_putchar(sudoku[i][j]);
			if (j != 8)
				ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
		if (i % 3 == 0 && i != 9)
			write(1, "------+-------+------\n", 22);
	}
}

int	ft_sudoku(char **sudoku)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			if (sudoku[i][j] == '.')
			{
				k = 0;
				while (k < 9)
				{
					if (ft_check(sudoku, i, j, k + '1'))
						// 1 to 9 instead of 0 to 8
					{
						sudoku[i][j] = k + '1';
						if (ft_sudoku(sudoku))
							return (1);
						else
							sudoku[i][j] = '.';
					}
					k++;
				}
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	fill_sudoku(char **sudoku)
{
	int		i;
	int		j;
	char	**str;

	str = (char *[9]){".........", ".........", ".........", ".........",
		".........", ".........", ".........", ".........", "........."};
	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			sudoku[i][j] = str[i][j];
			j++;
		}
		i++;
	}
}

void	put_number_img(t_data *data, char **ft_sudoku)
{
	int	i;
	int	j;
	int	x;
	int	y;

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_background, 0, 0);
	y = 20;
	for (i = 0; i < 9; i++) // Use for-loop for better readability
	{
		x = 20;
		for (j = 0; j < 9; j++)
		{
			if (ft_sudoku[i][j] == '1')
            {
                if (i == data->selected_y && j == data->selected_x)
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_1s, x, y);
                else
				    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					    data->img_1, x, y);
            }
			else if (ft_sudoku[i][j] == '2')
            {
                if (i == data->selected_y && j == data->selected_x)
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_2s, x, y);
                else
				    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					    data->img_2, x, y);
            }
			else if (ft_sudoku[i][j] == '3')
            {
                if (i == data->selected_y && j == data->selected_x)
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_3s, x, y);
                else
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_3, x, y);
            }
            else if (ft_sudoku[i][j] == '4')
            {
                if (i == data->selected_y && j == data->selected_x)
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_4s, x, y);
                else
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_4, x, y);
            }
            else if (ft_sudoku[i][j] == '5')
            {
                if (i == data->selected_y && j == data->selected_x)
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_5s, x, y);
                else
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_5, x, y);
            }
            else if (ft_sudoku[i][j] == '6')
            {
                if (i == data->selected_y && j == data->selected_x)
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_6s, x, y);
                else
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_6, x, y);
            }
            else if (ft_sudoku[i][j] == '7')
            {
                if (i == data->selected_y && j == data->selected_x)
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_7s, x, y);
                else
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_7, x, y);
            }
            else if (ft_sudoku[i][j] == '8')
            {
                if (i == data->selected_y && j == data->selected_x)
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_8s, x, y);
                else
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_8, x, y);
            }
            else if (ft_sudoku[i][j] == '9')
            {
                if (i == data->selected_y && j == data->selected_x)
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_9s, x, y);
                else
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_9, x, y);
            }
            else if (ft_sudoku[i][j] == '.')
            {
                if (i == data->selected_y && j == data->selected_x)
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, 
                        data->img_backgroundtiles, x + 0, y + 10);
                else
                    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                        data->img_backgroundtile, x, y);
            }
			x += IMG_WiDTH + 8;
		}
		y += IMG_HEIGHT + 8;
	}
}

int	safeexit(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
}

int	hook(int keycode, void *param)
{
    t_data	*data;

    data = (t_data *)param;
	if (keycode == 65307)
		safeexit(param);
    if (keycode == 65362)
        data->selected_y -= 1;
    if (keycode == 65364)
        data->selected_y += 1;
    if (keycode == 65361)
        data->selected_x -= 1;
    if (keycode == 65363)
        data->selected_x += 1;
    if (keycode == 65293)
    {
        if (ft_sudoku(data->sudoku))
            ft_print_sudoku(data->sudoku);
        else
            write(1, "No solution\n", 13);
    }
    if (data->selected_x < 0)
        data->selected_x = 0;
    if (data->selected_x > 8)
        data->selected_x = 8;
    if (data->selected_y < 0)
        data->selected_y = 0;
    if (data->selected_y > 8)
        data->selected_y = 8;
    if (keycode == 65436)
    {
        if (ft_check(data->sudoku, data->selected_y, data->selected_x, '1'))
            data->sudoku[data->selected_y][data->selected_x] = '1';
        else
            data->life -= 1;
    }
    if (keycode == 65433)
    {
        if (ft_check(data->sudoku, data->selected_y, data->selected_x, '2'))
            data->sudoku[data->selected_y][data->selected_x] = '2';
        else
            data->life -= 1;
    }
    if (keycode == 65435)
    {
        if (ft_check(data->sudoku, data->selected_y, data->selected_x, '3'))
            data->sudoku[data->selected_y][data->selected_x] = '3';
        else
            data->life -= 1;
    }
    if (keycode == 65430)
    {
        if (ft_check(data->sudoku, data->selected_y, data->selected_x, '4'))
            data->sudoku[data->selected_y][data->selected_x] = '4';
        else
            data->life -= 1;
    }
    if (keycode == 65437)
    {
        if (ft_check(data->sudoku, data->selected_y, data->selected_x, '5'))
            data->sudoku[data->selected_y][data->selected_x] = '5';
        else
            data->life -= 1;
    }
    if (keycode == 65432)
    {
        if (ft_check(data->sudoku, data->selected_y, data->selected_x, '6'))
            data->sudoku[data->selected_y][data->selected_x] = '6';
        else
            data->life -= 1;
    }
    if (keycode == 65429)
    {
        if (ft_check(data->sudoku, data->selected_y, data->selected_x, '7'))
            data->sudoku[data->selected_y][data->selected_x] = '7';
        else
            data->life -= 1;
    }
    if (keycode == 65431)
    {
        if (ft_check(data->sudoku, data->selected_y, data->selected_x, '8'))
            data->sudoku[data->selected_y][data->selected_x] = '8';
        else
            data->life -= 1;
    }
    if (keycode == 65434)
    {
        if (ft_check(data->sudoku, data->selected_y, data->selected_x, '9'))
            data->sudoku[data->selected_y][data->selected_x] = '9';
        else
            data->life -= 1;
    }
    if (keycode == 65438)
        data->sudoku[data->selected_y][data->selected_x] = '.';
    if (keycode == 32)
        fill_sudoku(data->sudoku);
    if (data->life == 0)
    {
        write(1, "Game Over\n", 10);
        safeexit(param);
    }
    put_number_img(data, data->sudoku);
    return (0);
}

int	main(void)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)malloc(sizeof(t_data));
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
		WINDOW_TITLE);
	creat_images(data); // make sure this function initializes images correctly
	data->sudoku = (char **)malloc(sizeof(char *) * 9);
	while (i < 9)
	{
		data->sudoku[i] = (char *)malloc(sizeof(char) * 9);
		i++;
	}
	fill_sudoku(data->sudoku);
    data->selected_x = 0;
    data->selected_y = 0;
    data->life = 3;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_background, 0, 0);
	put_number_img(data, data->sudoku);
	mlx_hook(data->win_ptr, 17, 0, safeexit, data);
    mlx_key_hook(data->win_ptr, hook, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
