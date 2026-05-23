/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 21:47:09 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/23 18:20:41 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{}

RPN::RPN(std::string equation) 
{
    for (unsigned long i = 0; i < equation.size(); i++)
    {
        // parse number
        if (equation[i] >= '0' && equation[i] <= '9')
        {
            // no multi-digit numbers (ex. 54)
            if (i > 0 && equation[i - 1] >= '0' && equation[i - 1] <= '9')
                throw std::runtime_error("Error: invalid RPN expression.");

            // previous char shouldnt be a digit
            if (i > 0 && equation[i - 1] != ' ')
                throw std::runtime_error("Error: invalid RPN expression.");

            // next char should be space or end of string
            if (i + 1 < equation.size() && equation[i + 1] != ' ')
                throw std::runtime_error("Error: invalid RPN expression.");

            int num = equation[i] - '0';
            _storage.push_front(num);
        }
        // parse operator
        else if (equation[i] == '+' || equation[i] == '-' || equation[i] == '/' || equation[i] == '*')
        {
            if (_storage.size() < 2)
                throw std::runtime_error("Error: invalid RPN expression.");
                
            char operatorType = equation[i];
            
            int numOne = _storage.front();
            _storage.pop_front();
            int numTwo = _storage.front();
            _storage.pop_front();
            
            int result;
            if (operatorType == '+')
                result = numTwo + numOne;
            else if (operatorType == '-')
                result = numTwo - numOne;
            else if (operatorType == '/')
            {
                if (numOne == 0)
                    throw std::runtime_error("Error: division by zero.");

                result = numTwo / numOne;
            }
            else if (operatorType == '*')
                result = numTwo * numOne;
            
            _storage.push_front(result);
        }
        // skip space
        else if (equation[i] == ' ')
        {}
        else
            throw std::runtime_error("Error: invalid RPN expression.");
    }

    // check how many numbers are left in the stack
    if (_storage.size() != 1)
        throw std::runtime_error("Error: invalid RPN expression.");
    
    // print result
    int equationResult = _storage.front();
    std::cout << equationResult << std::endl;
}

RPN::RPN(const RPN& other)
{
    _storage = other._storage;
}

RPN& RPN::operator=(const RPN& other) 
{
    if (this != &other) 
    {
        _storage = other._storage;
    }
    
    return *this;
}

RPN::~RPN()
{}
