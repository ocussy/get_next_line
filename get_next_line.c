/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:12:17 by ocussy            #+#    #+#             */
/*   Updated: 2023/12/01 13:37:52 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

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


t_list	*ft_lstnew(char *content)
{
	t_list	*new;
	//printf("s = %s\n", content);

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->content = ft_strdup(content);
	//printf("%s\n", new->content);
	new->next = NULL;
	return (new);
}

void    ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list *temp;

    if (!new)
        return ;
    if (*lst == NULL)
	{
        *lst = new;
	}
    else
    {
        temp = *lst;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }
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

char *ft_make_str(t_list *list, int count)
{
	char *dest;
	int i;

	dest = malloc(sizeof(char) * (BUFFER_SIZE * (count + 1)));
	if (!dest)
		return (NULL);
	dest[0] = '\0';
	while (list)
	{
		dest = ft_strcat(dest, (list)->content);
		(list) = (list)->next;
	}
	i = ft_strlen(dest);
	dest[i++] = '\n';
	dest[i] = '\0';
	return(dest);
}

t_list	*ft_clean(t_list *lst)
{
	t_list *head;
	int i;
	int j;
	t_list *temp;
	
	i = 0;
	j = 0;
	head = malloc(sizeof(t_list));
	// if ( !*lst)
	// 	return (0);
	while (lst->next != NULL)
	{
		temp = lst->next;
		free(lst);
		lst = temp;
	}
	while (lst->content[i] != '\n' && lst->content[i])
		i++;
	if (lst->content[i] == '\n')
		i++;
	head->content = ft_strdup(&lst->content[i]);
	head->next = NULL;
	printf("node :%s \n", head->content);
	free(lst);
	return (head);
}

char *ft_create_list(t_list **list, int fd)
{
	t_list *new;
	char *buf;
	int read_bytes;
	int count;
	char *line;

	count = 0;
	line = "\0";
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while ((read_bytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		count++;
		buf[read_bytes] = '\0';
		new = ft_lstnew(buf);
		ft_lstadd_back(list, new);
		
		if (ft_strchr(buf, '\n') == 1)
		{	
			line = ft_make_str(*list, count);
			(*list) = ft_clean(*list);
			break;
		}
	}
	free(buf);
	return (line);
}

char *get_next_line(int fd)
{
	int i;
	static t_list *list;
	char *line;

	// on protege en verifiant les infos
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_create_list(&list, fd);
	if (line[0]==0)
		return NULL;
	return (line);
}


int    main(void)
{
    int fd;
    char *line;
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        // free(line);
    }
    close(fd);
    return (0);
}