/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:08:57 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/18 19:52:30 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"

enum	string_code {
	ADD,
	SEARCH,
	EXIT,
	NONE,
};

string_code	hashit(std::string const& inString) {
	if (inString == "ADD") return ADD;
	if (inString == "SEARCH") return SEARCH;
	if (inString == "EXIT") return EXIT;
	else return NONE;
}

int	main(void)
{
	Phonebook	MyPhoneBook;
	std::string	choice;
	
	while (1)
	{
		std::cout << "COMMAND (ADD, SEARCH, EXIT): ";
		std::getline(std::cin, choice);
		switch(hashit(choice))
		{
			case ADD:
				MyPhoneBook.add();
				break;
			case SEARCH:
				MyPhoneBook.search();
				break;
			case EXIT:
				return (0);
			default:
				break;
		}
	}
	return (0);
}
