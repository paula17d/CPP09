/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:56:50 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/20 22:25:13 by pdrettas         ###   ########.fr       */
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
#include <climits>
#include <string>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define ORANGE "\033[38;5;208m"
#define BLUE "\033[34m"
#define LIGHT_GREEN "\033[38;5;120m"
#define PINK "\033[38;5;205m"
#define RESET "\033[0m"

typedef std::vector<unsigned int> vector;
typedef std::deque<unsigned int> deque;
typedef std::vector<std::pair<unsigned int, unsigned int>> vectorPair;
typedef std::deque<std::pair<unsigned int, unsigned int>> dequePair;

class PmergeMe
{
    private:
        std::vector<unsigned int> vec;
        std::deque<unsigned int> deq;

        // constructor
        PmergeMe();
    
    public:
        // personalized constructor
        PmergeMe(char **inputSequence);
        // copy constructor
        PmergeMe(const PmergeMe& other);
        // copy assignment operator
        PmergeMe& operator=(const PmergeMe& other);
        // destructor
        ~PmergeMe();
        
        void parseInputAndFillContainers(char **inputSequence);
        
        template <typename Container>
        void sortContainerAndMeasureTime(Container c, const std::string& containerName);

        template <typename Container>
        void printSortedSequence(const Container &sortedSequence, std::chrono::duration<double, std::micro> &elapsed, const size_t &inputSize, const std::string& containerName);
        
        // member functions [vec]
        vector fordJohnsonAlgorithm(vector &sequence);
        void extractLeftoverElement(vector &inputSequence, unsigned int &leftoverElement, bool &leftoverFound);
        void createAndSortPairs(vector &inputSequence, vectorPair &pairs, vector &pendElements, vector &mainChain);
        void calculateJacobsthalSequence(vector &jacobsthalSequence, vector &pendElements);
        void generateJacobsthalInsertionOrder(vector &insertionOrder, vector &jacobsthalSequence, vector &pendElements);
        void insertPendElementsIntoMainChain(vector &insertionOrder, vectorPair &pairs, vector &pendElements, vector &mainChain);
        void addLeftoverElement(unsigned int &leftoverElement, bool &leftoverFound, vector &mainChain);

        // member functions [deq]
        deque fordJohnsonAlgorithm(deque &sequence);
        void extractLeftoverElement(deque &inputSequence, unsigned int &leftoverElement, bool &leftoverFound);
        void createAndSortPairs(deque &inputSequence, dequePair &pairs, deque &pendElements, deque &mainChain);
        void calculateJacobsthalSequence(deque &jacobsthalSequence, deque &pendElements);
        void generateJacobsthalInsertionOrder(deque &insertionOrder, deque &jacobsthalSequence, deque &pendElements);
        void insertPendElementsIntoMainChain(deque &insertionOrder, dequePair &pairs, deque &pendElements, deque &mainChain);
        void addLeftoverElement(unsigned int &leftoverElement, bool &leftoverFound, deque &mainChain);
};

std::ostream &operator<<(std::ostream &out, const vector &vec);
std::ostream &operator<<(std::ostream &out, const deque &deque);

#endif
