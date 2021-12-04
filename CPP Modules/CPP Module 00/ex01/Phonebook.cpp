/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:19:29 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/20 11:13:50 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"

bool	isNumber(const std::string& str) {
	size_t	len;

	len = str.length();
	for(size_t	i(0); i < len; i++) {
	    if (!(std::isdigit(str[i])))
			return (false);
	}
	return (true);
}

Phonebook::Phonebook() : index(0), entered(0) {}

void	Phonebook::add(void) {
	if (index == 8)
		index = 0;
	Phonebook::contacts[index].setFirstName();
	Phonebook::contacts[index].setLastName();
	Phonebook::contacts[index].setNickame();
	Phonebook::contacts[index].setPhoneNumber();
	Phonebook::contacts[index].setDarkestSecret();
	index++;
	if (entered < 8)
		entered++;
}

void	setWidth(std::string field) {
	if (field.length() > 10)
	{
		field = field.substr(0, 9);
		field += '.';
	}
	std::cout << std::setw(10);
	std::cout << field;
	std::cout << '|';
}

void	printUser(Contact contacts[], int entered) {
	std::string	index;
	int			intIndex;

	while (1) {
		std::cout << "index of the desired entry: ";
		std::getline(std::cin, index);
		if (isNumber(index) && !index.empty())
		{
			intIndex = std::stoi(index);
			break ;
		}
		else
			std::cout << "\033[0;31mWrong input for index.\033[0m" << std::endl;
	}
	if (intIndex >= entered) {
		std::cout << "\033[0;31mNo available entry.\033[0m" << std::endl;
		return ;
	}
	std::cout << "\033[0;36mfirst name:	\033[0m" << contacts[intIndex].getFirstName() << std::endl;
	std::cout << "\033[0;36mlast name:	\033[0m" << contacts[intIndex].getLastName() << std::endl;
	std::cout << "\033[0;36mnickname:	\033[0m" << contacts[intIndex].getNickame() << std::endl;
	std::cout << "\033[0;36mphone number:	\033[0m" << contacts[intIndex].getPhoneNumber() << std::endl;
	std::cout << "\033[0;36mdarkest secret:	\033[0m" << contacts[intIndex].getDarkestSecret() << std::endl;
}

void	Phonebook::search(void) {
	setWidth("index");
	setWidth("first name");
	setWidth("last name");
	setWidth("nickname");
	std::cout << std::endl;
	for (int i(0); i < entered; i++) {
		setWidth(std::to_string(i));
		setWidth(contacts[i].getFirstName());
		setWidth(contacts[i].getLastName());
		setWidth(contacts[i].getNickame());
		std::cout << std::endl;
	}
	printUser(contacts, entered);
}

Phonebook::~Phonebook() {}
