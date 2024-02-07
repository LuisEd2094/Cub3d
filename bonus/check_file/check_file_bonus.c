#include <cub3d_bonus.h>

void	validate_map(char *file_name, t_prg *prg)
{
	int	fd;

	if (check_if_invalid_ext(file_name, ".cub", ft_strlen(".cub")))
		exit_error(INCORRECT_FILE, prg);
	if ((errno && errno != 11))
		exit_error(NULL, prg);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit_error(NULL, prg);
	if (!parse_file(fd, prg) || (errno && errno != 11))
	{
		close(fd);
		exit_error(NULL, prg);
	}
	open_img(&(prg->mlx), &(prg->door_img), "./imgs/door.xpm");//
	open_img(&(prg->mlx), &(prg->sprite[0]), "./imgs/sprite1.xpm");
	open_img(&(prg->mlx), &(prg->sprite[1]), "./imgs/sprite2.xpm");
	open_img(&(prg->mlx), &(prg->sprite[2]), "./imgs/sprite3.xpm");
	close(fd);
}
