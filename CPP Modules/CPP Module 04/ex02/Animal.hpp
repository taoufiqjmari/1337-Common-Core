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

// I assume that with interface you mean a C++ class with only pure virtual methods (i.e. without any code), instead with abstract class you mean a C++ class with virtual methods that can be overridden, and some code, but at least one pure virtual method that makes the class not instantiable.

#endif
