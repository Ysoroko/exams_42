/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:43:00 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/10 14:15:04 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ARG_ERROR "Error: argument"
#define FILE_ERROR "Error: Operation file corrupted"

#define MAIN_ERROR 1
#define MAIN_OK 0

typedef struct s_canvas
{
	int		width;
	int		height;
	char	background_char;
}	t_canvas;

typedef struct s_rectangle
{
	char	r_type;
	float	x_top;
	float	y_top;
	float	x_bottom;
	float	y_bottom;
	float	width;
	float	height;
	float	draw_char;
}	t_rectangle;

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_putendl(char *str, int to_return)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (to_return);
}

/// Print the final result (initial array of strings modified by drawings)
void	ft_print_final_result(char **background)
{
	int	i;

	i = -1;
	while (background[++i])
		ft_putendl(background[i], 0);
}

/// Arg errors and open file:
/// Possible errors:
/// 1) More/less than 1 argument
/// 2) The file cannot be opened (wrong name or fscanf returns NULL)
int ft_check_arg_errors_and_open_file(int argc, char **argv, FILE **file)
{
	if (argc != 2)
		return (ft_putendl(ARG_ERROR, MAIN_ERROR));
	*file = fopen(argv[1], "r");
	if (!*file)
		return (ft_putendl(FILE_ERROR, MAIN_ERROR));
	return (MAIN_OK);
}

/// Possible canvas errors:
/// 1) Width > 300 or width < 1
/// 2) Height > 300 or height < 1
/// (No conditions for background char, could be '\0')
int	ft_check_for_canvas_errors(int width, int height)
{
	if (width > 300 || width < 1)
		return (MAIN_ERROR);
	if (height > 300 || height < 1)
		return (MAIN_ERROR);
	return (MAIN_OK);
}

/// Read the first line of file and create a canvas which we will later use to draw on
int	ft_init_canvas(FILE *file, t_canvas **canvas)
{
	int			fscanf_ret;
	int			width;
	int			height;
	char		background_char;
	t_canvas	*ret;

	fscanf_ret = fscanf(file, "%d %d %c\n", &width, &height, &background_char);
	if (fscanf_ret != 3 || ft_check_for_canvas_errors(width, height) == MAIN_ERROR)
		return (ft_putendl(FILE_ERROR, MAIN_ERROR));
	ret = malloc(sizeof(t_canvas));
	if (!ret)
		return (ft_putendl(FILE_ERROR, MAIN_ERROR));
	ret->width = width;
	ret->height = height;
	ret->background_char = background_char;
	*canvas = ret;
	return (MAIN_OK);
}

int	ft_init_background(t_canvas *canvas, char ***background)
{
	int		height;
	int		width;
	char	background_char;
	int		i;
	char	**ret;

	height = canvas->height;
	width = canvas->width;
	background_char = canvas->background_char;
	ret = malloc(sizeof(*ret) * (height + 1));
	if (!ret)
		return (ft_putendl(FILE_ERROR, MAIN_ERROR));
	i = -1;
	while (++i < height)
	{
		ret[i] = malloc(sizeof(**ret) * (width + 1));
		if (!ret[i])
		{
			*background = ret;
			return (ft_putendl(FILE_ERROR, MAIN_ERROR));
		}
		memset(ret[i], (int)(background_char), width);
		ret[i][width] = '\0';
	}
	ret[i] = NULL;
	*background = ret;
	return (MAIN_OK);
}

/// To clean up:
/// 1) Close the file
/// 2) Free the t_canvas structure
/// 3) Free every string in array **background + free background itself
int	ft_cleanup(FILE *file, t_canvas *canvas, char **background, int to_return)
{
	int	i;

	if (file)
	{
		if (fclose(file))
			return (ft_putendl(FILE_ERROR, MAIN_ERROR));
	}
	if (canvas)
		free(canvas);
	if (background)
	{
		i = -1;
		while (background[++i])
			free(background[i]);
		free(background);
	}	
	return (to_return);
}

/// Malloc a t_rectangle structure and assign the values read from the file to it
t_rectangle	*ft_init_rectangle_and_check_errors(char r_type, float x, float y, float width, float height, char draw_char)
{
	t_rectangle	*ret;

	if (r_type != 'r' && r_type != 'R')
		return (NULL);
	if (width <= 0)
		return (NULL);
	if (height <= 0)
		return (NULL);
	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL);
	ret->r_type = r_type;
	ret->x_top = x;
	ret->y_top = y;
	ret->x_bottom = x + width;
	ret->y_bottom = y + height;
	ret->width = width;
	ret->height = height;
	ret->draw_char = draw_char;
	return (ret);
}

float	ft_vabs(float x)
{
	if (x < 0)
		return (x * -1);
	return (x);
}

/// R: If Xtl <= Xa <= Xbr and Ytl <= Ya <= Ybr then the point is in the rectangle
///
/// r: A pixel with a top left corner with a distance bigger or equal than 1 from the border of a rectangle is not part of an empty rectangle
/// A pixel with a top left corner with a distance lower than 1 from the border of a rectangle is part of an empty rectangle.
int	ft_need_to_draw_here(float x, float y, t_rectangle *rectangle)
{
	char	rect_type;

	int		ret;
	float	xtl;
	float	ytl;
	float	xbr;
	float	ybr;

	xtl = rectangle->x_top;
	ytl = rectangle->y_top;
	xbr = rectangle->x_bottom;
	ybr = rectangle->y_bottom;
	ret = 0;
	rect_type = rectangle->r_type;
	if (rect_type == 'R')
	{
		if (xtl <= x && xbr >=x && ytl <= y && ybr >= y)
		   return (1);
	}
	else if (rect_type == 'r')
	{
		if (x < xtl || x > xbr || y < ytl || y > ybr)
			return (0);
		if (x - xtl < 1 || xbr - x < 1 || y - ytl < 1 || ybr - y < 1)
			return (1);
	}
	return (0);
}

/// Go through the background and if rectangle[x][y] belongs to the rectangle
/// We change the background's character
void	ft_draw(char **background, t_rectangle *rectangle)
{
	int		x;
	int		y;
	char	draw_char;

	y = -1;
	draw_char = rectangle->draw_char;
	while (background[++y])
	{
		x = -1;
		while (background[y][++x])
		{
			if (ft_need_to_draw_here((float)x, (float)y, rectangle))
				background[y][x] = draw_char;
		}
	}

}

int	ft_draw_rectangles(FILE *file, char **background)
{
	int			fscanf_ret;
	char		r_type;
	float		x;
	float		y;
	float		r_width;
	float		r_height;
	char		draw_char;
	
	t_rectangle	*rectangle;

	while ((fscanf_ret = fscanf(file, "%c %f %f %f %f %c\n", &r_type, &x, &y, &r_width, &r_height, &draw_char)) == 6)
	{

		rectangle = ft_init_rectangle_and_check_errors(r_type, x, y, r_width, r_height, draw_char);
		if (!rectangle)
			return (ft_putendl(FILE_ERROR, MAIN_ERROR));
		ft_draw(background, rectangle);
		free(rectangle);
	}
	if (fscanf_ret != EOF)
		return (ft_putendl(FILE_ERROR, MAIN_ERROR));
	return (MAIN_OK);
}


int	main(int argc, char **argv)
{
	FILE		*file;
	t_canvas	*canvas;
	char		**background;

	background = NULL;
	if (ft_check_arg_errors_and_open_file(argc, argv, &file) == MAIN_ERROR)
		return (MAIN_ERROR);
	if (ft_init_canvas(file, &canvas) == MAIN_ERROR)
		return (MAIN_ERROR);
	if (ft_init_background(canvas, &background) == MAIN_ERROR)
		return (ft_cleanup(file, canvas, background, MAIN_ERROR));
	if (ft_draw_rectangles(file, background) == MAIN_ERROR)
		return (ft_cleanup(file, canvas, background, MAIN_ERROR));
	ft_print_final_result(background);
	return (ft_cleanup(file, canvas, background, MAIN_OK));
}
