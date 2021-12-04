/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:28:49 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/03 18:15:59 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scalar.hpp"

int	main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "\033[0;31mUSAGE: \033[0m./convert param" << std::endl;
		return (1);
	}
	Scalar	toConvert(argv[1]);
	std::cout << toConvert;
	return (0);
}
