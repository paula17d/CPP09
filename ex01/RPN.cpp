/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 21:47:09 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/20 23:25:40 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{}

RPN::RPN(std::string equation) // TODO: check for edge cases again!
{
    for (unsigned long i = 0; i < equation.size(); i++)
    {
        if (equation[i] >= 48 && equation[i] <= 57)
        {
            int num = equation[i] - '0';
            _storage.push_back(num);
        }
        else if (equation[i] == '+' || equation[i] == '-' || equation[i] == '/' || equation[i] == '*')
        {
            if (_storage.size() < 2)
                throw std::runtime_error("Error: invalid RPN expression.");
                
            char operatorType = equation[i];
            
            int numOne = _storage.back();
            _storage.pop_back();
            int numTwo = _storage.back();
            _storage.pop_back();
            
            int result;
            if (operatorType == '+')
                result = numTwo + numOne;
            else if (operatorType == '-')
                result = numTwo - numOne;
            else if (operatorType == '/')
                result = numTwo / numOne;
            else if (operatorType == '*')
                result = numTwo * numOne;
            
            _storage.push_back(result);
        }
        else if (equation[i] == ' ')
        {}
        else
            throw std::runtime_error("Error: invalid RPN expression.");
    }

    // check how many numbers are left in the stack
    if (_storage.size() > 1)
        throw std::runtime_error("Error: invalid RPN expression.");
    
    // print result
    int equationResult = _storage.back();
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
