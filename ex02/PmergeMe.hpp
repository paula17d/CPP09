/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:56:50 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/18 01:36:36 by pdrettas         ###   ########.fr       */
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
        std::vector<int> vec; // TODO: change naming later
        std::deque<int> deq;
        std::vector<std::pair<int, int>> originalPairs;
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
        std::vector<int> fordJohnsonAlgorithm(std::vector<int> &sequence);
        void extractLeftoverElement(std::vector<int> &inputSequence, unsigned int &leftoverElement, bool &leftoverFound);
        void createAndSortPairs(bool &firstPairing, std::vector<int> &inputSequence, std::vector<std::pair<int, int>> &pairs, std::vector<int> &smallerElementSequence, std::vector<int> &largerElementSequence);
        void calculateJacobsthalSequence(std::vector<int> &jacobsthalSequence, std::vector<int> &smallerElementSequence);
        void generateJacobsthalInsertionOrder(std::vector<int> &insertionOrder, std::vector<int> &jacobsthalSequence, std::vector<int> &smallerElementSequence);
        void insertPendElementsIntoMainChain(std::vector<int> &insertionOrder, std::vector<std::pair<int, int>> &pairs, std::vector<int> &smallerElementSequence, std::vector<int> &largerElementSequence);
        void addLeftoverElement(unsigned int &leftoverElement, bool &leftoverFound, std::vector<int> &largerElementSequence);
        
    };

std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec);
std::ostream &operator<<(std::ostream &out, const std::deque<int> &deque);

#endif