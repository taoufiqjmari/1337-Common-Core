/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:52:52 by tjmari            #+#    #+#             */
/*   Updated: 2022/07/07 00:29:49 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>

#define LENGHT 100

class Brain
{
private:
	std::string _ideas[LENGHT];

public:
	Brain();
	Brain(std::string);
	Brain(Brain const &);
	~Brain();

	Brain &operator=(const Brain &);

	std::string getIdea() const;
};

#endif
