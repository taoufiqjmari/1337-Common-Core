/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:53:26 by tjmari            #+#    #+#             */
/*   Updated: 2021/02/24 11:17:45 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libasm.h"

int		main(void)
{
	int		len;
	char	dest[20];
	int		fd;
	char	*str;
	int		read;

	fd = open("./includes/libasm.h", O_RDONLY);
	str = malloc(sizeof(char) * 100);
	len = ft_strlen("1337 Future is loading");
	printf("ft_strlen: %d\n\n", len);
	printf("   strcpy: %s\n", strcpy(dest, "azerty"));
	printf("ft_strcpy: %s\n\n", ft_strcpy(dest, "azerty"));
	printf("   strcmp: %d\n", strcmp("abc", "abd"));
	printf("ft_strcmp: %d\n\n", ft_strcmp("abc", "abd"));
	write(1, "   write: 1337 Future is loading\n", len + 12);
	ft_write(1, "ft_write: 1337 Future is loading\n\n", len + 13);
	read = ft_read(fd, str, 70);
	str[read] = '\0';
	printf("ft_read: %s\n\n", str);
	printf("   strdup: %s\n", strdup("1337 Future is loading"));
	printf("ft_strdup: %s\n\n", ft_strdup("1337 Future is loading"));
	return (0);
}
