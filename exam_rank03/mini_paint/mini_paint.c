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
	write(1, "\n", 1);
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

	fscanf_ret = fscanf(file, "%d %d %c\n", &width, &height, &background_char);
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
	ft_print_final_result(background);
	return (ft_cleanup(file, canvas, background, OK));
}
