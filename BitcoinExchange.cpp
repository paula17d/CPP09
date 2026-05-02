/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 11:14:34 by pauladretta       #+#    #+#             */
/*   Updated: 2026/04/30 16:21:08 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/*
str.length()
str.size()
str.empty()
str.substr(pos, len)
str.find("text")
str.append("text")
str.insert(pos, "text")
str.erase(pos, len)
str.compare(other)
*/

/*
A year is a leap year if it is divisible by 4, 
except for century years (ending in 00) which must be divisible by 400. 
Formula: (Year % 4 == 0 AND Year % 100 != 0) OR (Year % 400 == 0). 
For instance, 2024 is a leap year (divisible by 4), 1900 was not (divisible by 100 but not 400), 
and 2000 was.
*/
bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// TODO: include error messages (check subject example)
bool isValidDate(const std::string &date)
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

BitcoinExchange::BitcoinExchange(const std::string &file)
{
    parseFile(file);
}

// TODO: parse first line in file (date | value), still left to do 
// TODO: parse (if empty line in file)
void BitcoinExchange::parseFile(const std::string &file)
{
    // std::string error;
    std::ifstream fileStream(file);
    if (!fileStream)
        std::cerr << "Error: could not open file." << std::endl;
        
    std::string line;

    while (getline(fileStream, line))
    {
        std::istringstream iss(line);
        
        // parse date
        std::string date;
        iss >> date;
        if (!(isValidDate(date)))
        {
            std::cerr << "Error: bad input =>" << date << std::endl;
            continue;   
        }

        // parse "|"
        std::string bar;
        iss >> bar;
        if (bar != "|")
        {
            std::cerr << "Error: bad input => '" << bar << "'. Should only be '|'." << std::endl;
            // std::cerr << "Error: no bar found '|'." << std::endl;
            continue;   
        }

        // parse exchange rate
        float value;
        iss >> value;
        if (value < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;   
        }

        if (value > 1000)
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;   
        }

        // parse input left after supposed end
        std::string leftover;
        iss >> leftover;
        if (!leftover.empty())
        {
            std::cerr << "Error: bad input => " << leftover << std::endl;
            continue;
        }
        
        // save in std::map
        if (data.find(date) != data.end())
        {
            std::cerr << "Error: date already exists, cannot appear more than once. " << date << std::endl;
            continue;
        }
        data.insert(std::make_pair(date, value));
        
        std::cout << line << std::endl;
    }
}
