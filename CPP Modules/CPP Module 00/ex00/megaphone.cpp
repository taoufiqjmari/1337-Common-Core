/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:27:17 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/17 17:34:24 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main(int argc, char *argv[])
{
	size_t	len;

	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
	{
		for (int i(1); i < argc; i++)
		{
			len = strlen(argv[i]);
			for (size_t j(0); j < len; j++)
				std::cout << (char)toupper(argv[i][j]);
		}
	}
	std::cout << std::endl;
	return (0);
}
