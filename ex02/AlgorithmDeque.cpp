/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlgorithmDeque.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 20:18:33 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/20 22:33:27 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*
The process of the below method is called Merge Insertion (The Art of Computer Programming).
This is due to some aspects of merging and some aspects of insertion.

This function starts with the entire original input number sequence
but returns only the resulting main chain (which is 50% the size of the original number sequence and filled with the largest elements)
*/
// each level w recursion, the inputSequence becomes updated (after first recursive call the inputSequence is the largerElementSequnce as input of function)
deque PmergeMe::fordJohnsonAlgorithm(deque &inputSequence)
{
    dequePair pairs;
    deque pendElements;
    deque mainChain;
    
    if (inputSequence.size() <= 1) // so the recursion doesnt call itself forever (starts unwinding phase)
    {
        // std::cout << GREEN << "returned here - top" << RESET << std::endl;
        return inputSequence;
    }
    
    unsigned int leftoverElement;
    bool leftoverFound = false;
    extractLeftoverElement(inputSequence, leftoverElement, leftoverFound);
    createAndSortPairs(inputSequence, pairs, pendElements, mainChain);

    // std::cout << RED << "+++++ RECURSIVE CALL +++++" << RESET << std::endl; // TODO: remove these print statements
    mainChain = fordJohnsonAlgorithm(mainChain); // enters reaching breaking point (<) at peak when only biggest num left 

    deque jacobsthalSequence; 
    calculateJacobsthalSequence(jacobsthalSequence, pendElements);

    deque insertionOrder;
    generateJacobsthalInsertionOrder(insertionOrder, jacobsthalSequence, pendElements);
    insertPendElementsIntoMainChain(insertionOrder, pairs, pendElements, mainChain);
    addLeftoverElement(leftoverElement, leftoverFound, mainChain);

    // std::cout << GREEN << "returned here - bottom" << RESET << std::endl;
    return mainChain;
}


// --HELPER FUNCTIONS

void PmergeMe::extractLeftoverElement(deque &inputSequence, unsigned int &leftoverElement, bool &leftoverFound)
{
    if (inputSequence.size() % 2 != 0)
    {
        leftoverFound = true;
        leftoverElement = inputSequence.back(); 
        // std::cout << "leftoverElement = " << leftoverElement << std::endl;  
        inputSequence.pop_back();
    }
}

// -- sort input numbers into larger Elements and smaller Elements (one pair per loop)
void PmergeMe::createAndSortPairs(deque &inputSequence, dequePair &pairs, deque &pendElements, deque &mainChain)
{
    deque::const_iterator it;
    
    for (it = inputSequence.begin(); it != inputSequence.end(); it += 2)
    {
        // std::cout << BLUE << "************** LOOP ITERATION [Pair Creation]  **************" << RESET << std::endl;
        // (make pairs from the current sequence, sort the pairs within for left is smaller, right is bigger. now we put them into a new small sequence, and new big sequence again. within the bigger one, create pairs again and so on....)
        // recursion happens to sort the main chain 
        
        // **** 3.1: group into pairs
        // get two numbers and create/add them as a pair to the pair deque
        unsigned int elementOne = *it;
        // std::cout << "elementOne = " << elementOne << std::endl;
        unsigned int elementTwo = *(it + 1);
        // std::cout << "elementTwo = " << elementTwo << std::endl;
        pairs.emplace_back(elementOne, elementTwo); // now have to move the pair iterator 2 ahead
        // std::cout << "pair = {" << pairs.back().first << ", " << pairs.back().second << "}" << std::endl;
        
        // sort each pair (left should be smaller, right should be bigger) (back() accesses the last element pair in the deque)
        if (!(pairs.back().first < pairs.back().second))
            std::swap(pairs.back().first, pairs.back().second);
        // std::cout << "sorted pair = {" << pairs.back().first << ", " << pairs.back().second << "}" << std::endl;
        // std::cout << ORANGE << "$comparison$" << RESET << std::endl;
        
        // **** 3.2: "split up" each pair internally (create two sequences: larger elements sequence, smaller elements sequence)
        // put left num in A sequence, and right num in B sequence
        pendElements.push_back(pairs.back().first);
        // std::cout << "pendElements = " << pendElements << std::endl;
        mainChain.push_back(pairs.back().second);
        // std::cout << "mainChain = " << mainChain << std::endl;
    }
}

// @@@@ part ONE [decide order of insertion]
// generate the amount of jacobsthal numbers needed
void PmergeMe::calculateJacobsthalSequence(deque &jacobsthalSequence, deque &pendElements)
{   
    unsigned int prevPrevNum = 0; // jt formula needs those two numbers (0, 1) as base to calculate next numbers in following loop
    unsigned int prevNum = 1;

    // building the sequence number by number (0, 1, 1, 3, 5, 11, ...) (without 0, 1) (basically defining ranges (each num is a starting point))
    while (true)
    {
        unsigned int nextJtNum = prevNum + 2 * prevPrevNum; // b -> previous number, a -> previous previous number
        if (nextJtNum > static_cast<unsigned int>(pendElements.size())) // .
            break;

        jacobsthalSequence.push_back(nextJtNum); // add next number to JT sequence

        prevPrevNum = prevNum;
        prevNum = nextJtNum;
    }
    // std::cout << LIGHT_GREEN << "jacobsthalSequence: " << jacobsthalSequence << RESET << std::endl;
}

// take numbers from above and with that insert each range in reverse (1.       3, 2.     5, 4.     11, 10, 9, 8, 7, 6.)
void PmergeMe::generateJacobsthalInsertionOrder(deque &insertionOrder, deque &jacobsthalSequence, deque &pendElements)
{
    unsigned int previousJtNum = 1;

    if (!pendElements.empty())
        insertionOrder.push_back(1);

    for (size_t i = 0; i < jacobsthalSequence.size(); ++i)
    {
        unsigned int currentJtNum = jacobsthalSequence[i];

        for (unsigned int j = currentJtNum; j > previousJtNum; --j) // start at current Jt num, go backwards, until previous jacobsthal num -> for (int j = 5; j > 3; --j) add 4 (so 1 3 2 5 4)
            insertionOrder.push_back(j);

        previousJtNum = currentJtNum;
    }

    for (unsigned int j = static_cast<unsigned int>(pendElements.size()); j > previousJtNum; --j) // since jt only defines blocks (1, 2-3, 4-5, 6-11,...) but possible to have 8 elements so insert everything thats missing depending on sequence size // ex. 1 3 2 5 4 8 7 6 (even tho next block would be at 11)
        insertionOrder.push_back(j);
    
    // std::cout << LIGHT_GREEN << "insertionOrder: " << insertionOrder << RESET << std::endl;
}

// @@@@ part TWO [do actual sorting & insertion]
// --NOW: that i got the order that needs to be implemented (1, 3, 2, 5, 4,  ...) ,
// using jacobsthal and binary search together (less comparisons overall)
void PmergeMe::insertPendElementsIntoMainChain(deque &insertionOrder, dequePair &pairs, deque &pendElements, deque &mainChain)
{
    for (int i = 0; i < static_cast<int>(insertionOrder.size()); i++) // loop goes thru jacobsthal insertion order (1, 3, 2, 5, 4, ...)
    {
        int index = insertionOrder[i] - 1; // index needs to be -1 bc (deque) indexes start w 0 // (-1) bc ex. looking for third element in pendElements which has index 2
        unsigned int elementToInsert = pendElements[index]; // this needs to be inserted in he largerElemenSequence/mainChain (with .insert) 
        // std::cout << PINK << "next smaller Element to be inserted into mainChain: " << elementToInsert << RESET << std::endl;

        // at this point, we have the actual number that we want to insert.
        // NOW, we need to find its larger partner from initial pair (which also appears in the mainChain)
        unsigned int largerPairPartner = pairs[index].second; // the index in the pendElements is the same index in vec pairs for the same number.
        // std::cout << PINK << "pairLargerPartner: " << largerPairPartner << RESET << std::endl;
        
        // look for position of largerPairPartner in mainChain/main chain
        auto positionLargerPairPartner = std::find(mainChain.begin(), mainChain.end(), largerPairPartner); 

        // find where to insert smaller element based on its number in the range of beginning to larger pair element in main chain
        auto positionElementToInsert = std::lower_bound(mainChain.begin(), positionLargerPairPartner, elementToInsert);

        // insert smaller element
        mainChain.insert(positionElementToInsert, elementToInsert);
    }
}

void PmergeMe::addLeftoverElement(unsigned int &leftoverElement, bool &leftoverFound, deque &mainChain)
{
    if (leftoverFound)
    {
        deque::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), leftoverElement);
        mainChain.insert(pos, leftoverElement); // inserted at the position that lower_bound found closest        
        // std::cout << "leftoverElement = " << leftoverElement << std::endl;
    }
}
