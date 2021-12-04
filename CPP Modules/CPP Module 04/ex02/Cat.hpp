/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:27:31 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/28 16:34:59 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Cat : public Animal {
private:
	Brain	*_ideas;
public:
	Cat();
	Cat(Cat const&);
	virtual	~Cat();

	Cat	&operator=(const Cat &);

	void		makeSound() const;
	std::string	getIdea() const;
};

#endif
