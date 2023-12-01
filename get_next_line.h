/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:12:28 by ocussy            #+#    #+#             */
/*   Updated: 2023/11/29 11:29:00 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4  // Valeur par défaut si BUFFER_SIZE n'est pas défini

#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 

typedef struct s_list {
	char *content;
	struct s_list *next;
} t_list;

char *get_next_line(int fd);

#endif
