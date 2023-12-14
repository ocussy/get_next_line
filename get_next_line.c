/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:54:37 by ocussy            #+#    #+#             */
/*   Updated: 2023/12/13 11:25:31 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;
	
	i = 0;
	if (!str)
		return(0);
	while (str[i])
		i++;
	return (i);
}
int	ft_strchr(char *s)
{
	int		i;

	i = 0;
	if(!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return(0);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	char	*res;

	res = malloc(elementSize * elementCount);
	if (!res)
		return (NULL);
	ft_bzero(res, elementSize * elementCount);
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		total_len;
	int i;
	int	j;

	i = -1;
	j = 0;
	if (!s1)
		s1 = ft_calloc(1, 1);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((total_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}



char	*ft_join(char *line, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(line, buf);
	free(line);
	return (tmp);
}

char	*ft_make_line(int fd, char *line)
{
	char	*buf;
	int		count;

	if (!line)
		line = ft_calloc(1, 1);
	buf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buf)
	{
		free(line);
		return (NULL);
	}
	count = 1;
	while (count > 0)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count == -1)
		{
			free(buf);
			return(NULL);
		}
		buf[count] = '\0';
		line = ft_join(line, buf);
		if (ft_strchr(buf) != 0)
			break;
	}
	free(buf);
	return (line);
}

char	*ft_get_line(char *tempo)
{
	char	*line;
	int		i;

	i = 0;
	if (!tempo)
		return(NULL);
	while (tempo[i] && tempo[i] != '\n')
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	i = 0;
	while (tempo[i] && tempo[i] != '\n')
	{
		line[i] = tempo[i];
		i++;
	}
	if (tempo[i] && tempo[i] == '\n')
	{
		line[i] = tempo[i];
		i++;
	}
	return (line);
}

char	*ft_clean(char *line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!line)
	{
		free(line);
		return (NULL);
	}
	while (line[i] != '\n' && line[i])
		i++;
	tmp = ft_calloc((ft_strlen(line) - i + 1), sizeof(char));
	if (!tmp)
	{
		free(line);
		return (NULL);
	}
	if (line[i] && line[i] == '\n')
		i++;
	while (line[i])
		tmp[j++] = line[i++];
	free(line);
	return(tmp);
}

char	*get_next_line(int fd)
{
	char		*final_line;
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_make_line(fd, line);
	if (!line)
		return (NULL);
	final_line = ft_get_line(line);
	line = ft_clean(line);
	return (final_line);
}

int main ()
{
	int fd;
    char *line;
    fd = open("coucou.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }
	line = get_next_line(fd);
    printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
    printf("%s", line);
	free(line);
	line = get_next_line(fd);
    printf("%s", line);
	free(line);
	line = get_next_line(fd);
    printf("%s", line);
	free(line);
	line = get_next_line(fd);
    printf("%s", line);
	free(line);
    close(fd);
    return (0);
}