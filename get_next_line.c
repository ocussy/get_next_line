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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		total_len;
	int i;
	int	j;

	i = -1;
	j = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return NULL;
	total_len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((total_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

void	*ft_memset(char *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n > 0)
	{
		*p++ = (unsigned char)c;
		n--;
	}
	return (s);
}

char	*ft_make_line(int fd, char *line)
{
	char	*buf;
	int		count;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	count = 1;
	while (ft_strchr(line) != 1 && count != 0)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count == 0 || count == -1)
		{
			free(buf);
			return(NULL);
		}
		if (count != BUFFER_SIZE && count != 0)
		{
			line = ft_strjoin(line, buf);
			free(buf);
			return (line);
		}
		buf[count] = '\0';
		line = ft_strjoin(line, buf);
	}
	free(buf);
	return (line);
}

char	*ft_get_line(char *tempo)
{
	char	*line;
	int		i;

	i = 0;
	while (tempo[i] && tempo[i] != '\n')
		i++;
	if (tempo[i] && tempo[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
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
	line[i] = '\0';
	return (line);
}
void	ft_clean(char *line, char *tempo)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	tempo = ft_memset(tempo, 0, ft_strlen(tempo));
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] && line[i] == '\n')
		i++;
	while (line[i])
		tempo[j++] = line[i++];
	tempo[j] = '\0';
}
char	*get_next_line(int fd)
{
	char		*final_line;
	static char	tempo[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = NULL;
	if (tempo[0] != '\0')
		line = ft_strjoin(line, tempo);
	line = ft_make_line(fd, line);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	final_line = ft_get_line(line);
	ft_clean(line, tempo);
	free(line);
	return (final_line);
}

int main ()
{
	int fd;
    char *line;
    fd = open("test.txt", O_RDONLY);
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