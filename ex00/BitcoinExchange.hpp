/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 11:10:02 by pauladretta       #+#    #+#             */
/*   Updated: 2026/05/21 23:52:33 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <ctime>
#include <iomanip>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define ORANGE "\033[38;5;208m"
#define BLUE "\033[34m"
#define LIGHT_GREEN "\033[38;5;120m"
#define RESET "\033[0m"

class BitcoinExchange
{
    private:
        std::map<std::string, float> _database;

        struct Result
        {
            std::string date;
            float value;
            bool errorFound;
            std::string errorMsg;
        };
        // Default constructor
        BitcoinExchange();

    public:
        // Personalized constructor
        BitcoinExchange(const std::string &file);
        // Copy constructor
        BitcoinExchange(const BitcoinExchange& other);
        // Copy assignment operator
        BitcoinExchange& operator=(const BitcoinExchange& other);
        // Destructor
        ~BitcoinExchange();

        // member functions
        void loadDatabase();
        void processInputFile(const std::string &file);
        void parseColumnHeader(std::ifstream &fileStream, std::string &row);
        void parseRow(std::string &row, Result &res);
        bool isValidDate(const std::string &date);
        bool isLeapYear(int year);
        bool printError(Result &res);
        void computeRowValueWithExchangeRate(Result &res);
};

#endif