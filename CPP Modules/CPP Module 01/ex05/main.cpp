/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:12:32 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/22 10:56:36 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

int	main(void) {
	Karen	karen;
	std::string	levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	for (int i(0); i < 4; i++)
		karen.complain(levels[i]);
	return (0);
}
