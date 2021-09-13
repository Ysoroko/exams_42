#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_canvas
{
	int	width;
	int	height;
	char	background_char;
}	t_canvas;

typedef struct s_circle
{
	char	c_type;
	float	xc;
	float	yc;
	float	radius;
	char	draw_char;
}	t_circle;

#define OK 0
#define KO 1

#define ARG_ERROR "Error: argument"
#define FILE_ERROR "Error: Operation file corrupted"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

int	ft_putendl(char *str, int to_return)
{
	if (!str)
		return (KO);
	write(1, str, ft_strlen(str));
	ft_putchar('\n');
	return (to_return);
}

/// This function checks for main arguments errors and opens the file argument
/// The pointer to FILE is stored in *file argument after it's initialized
/// Possible errors:
/// 1) The program has no arguments or the program has more than 1 argument
/// 2) Bad path to file / bad file name provided
int	ft_check_arg_errors_and_open_file(int argc, char **argv, FILE **file)
{
	FILE	*f;

	if (argc != 2)
		return (ft_putendl(ARG_ERROR, KO));
	f = fopen(argv[1], "r");
	if (f == NULL)
		return (ft_putendl(FILE_ERROR, KO));
	*file = f;
	return (OK);
}

/// Check for errors in first line of our file
/// Returns KO if an error was found, OK otherwise
/// Possible errors:
/// 1) Width is bigger than 300 or width is lower than 1
/// 2) Height is bigger than 300 or height is lower than 1
int	ft_check_for_canvas_errors(int width, int height)
{
	if (width <= 0  || width > 300)
		return (KO);
	if (height <= 0 || height > 300)
		return (KO);
	return (OK);
}

/// This function reads the first line of the file and creates a t_canvas structure
/// where it stores the values. 
/// Then it assigns *canvas argument to point to this structure.
/// If any error is found in values or the first line, KO (=1) is returned and *canvas
/// remains unitialized
int	ft_init_canvas(FILE *file, t_canvas **canvas)
{
	int		width;
	int		height;
	char		background_char;
	int		fscanf_ret;
	t_canvas	*c;

	fscanf_ret = fscanf(file, " %d %d %c\n", &width, &height, &background_char);
	if (fscanf_ret != 3)
		return (ft_putendl(FILE_ERROR, KO));
	if (ft_check_for_canvas_errors(width, height) == KO)
		return (ft_putendl(FILE_ERROR, KO));
	c = malloc(sizeof(t_canvas));
	if (!c)
		return (ft_putendl(FILE_ERROR, KO));
	c->width = width;
	c->height = height;
	c->background_char = background_char;
	*canvas = c;
	return (OK);
}

/// Closes the file and frees all the allocated memory
/// To do:
/// 1) Close the file
/// 2) Free the t_canvas structure
/// 3) Free every string in "background" array of strings + free "background" itself 
/// (If failed to close the file, prints the FILE_ERROR message and returns KO)
/// Returns to_return argument
int	ft_cleanup(FILE *file, t_canvas *canvas, char **background, int to_return)
{
	int	i;

	if (file)
	{
		if (fclose(file) == EOF)
			return (ft_putendl(FILE_ERROR, KO));
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


/// Initialize the array of strings which will serve as a background we will draw on
/// Assign the *background argument to point to the newly created array of strings
/// If a malloc call fails, print FILE_ERROR and return KO.
/// If a malloc fails in the while loop, still assign *background to be the new array
/// to be able to free all strings allocated so far in ft_cleanup
int	ft_init_background(t_canvas *canvas, char ***background)
{
	char	**res;
	int	i;
	int	width;
	int	height;
	char	background_char;

	width = canvas->width;
	height = canvas->height;
	background_char = canvas->background_char;
	res = malloc(sizeof(*res) * (height + 1));
	if (!res)
		return (ft_putendl(FILE_ERROR, KO));
	i = -1;
	while (++i < height)
	{
		res[i] = malloc(sizeof(char) * (width + 1));
		if (!res[i])
		{
			*background = res;
			return (ft_putendl(FILE_ERROR, KO));
		}
		memset(res[i], background_char, width);
		res[i][width] = '\0';
	}
	res[i] = NULL;
	*background = res;
	return (OK);
}

/// Print every string in "background" array of strings
void	ft_print_final_result(char **background)
{
	int	i;

	i = -1;
	while (background[++i])
		ft_putendl(background[i], 0);
}

/// Check for values errors, malloc a new t_circle, fill in the values and assign *circle argument to be the new t_circle
/// Possible errors:
/// 1) Circle type character is different from 'c' and 'C'
/// 2) Radius is less than or equal to 0
/// Returns KO if an error is found or if the malloc call fails
/// Returns OK otherwise
int	ft_check_for_value_errors_and_init_circle(char c_type, float xc, float yc, float radius, char draw_char, t_circle **circle)
{
	t_circle	*res;

	if (c_type != 'c' && c_type != 'C')
		return (KO);
	if (radius <= 0)
		return (KO);
	res = malloc(sizeof(t_circle));
	if (!res)
		return (KO);
	res->c_type = c_type;
	res->xc = xc;
	res->yc = yc;
	res->radius = radius;
	res->draw_char = draw_char;
	*circle = res;
	return (OK);
}

/// Returns the distance between two points [x_a ; y_a] and [x_b ; y_b]
/// If you've got 2 points are defined as (Xa,Ya) and (Xb,Yb)
/// Distance between the two points is : srqt((Xa - Xb) * (Xa - Xb) + (Ya - Yb) * (Ya - Yb)) 
float	ft_get_distance(float x_a, float y_a, float x_b, float y_b)
{
	float	x_diff;
	float	y_diff;
	float	x_diff_sqr;
	float	y_diff_sqr;
	float	sqr_sum;

	x_diff = x_a - x_b;
	x_diff_sqr = powf(x_diff, 2);
	y_diff = y_a - y_b;
	y_diff_sqr = powf(y_diff, 2);
	sqr_sum = x_diff_sqr + y_diff_sqr;
	return (sqrtf(sqr_sum));
}

/// Returns OK if the point [x ; y] belongs to the circle argument
/// Returns KO otherwise
/// A point belongs to the circle if all the criteria are met:
/// 'c' circle (border only):
/// 1) x_point belongs to the range [x_center_circle - radius ; x_center_circle + radius]
/// 2) y_point belongs to the range [y_center_circle - radius; y_center_circle + radius]
/// 3) Distance between the circle border and the point is < 1
/// (RADIUS - P_DISTANCE_TO_CENTER < 1);
///
///
/// 'C' circle (filled-in circle)
/// 1) x_point belongs to the range [x_center_circle - radius ; x_center_circle + radius]
/// 2) y_point belongs to the range [y_center_circle - radius; y_center_circle + radius]
/// 3) Distance between the point and the center of the circle <= radius of the circle
/// (This is the same as the first 2 conditions)
int	ft_belongs_to_the_circle(float x, float y, t_circle *circle)
{
	float	distance_to_center;
	float	xc;
	float	yc;
	float	radius;

	xc = circle->xc;
	yc = circle->yc;
	radius = circle->radius;
	distance_to_center = ft_get_distance(x, y, circle->xc, circle->yc);
	if (circle->c_type == 'c')
	{
		// distance to center needs to be (<= radius) and (> radius - 1)
		if (distance_to_center <= radius && radius - distance_to_center < 1)
			return (OK);
	}
	else if (circle->c_type == 'C')
	{
		// distance to center needs to be (<= radius)
		if (distance_to_center <= radius)
			return (OK);
	}
	return (KO);

}

/// Goes through the background and checks if the point [x;y] belongs to the circle
/// If so, changes the character background[y][x] character
void	ft_draw_the_circle(char **background, t_circle *circle)
{
	int	x;
	int	y;
	char	draw_char;

	y = -1;
	draw_char = circle->draw_char;
	while (background[++y])
	{
		x = -1;
		while (background[y][++x])
		{
			if (ft_belongs_to_the_circle((float)x, (float)y, circle) == OK)
				background[y][x] = draw_char;
		}
	}

}

/// The central function of drawing on background
/// Reads next line from file, initializes a t_circle structure based on values
/// and modifies the characters in the background based on the circle
/// Displays an error message and returns KO if an error is found in file or a malloc failure
/// Returns OK otherwise
int	ft_draw_on_background(FILE *file, char **background)
{
	t_circle	*circle;
	int			fscanf_ret;
	char		c_type;
	float		xc;
	float		yc;
	float		radius;
	char		draw_char;

	while ((fscanf_ret = fscanf(file, "%c %f %f %f %c\n", &c_type, &xc, &yc, &radius, &draw_char)) == 5)
	{
		if (ft_check_for_value_errors_and_init_circle(c_type, xc, yc, radius, draw_char, &circle) == KO)
			return (ft_putendl(FILE_ERROR, KO));
		ft_draw_the_circle(background, circle); 
		free(circle);

	}
	if (fscanf_ret != EOF)
		return (ft_putendl(FILE_ERROR, KO));
	return (OK);	
}

int	main(int argc, char **argv)
{
	FILE		*file;
	t_canvas	*canvas;
	char		**background;

	if (ft_check_arg_errors_and_open_file(argc, argv, &file) == KO)
		return (KO);
	if (ft_init_canvas(file, &canvas) == KO)
		return (ft_cleanup(file, NULL, NULL, KO));
	if (ft_init_background(canvas, &background) == KO)
		return (ft_cleanup(file, canvas, NULL, KO));
	if (ft_draw_on_background(file, background) == KO)
		return (ft_cleanup(file, canvas, background, KO));
	ft_print_final_result(background);
	return (ft_cleanup(file, canvas, background, OK));
}
