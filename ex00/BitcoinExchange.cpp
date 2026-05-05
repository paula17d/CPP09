/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 11:14:34 by pauladretta       #+#    #+#             */
/*   Updated: 2026/05/04 01:12:00 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/*
personalized constructor
- parse database file data.csv
- parse file taken as argument
*/
BitcoinExchange::BitcoinExchange(const std::string &file)
{
    loadDatabase();
    processInputFile(file);
}

void BitcoinExchange::loadDatabase()
{
    // open file
    std::ifstream fileStream("data.csv");
    if (!fileStream)
        std::cerr << RED << "Error: could not open database file (data.csv)." << RESET << std::endl;
    
    // get line / skip column header
    std::string row;
    getline(fileStream, row);

    // get date & exchange rate from rows and assign to map
    while (getline(fileStream, row))
    {
        std::string date = row.substr(0, 10);
        float exchangeRate = std::atof(row.substr(11).c_str()); //
        _database.insert(std::make_pair(date, exchangeRate));
    } 
}

void BitcoinExchange::processInputFile(const std::string &file)
{
    Result res;
    
    // -- FILE --
    std::ifstream fileStream(file);
    if (!fileStream)
        std::cerr << RED << "Error: could not open file." << RESET << std::endl;
    
    // -- HEADER --
    std::string row;
    parseColumnHeader(fileStream, row);

    // -- ROWS --
    while (getline(fileStream, row))
    {
        parseRow(row, res);
        if (!(printError(res)))
            computeRowValueWithExchangeRate(res);
    }
}

void BitcoinExchange::parseRow(std::string &row, Result &res)
{
    std::istringstream iss(row);
    
    // parse date
    std::string date;
    iss >> date;
    if (!(isValidDate(date)))
    {
        res.errorMsg = std::string("Error: bad input => '") 
                + date;
        res.errorFound = true;
        return ;
    }

    // parse "|"
    std::string bar;
    iss >> bar;
    if (bar != "|")
    {
        res.errorMsg = std::string("Error: bad input => '")
                + bar
                + "'. Should only be '|'.";
        res.errorFound = true;
        return ;
    }

    // parse value
    float value;
    iss >> value;
    if (value < 0)
    {
        res.errorMsg = std::string("Error: not a positive number.");
        res.errorFound = true;
        return ;
    }

    if (value > 1000)
    {
        res.errorMsg = std::string("Error: too large a number.");
        res.errorFound = true;
        return ;
    }

    // parse input that's left after supposed end
    std::string leftover;
    iss >> leftover;
    if (!leftover.empty())
    {
        res.errorMsg = std::string("Error: bad input => '")
                + leftover;
        res.errorFound = true;
        return ;
    }
    
    res.errorFound = false;
    res.date = date;
    res.value = value;
}

void BitcoinExchange::parseColumnHeader(std::ifstream &fileStream, std::string &line)
{
    getline(fileStream, line);
    std::string header = "date | value";
    if (line != header)
    {
        std::cerr << RED << "Error: bad input => '" << line << "'. Should be 'date | value'." << RESET << std::endl;
        return ;
    }
    std::cout << line << std::endl;
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
    // check format of date
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    // check if all numbers
    for (int i = 0; i < 10; i++)
    {
        if (!(i == 4 || i == 7))
        {
            if (!isdigit(date[i]))
                return false; 
        }
    }
    
    // split up into subcategories of date
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    // check if valid date
    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);

    int curYear  = local->tm_year + 1900;
    int curMonth = local->tm_mon + 1;
    int curDay   = local->tm_mday;
    
    if (!((0 <= year) && (year <= curYear)))
        return false;

    if (!((month >= 1 && month <= 12)))
        return false;
    
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };
    
    if (isLeapYear(year))
        daysInMonth[1] = 29;
        
    if (!(day >= 1 && day <= daysInMonth[month - 1]))
        return false;

    // make sure date is not after current date
    if (year == curYear)
    {
        if (month > curMonth)
            return false;
        if (month == curMonth)
        {
            if(day > curDay)
                return false;
        }
    }
    
    return true;
}

/*
A year is a leap year if it is divisible by 4, 
except for century years (ending in 00) which must be divisible by 400. 
Formula: (Year % 4 == 0 AND Year % 100 != 0) OR (Year % 400 == 0). 
For instance, 2024 is a leap year (divisible by 4), 1900 was not (divisible by 100 but not 400), 
and 2000 was.
*/
bool BitcoinExchange::isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool BitcoinExchange::printError(Result &res)
{
    if (res.errorFound)
    {
        std::cerr << RED << res.errorMsg << RESET << std::endl;
        return true;
    }

    return false; // no error printed
}

/*
Your program should display on the standard output the result of the value multiplied
by the exchange rate according to the date indicated in your database.
*/
void BitcoinExchange::computeRowValueWithExchangeRate(Result &res)
{
    std::map<std::string, float>::iterator it = _database.find(res.date);
    if (it == _database.end()) // if date not found
    {
        it = _database.lower_bound(res.date);
        
        // edgecase (if input.csv date is too early for data.csv)
        if (it == _database.begin())
        {
            std::cerr << RED << "Error: no Bitcoin exchange rate available yet for this date." << RESET << std::endl;
            return ;
        }
        it--;
    }
    
    float matchingExchangeRate = it->second; // second is the value, first is the key
    float convertedValue = res.value * matchingExchangeRate; 

    std::cout << res.date << " => " << res.value << GREEN << " = " << convertedValue << RESET << std::endl;
}

BitcoinExchange::BitcoinExchange() 
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _database(other._database)
{}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
        _database = other._database;
    return *this;
}

BitcoinExchange::~BitcoinExchange() 
{}