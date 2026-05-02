/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 11:10:02 by pauladretta       #+#    #+#             */
/*   Updated: 2026/04/30 15:51:41 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

// TODO: define and add all errors here (from parsing)

class BitcoinExchange
{
    private:
        std::map<std::string, float> data;

    public:
        // Default constructor
        BitcoinExchange();
        // Personalized constructor
        BitcoinExchange(const std::string &file);
        // Copy constructor
        BitcoinExchange(const BitcoinExchange& other);
        // Copy assignment operator
        BitcoinExchange& operator=(const BitcoinExchange& other);
        // Destructor
        // ~BitcoinExchange();

        // member functions
        void parseFile(const std::string &file);
};

#endif