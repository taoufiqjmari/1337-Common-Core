/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:25:52 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/27 14:35:52 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <iostream>

class WrongAnimal {
protected:
	std::string	_type;
public:
	WrongAnimal();
	WrongAnimal(std::string);
	WrongAnimal(WrongAnimal const&);
	~WrongAnimal();

	WrongAnimal	&operator=(const WrongAnimal &);

	std::string	getType(void) const;
	void		makeSound() const;
};

#endif
