/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:00:14 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/11 15:52:23 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ARRAY_HPP
#define	ARRAY_HPP

template <typename T>
class Array {
private:
	T				*_ptr;
	unsigned int	_size;
public:
	Array();
	Array(unsigned int);
	Array(Array const&);
	~Array();

	Array	&operator=(const Array &);
	T		&operator[](unsigned int);

	class outOfRange : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	unsigned int	size(void) const;
};

template <typename T>
Array<T>::Array() {
	std::cout << "Default constructer called" << std::endl;
	_ptr = new T[0];
	_size = 0;
}

template <typename T>
Array<T>::Array(unsigned int n) {
	std::cout << "Constructer called" << std::endl;
	_ptr = new T[n];
	_size = n;
}

template <typename T>
Array<T>::Array(const Array<T> &src) : _ptr(NULL) {
	std::cout << "Copy constructer called" << std::endl;
	*this = src;
}

template <typename T>
Array<T>	&Array<T>::operator=(const Array<T> &rhs) {
	std::cout << "Array equal operator called" << std::endl;
	if (_ptr)	
		delete[] _ptr;
	_size = rhs._size;
	_ptr = new T[_size];
	for (unsigned int i(0); i < _size; i++)
		_ptr[i] = rhs._ptr[i];
	return (*this);
}

template <typename T>
Array<T>::~Array() {
	std::cout << "Default destructor called" << std::endl;
	delete[] _ptr;
}

template <typename T>
unsigned int	Array<T>::size(void) const {
	return (_size);
}

template <typename T>
T	&Array<T>::operator[](unsigned int i) {
	if (i < 0 || i >= _size)
		throw outOfRange();
	return (_ptr[i]);
}

template <typename T>
const char	*Array<T>::outOfRange::what() const throw() {
	return ("out_of_range");
}

#endif
