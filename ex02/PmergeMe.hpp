/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:56:50 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/20 01:34:37 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <stdexcept>
#include <algorithm>
#include <chrono>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define ORANGE "\033[38;5;208m"
#define BLUE "\033[34m"
#define LIGHT_GREEN "\033[38;5;120m"
#define PINK "\033[38;5;205m"
#define RESET "\033[0m"

/*
You must use at least two different containers in your code 
to validate this exercise.
*/
class PmergeMe
{
    private:
        std::vector<unsigned int> vec;
        std::deque<unsigned int> deq;

        // constructor
        PmergeMe(); // bc should only be instantiated w integers
    
    public:
        // personalized constructor
        PmergeMe(char **inputSequence);
        // copy constructor
        PmergeMe(const PmergeMe& other);
        // copy assignment operator
        PmergeMe& operator=(const PmergeMe& other);
        // destructor
        ~PmergeMe();
        
        // member functions
        void parseInputAndFillContainers(char **inputSequence);
        std::vector<unsigned int> fordJohnsonAlgorithm(std::vector<unsigned int> &sequence);
        void extractLeftoverElement(std::vector<unsigned int> &inputSequence, unsigned int &leftoverElement, bool &leftoverFound);
        void createAndSortPairs(std::vector<unsigned int> &inputSequence, std::vector<std::pair<unsigned int, unsigned int>> &pairs, std::vector<unsigned int> &smallerElementSequence, std::vector<unsigned int> &largerElementSequence);
        void calculateJacobsthalSequence(std::vector<unsigned int> &jacobsthalSequence, std::vector<unsigned int> &smallerElementSequence);
        void generateJacobsthalInsertionOrder(std::vector<unsigned int> &insertionOrder, std::vector<unsigned int> &jacobsthalSequence, std::vector<unsigned int> &smallerElementSequence);
        void insertPendElementsIntoMainChain(std::vector<unsigned int> &insertionOrder, std::vector<std::pair<unsigned int, unsigned int>> &pairs, std::vector<unsigned int> &smallerElementSequence, std::vector<unsigned int> &largerElementSequence);
        void addLeftoverElement(unsigned int &leftoverElement, bool &leftoverFound, std::vector<unsigned int> &largerElementSequence);
    };

std::ostream &operator<<(std::ostream &out, const std::vector<unsigned int> &vec);
std::ostream &operator<<(std::ostream &out, const std::deque<unsigned int> &deque);

#endif