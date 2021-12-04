/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:15:08 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/21 11:21:37 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main(void) {
	std::string	str("HI THIS IS BRAIN");
	std::string	*stringPTR(&str);
	std::string &stringREF(str);

	std::cout << "The address in memory of the string:		" << &str << std::endl;
	std::cout << "The address of the string by using stringPTR:	" << stringPTR << std::endl;
	std::cout << "The address of the string by using stringREF:	" << &stringREF << std::endl;

	std::cout << "The string using the pointer:			" << *stringPTR << std::endl;
	std::cout << "The string using the reference:			" << stringREF << std::endl;
}