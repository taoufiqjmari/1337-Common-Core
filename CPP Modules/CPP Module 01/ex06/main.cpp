/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:12:32 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/22 09:44:51 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

enum	levelsCode {
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	OTHER,
};

levelsCode	hashit(std::string const& inString) {
	if (inString == "DEBUG") return (DEBUG);
	if (inString == "INFO") return (INFO);
	if (inString == "WARNING") return (WARNING);
	if (inString == "ERROR") return (ERROR);
	else return (OTHER);
}

int	main(int argc, char *argv[]) {
	Karen		karen;

	if (argc == 2) {
		std::string	av(argv[1]);
		switch (hashit(av))
		{
		case DEBUG:
			karen.complain("DEBUG");
			std::cout << std::endl;
		case INFO:
			karen.complain("INFO");
			std::cout << std::endl;
		case WARNING:
			karen.complain("WARNING");
			std::cout << std::endl;
		case ERROR:
			karen.complain("ERROR");
			std::cout << std::endl;
			break;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
			std::cout << std::endl;
			break;
		}
	}
	return (1);
}
