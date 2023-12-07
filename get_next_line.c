#include "get_next_line.h"

char	*ft_strdup(const char *src)
{
	char	*copy;
	int		i;

	i = 0;
	copy = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!copy)
		return(0);
	while (src[i])
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int	ft_strchr(const char *s, char ch)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return (1);
		i++;
	}
	return(0);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[j])
		j++;
	while (src[i] && src[i] != '\n')
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char    *ft_clean(char *line)
{
    int     j;
    char    *str;

    while (*line && *line != '\n')
        line++;
    str = malloc(sizeof(char) * (*line + 1));
    if (!str)
        return (NULL);
    while (*line)
    {
        *str = *line;
        str++;
        line++;
    }
    *str = '\0';
    return
}


char get_next_line(int fd)
{
    char *line;
    char        *buf;
    int         read_bytes;
    static char        *tmp;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    while ((read_bytes = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        buf[read_bytes] = '\0';
        tmp = ft_strdup(buf);
        line = malloc(sizeof(tmp + 1));
        if (ft_strchr(buf, '\n' == 1))
        {
            tmp = ft_clean(line);
            line = ft_strcat(line, tmp);
            break;
        }
        line = ft_strcat(line, tmp);
    }
    return (line);
}