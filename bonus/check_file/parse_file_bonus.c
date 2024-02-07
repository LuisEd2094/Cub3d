#include <cub3d_bonus.h>
#include "parse_file_bonus.h"

bool	parse_file(int fd, t_prg *prg)
{
	t_parseer	parse;

	init_parseer(&parse);
	if (!parse_for_ids(fd, prg, &parse) || errno && errno != 11)
		return (false);
	if (!parse_map(fd, prg, &parse) || errno && errno != 11)
		return (false);
	return (true);
}
