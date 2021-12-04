/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:16:49 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/20 16:13:33 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <ctime>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

int	Account::getNbAccounts(void) {
	return (_nbAccounts);
}

int	Account::getTotalAmount(void) {
	return (_totalAmount);
}

int	Account::getNbDeposits(void) {
	return (_totalNbDeposits);
}

int	Account::getNbWithdrawals(void) {
	return (_totalNbWithdrawals);
}

Account::Account(int initial_deposit) {
	_displayTimestamp();
	_accountIndex = getNbAccounts();
	std::cout << "index:" << _accountIndex;
	_amount = initial_deposit;
	std::cout << ";amount:" << initial_deposit;
	_totalAmount += initial_deposit;
	std::cout << ";created" << std::endl;
	_nbDeposits = 0;
	_nbWithdrawals = 0;
	_nbAccounts++;
}

Account::Account(void) {}

Account::~Account(void) {
	_displayTimestamp();
	std::cout << "index:" << _accountIndex;
	std::cout << ";amount:" << _amount;
	std::cout << ";closed" << std::endl;
}

void	Account::_displayTimestamp() {
	time_t		rawtime;
	struct tm	*timeinfo;
	char		buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%Y%m%d_%H%M%S", timeinfo);
	std::cout << "[" << buffer << "] ";
}

void	Account::displayAccountsInfos(void) {
	_displayTimestamp();
	std::cout << "accounts:" << getNbAccounts();
	std::cout << ";total:" << getTotalAmount();
	std::cout << ";deposits:" << getNbDeposits();
	std::cout << ";withdrawals:" << getNbWithdrawals() << std::endl;
}

void	Account::makeDeposit(int deposit) {
	_displayTimestamp();
	int	p_amount = this->_amount;
	this->_amount += deposit;
	this->_totalAmount += deposit;
	this->_nbDeposits++;
	this->_totalNbDeposits++;
	std::cout << "index:" << this->_accountIndex;
	std::cout << ";p_amount:" << p_amount;
	std::cout << ";deposit:" << deposit;
	std::cout << ";amount:" << this->_amount;
	std::cout << ";nb_deposits:" << this->_nbDeposits << std::endl;
}

bool	Account::makeWithdrawal(int withdrawal) {
	_displayTimestamp();
	int	p_amount(this->_amount);
	this->_amount -= withdrawal;
	std::cout << "index:" << this->_accountIndex;
	std::cout << ";p_amount:" << p_amount;
	if (checkAmount()) {
		this->_totalAmount -= withdrawal;
		this->_nbWithdrawals++;
		this->_totalNbWithdrawals++;
		std::cout << ";withdrawal:" << withdrawal;
	}
	else {
		this->_amount = p_amount;
		std::cout << ";withdrawal:refused" << std::endl;
		return (false);
	}
	std::cout << ";amount:" << this->_amount;
	std::cout << ";nb_withdrawals:" << this->_nbWithdrawals << std::endl;
	return (true);
}

int		Account::checkAmount(void) const {
	if (this->_amount < 0)
		return (0);
	return (1);
}

void	Account::displayStatus(void) const {
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex;
	std::cout << ";amount:" << this->_amount;
	std::cout << ";deposits:" << this->_nbDeposits;
	std::cout << ";withdrawals:" << this->_nbWithdrawals << std::endl;
}
