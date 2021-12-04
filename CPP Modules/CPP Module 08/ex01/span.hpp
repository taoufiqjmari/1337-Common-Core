/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:24:06 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/12 16:16:07 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(SPAN_HPP)
#define SPAN_HPP

#include <iostream>
#include <exception>
#include <algorithm>
#include <vector>

class Span
{
private:
	uint	_N;
	std::vector<int> _V;
	Span();
public:
	Span(const uint);
	Span(const Span &);
	~Span();

	Span	&operator=(const Span &);

	class	insufficientElements : public std::exception {
	public:
		virtual const char *what() const throw();
	};

	class	vectorFull : public std::exception {
	public:
		virtual const char *what() const throw();
	};

	void	addNumber(const int);
	void	addNumber(std::vector<int>::iterator, std::vector<int>::iterator);
	uint	shortestSpan(void);
	uint	longestSpan(void);
};

#endif // SPAN_HPP
