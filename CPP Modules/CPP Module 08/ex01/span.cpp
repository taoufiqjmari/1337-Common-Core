/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:24:36 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/12 16:32:57 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "span.hpp"

Span::Span() {}

Span::Span(unsigned int N) : _N(N) {}

Span::Span(const Span &src) {
	*this = src;
}

Span	&Span::operator=(const Span &rhs) {
	_V.clear();
	_N = rhs._N;
	_V.assign(rhs._V.begin(), rhs._V.end());
	return (*this);
}

Span::~Span() {}

void	Span::addNumber(int i) {
	if (_V.size() >= _N)
		throw Span::vectorFull();
	_V.push_back(i);
}

void	Span::addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
	if (_V.size() + std::distance(begin, end) > _N)
		throw Span::vectorFull();
	_V.insert(_V.end(), begin, end);
}

uint	Span::shortestSpan(void) {
	int	shortestSpan = INT_MAX;

	if (_V.size() <= 1)
		throw insufficientElements();
	sort(_V.begin(), _V.end());
	std::vector<int>::iterator it;
	for (it = _V.begin(); it != _V.end() - 1; it++) {
		if ((*(it + 1) - *it) < shortestSpan)
			shortestSpan = *(it + 1) - *it;
	}
	return (shortestSpan);
}

uint	Span::longestSpan(void) {
	if (_V.size() <= 1)
		throw insufficientElements();
	sort(_V.begin(), _V.end());
	return (*(_V.end() - 1) - *(_V.begin()));
}

const char *Span::insufficientElements::what() const throw() {
	return ("Insufficient elements at the object");
}

const char *Span::vectorFull::what() const throw() {
	return ("Object is at full capacity");
}
