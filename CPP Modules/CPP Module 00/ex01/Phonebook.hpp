/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:19:26 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/18 19:45:23 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <iostream>
#include <iomanip>

class Phonebook
{
	private:
		Contact	contacts[8];
		int		index;
		int		entered;
	public:
		Phonebook();
		void	add(void);
		void	search(void);
		~Phonebook();
};

#endif
