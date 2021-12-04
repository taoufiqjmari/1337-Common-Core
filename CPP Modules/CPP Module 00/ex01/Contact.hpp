/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:19:32 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/20 16:15:12 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>

class Contact
{
	private:
		std::string _firstName;
		std::string _lastName;
		std::string _nickname;
		std::string	_phoneNumber;
		std::string _darkestSecret;
	public:
		Contact();
		std::string getFirstName(void) const;
		std::string getLastName(void) const;
		std::string getNickame(void) const;
		std::string getPhoneNumber(void) const;
		std::string getDarkestSecret(void) const;
		void 		setFirstName(void);
		void 		setLastName(void);
		void 		setNickame(void);
		void 		setPhoneNumber(void);
		void 		setDarkestSecret(void);
		~Contact();
};

bool	isNumber(const std::string& str);

#endif
