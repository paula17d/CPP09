/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 21:47:09 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/06 01:50:43 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{}

// TODO: refactor into helper functions
RPN::RPN(std::string equation)
{
    for (unsigned long i = 0; i < equation.size(); i++)
    {
        // if it's 0-9
        if (equation[i] >= 48 && equation[i] <= 57)
        {
            int num = equation[i] - '0';
            _storage.push(num); // push onto stack
        }

        // else if it's operator
        else if (equation[i] == '+' || equation[i] == '-' || equation[i] == '/' || equation[i] == '*')
        {
            if (_storage.size() < 2)
                throw std::runtime_error("Error: invalid RPN expression.");
                
            char operatorType = equation[i];
            int numOne = _storage.top(); // read top element
            _storage.pop(); // remove element
            int numTwo = _storage.top(); // read top element
            _storage.pop(); // remove element
            
            // TODO: potentially turn this into a switch case thingy instead of if/else
            int result;
            if (operatorType == '+')
                result = numTwo + numOne;
            else if (operatorType == '-')
                result = numTwo - numOne;
            else if (operatorType == '/')
                result = numTwo / numOne;
            else if (operatorType == '*')
                result = numTwo * numOne;
            
            _storage.push(result);
        }

        // else if it's space
        else if (equation[i] == ' ')
        {}
        
        // else (error)
        else
            throw std::runtime_error("Error: invalid RPN expression."); // TODO: fix layout
    }

    // check how many numbers are left in the stack
    if (_storage.size() > 1)
        throw std::runtime_error("Error: invalid RPN expression.");
    
    // print result
    int equationResult = _storage.top();
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
