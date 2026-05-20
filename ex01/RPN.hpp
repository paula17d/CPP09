/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 21:47:42 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/20 23:25:26 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <stdexcept>
#include <list>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define ORANGE "\033[38;5;208m"
#define BLUE "\033[34m"
#define LIGHT_GREEN "\033[38;5;120m"
#define RESET "\033[0m"

class RPN
{
    private:
        std::list<int> _storage;
        // constructor
        RPN(); // bc should only be instantiated w equation
    
    public:
        // personalized constructor
        RPN(std::string equation);
        // copy constructor
        RPN(const RPN& other);
        // copy assignment operator
        RPN& operator=(const RPN& other);
        // destructor
        ~RPN();
};

#endif