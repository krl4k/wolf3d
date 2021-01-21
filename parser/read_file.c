/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:50:10 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/24 13:50:17 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		open_file(char *filename)
{
	int fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		close(fd);
		fd = -1;
	}
	return (fd);
}

t_list	*read_file(int fd)
{
	t_list	*head;
	char	*line;
	int		i;

	head = NULL;
	line = NULL;
	while ((i = get_next_line(fd, &line)) > 0)
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	if (i < 0)
	{
		ft_lstclear(&head, ft_lstfree_cont);
		error_handler(READ, 0);
	}
	return (head);
}
