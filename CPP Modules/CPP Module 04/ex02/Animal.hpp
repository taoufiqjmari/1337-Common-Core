/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:25:52 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/27 18:44:29 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>

class Animal {
protected:
	std::string	_type;
public:
	Animal();
	Animal(std::string);
	Animal(Animal const&);
	virtual	~Animal();

	virtual	Animal	&operator=(const Animal &);

	virtual	std::string	getType(void) const;
	virtual	void		makeSound() const = 0;
};

#endif
