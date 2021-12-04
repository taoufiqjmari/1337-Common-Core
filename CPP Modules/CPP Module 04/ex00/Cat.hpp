/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:27:31 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/28 16:34:43 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"

class Cat : public Animal {
public:
	Cat();
	Cat(Cat const&);
	virtual	~Cat();

	Cat	&operator=(const Cat &);

	virtual void	makeSound() const;
};

#endif
