/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:14:26 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/26 14:55:29 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include "ClapTrap.hpp"

class FragTrap : public ClapTrap {

public:
	FragTrap();
	FragTrap(std::string);
	FragTrap(FragTrap const&);
	~FragTrap();

	FragTrap	&operator=(const FragTrap &);

	void	attack(std::string const&target);
	void	highFivesGuys(void);
};

#endif
