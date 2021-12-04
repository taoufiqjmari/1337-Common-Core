/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:19:34 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/20 16:15:12 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact() {}

std::string Contact::getFirstName() const
{
	return (this->_firstName);
}

std::string Contact::getLastName() const
{
	return (this->_lastName);
}

std::string Contact::getNickame() const
{
	return (this->_nickname);
}

std::string Contact::getPhoneNumber() const
{
	return (this->_phoneNumber);
}

std::string Contact::getDarkestSecret() const
{
	return (this->_darkestSecret);
}

void Contact::setFirstName(void)
{
	std::string	newValue;

	std::cout << "first name:	";
	std::getline(std::cin, newValue);
	this->_firstName = newValue;
}

void Contact::setLastName(void)
{
	std::string	newValue;

	std::cout << "last name:	";
	std::getline(std::cin, newValue);
	this->_lastName = newValue;
}

void Contact::setNickame(void)
{
	std::string	newValue;

	std::cout << "nickname:	";
	std::getline(std::cin, newValue);
	this->_nickname = newValue;
}

void Contact::setPhoneNumber(void)
{
	std::string		newValue;

	while (1) {
		std::cout << "phone number:	";
		std::getline(std::cin, newValue);
		if (isNumber(newValue)) {
			this->_phoneNumber = newValue;
			return ;
		}
		else
			std::cout << "Wrong input for phone number." << std::endl;
	}
}

void Contact::setDarkestSecret(void)
{
	std::string	newValue;

	std::cout << "darkest secret:	";
	std::getline(std::cin, newValue);
	this->_darkestSecret = newValue;
}

Contact::~Contact() {}
