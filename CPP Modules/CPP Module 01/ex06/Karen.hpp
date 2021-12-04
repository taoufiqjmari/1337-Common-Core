/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Karen.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:07:25 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/21 18:24:21 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KAREN_HPP
#define KAREN_HPP

#include <iostream>

class Karen
{
private:
	void	debug(void);
	void	info(void);
	void	warning(void);
	void	error(void);
public:
	Karen();
	~Karen();
	void	complain(std::string level);
};

#endif
 