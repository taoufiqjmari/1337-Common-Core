/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutantstack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:25:30 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/13 11:47:41 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(MUTANTSTACK)
#define MUTANTSTACK

#include <iostream>
#include <stack>

template <typename T>
class MutantStack : public std::stack<T> {
private:
public:
	MutantStack() : std::stack<T>() {};
	MutantStack(const MutantStack<T> &src) {*this = src;};
	~MutantStack() {};

	MutantStack	&operator=(const MutantStack<T> &rhs) {this->c = rhs.c; return (*this);};

	typedef typename std::stack<T>::container_type::iterator iterator;

	iterator    begin() {return this->c.begin();}
	iterator    end() {return this->c.end();}
};

#endif // MUTANTSTACK
