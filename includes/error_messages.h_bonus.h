/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:06:03 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:08:26 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

# ifndef INCORRECT_USE
#  define INCORRECT_USE "Incorrect use, please run ./cub3D <map_file.cub>\n"
# endif

# ifndef INCORRECT_FILE
#  define INCORRECT_FILE "Incorrect file, please check the description, \
extension and permissions\n"
# endif

# ifndef MISCONFIG
#  define MISCONFIG "Error\nFile doesn't follow subject configuration\n"
# endif

# ifndef REPEATED
#  define REPEATED "Error\nOne or more of the identifiers are repeated\n"
# endif

# ifndef RGB_ERROR
#  define RGB_ERROR "Error\nIncorrect ceiling/floor configuration\n"
# endif

# ifndef NO_MAP
#  define NO_MAP "Error\nFile does't have a map\n"
# endif

# ifndef NO_PLAYER
#  define NO_PLAYER "Error\nFile does't have a player\n"
# endif

# ifndef WRONG_MAP
#  define WRONG_MAP "Error\nCheck subject specifications for the map\n"
# endif

# ifndef OPEN_MAP
#  define OPEN_MAP "Error\nCheck map! There is an open wall\n"
# endif

# ifndef DOOR_ERROR
#  define DOOR_ERROR "Error\nCheck map! A door not in a valid position\n"
# endif

#endif
