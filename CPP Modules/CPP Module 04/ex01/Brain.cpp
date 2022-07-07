/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:52:55 by tjmari            #+#    #+#             */
/*   Updated: 2022/07/07 00:28:33 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain default constructor called" << std::endl;
	for (int i(0); i < LENGHT; i++)
		_ideas[i] = "N/A";
}

Brain::Brain(std::string idea)
{
	std::cout << "Brain type constructor called" << std::endl;
	for (int i(0); i < LENGHT; i++)
		_ideas[i] = idea;
}

Brain::Brain(Brain const &src)
{
	std::cout << "Brain copy constructor called" << std::endl;
	*this = src;
}

Brain::~Brain()
{
	std::cout << "Brain destructor called" << std::endl;
}

Brain &Brain::operator=(const Brain &rhs)
{
	std::cout << "Brain equal operator called" << std::endl;
	if (this != &rhs)
		for (int i(0); i < LENGHT; i++)
			this->_ideas[i] = rhs._ideas[i];
	return (*this);
}

std::string Brain::getIdea() const
{
	return (*_ideas);
}
