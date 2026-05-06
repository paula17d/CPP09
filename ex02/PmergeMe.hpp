/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:56:50 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/06 18:25:48 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <stdexcept>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define ORANGE "\033[38;5;208m"
#define BLUE "\033[34m"
#define LIGHT_GREEN "\033[38;5;120m"
#define RESET "\033[0m"

/*
You must use at least two different containers in your code 
to validate this exercise.
*/
class PmergeMe
{
    private:
        std::vector<int> sequenceInVec; // TODO: change naming later
        std::deque<int> sequenceInDeque;
        // constructor
        PmergeMe(); // bc should only be instantiated w integers
    
    public:
        // personalized constructor
        PmergeMe(char **numSequence);
        // copy constructor
        PmergeMe(const PmergeMe& other);
        // copy assignment operator
        PmergeMe& operator=(const PmergeMe& other);
        // destructor
        ~PmergeMe();
};

#endif