/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <matahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:33:03 by matahir           #+#    #+#             */
/*   Updated: 2025/01/15 03:44:53 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	*ft_calloc(size_t lenn, size_t size);
size_t	ft_strlen(char *s);
char	*my_strchr(char *s, char c);
char	*ft_strjoin(char *cup, char *spoon);
char	*append_buffer(char *cup, char *spoon);
char	*extract_line(char *cup);
char	*save_leftovers(char *cup);
char	*check(char *t);
char	*reading_fct(char *cup, int fd);

#endif
