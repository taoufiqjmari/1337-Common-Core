/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:18:22 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/13 12:06:49 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(EASYFIND)
#define EASYFIND

#include <iostream>
#include <exception>
#include <algorithm>

class notFound : public std::exception {
public:
	virtual const char *what() const throw();
};

template <typename T>
typename T::iterator	easyfind(T &container, int toBeFound) {
	typename T::iterator it = find(container.begin(), container.end(), toBeFound);
	if (it == container.end())
		throw notFound();
	return (it);
}

#endif // EASYFIND
