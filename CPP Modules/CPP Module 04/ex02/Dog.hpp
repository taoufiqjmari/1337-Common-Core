/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:27:34 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/28 17:12:48 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Dog : public Animal {
private:
	Brain	*_ideas;
public:
	Dog();
	Dog(Dog const&);
	virtual	~Dog();

	Dog	&operator=(const Dog &);

	virtual void	makeSound() const;
	std::string	getIdea() const;
};

#endif
