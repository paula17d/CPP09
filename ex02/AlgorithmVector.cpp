/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlgorithmVector.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 20:18:31 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/20 18:34:55 by pauladretta      ###   ########.fr       */
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
std::vector<unsigned int> PmergeMe::fordJohnsonAlgorithm(std::vector<unsigned int> &inputSequence) // TODO: potentially pass without reference 
{
    std::vector<std::pair<unsigned int, unsigned int>> pairs;
    std::vector<unsigned int> smallerElementSequence;
    std::vector<unsigned int> largerElementSequence;
    
    if (inputSequence.size() <= 1) // so the recursion doesnt call itself forever (starts unwinding phase)
    {
        std::cout << GREEN << "returned here - top" << RESET << std::endl;
        return inputSequence;
    }
    
    unsigned int leftoverElement;
    bool leftoverFound = false;
    extractLeftoverElement(inputSequence, leftoverElement, leftoverFound);
    createAndSortPairs(inputSequence, pairs, smallerElementSequence, largerElementSequence);

    std::cout << RED << "+++++ RECURSIVE CALL +++++" << RESET << std::endl;
    largerElementSequence = fordJohnsonAlgorithm(largerElementSequence); // enters reaching breaking point (<) at peak when only biggest num left 

    std::vector<unsigned int> jacobsthalSequence; 
    calculateJacobsthalSequence(jacobsthalSequence, smallerElementSequence);

    std::vector<unsigned int> insertionOrder;
    generateJacobsthalInsertionOrder(insertionOrder, jacobsthalSequence, smallerElementSequence);
    insertPendElementsIntoMainChain(insertionOrder, pairs, smallerElementSequence, largerElementSequence);
    addLeftoverElement(leftoverElement, leftoverFound, largerElementSequence);

    std::cout << GREEN << "returned here - bottom" << RESET << std::endl;
    return largerElementSequence; // TODO: rename to main chain & pend chain
}


// --HELPER FUNCTIONS

void PmergeMe::extractLeftoverElement(std::vector<unsigned int> &inputSequence, unsigned int &leftoverElement, bool &leftoverFound)
{
    if (inputSequence.size() % 2 != 0)
    {
        leftoverFound = true;
        leftoverElement = inputSequence.back(); 
        std::cout << "leftoverElement = " << leftoverElement << std::endl;  
        inputSequence.pop_back();
    }
}

// -- sort input numbers into larger Elements and smaller Elements (one pair per loop)
void PmergeMe::createAndSortPairs(std::vector<unsigned int> &inputSequence, std::vector<std::pair<unsigned int, unsigned int>> &pairs, std::vector<unsigned int> &smallerElementSequence, std::vector<unsigned int> &largerElementSequence)
{
    std::vector<unsigned int>::const_iterator it;
    
    for (it = inputSequence.begin(); it != inputSequence.end(); it += 2)
    {
        std::cout << BLUE << "************** LOOP ITERATION [Pair Creation]  **************" << RESET << std::endl;
        // (make pairs from the current sequence, sort the pairs within for left is smaller, right is bigger. now we put them into a new small sequence, and new big sequence again. within the bigger one, create pairs again and so on....)
        // recursion happens to sort the main chain 
        
        // **** 3.1: group into pairs
        // get two numbers and create/add them as a pair to the pair vector
        unsigned int elementOne = *it;
        std::cout << "elementOne = " << elementOne << std::endl;
        unsigned int elementTwo = *(it + 1);
        std::cout << "elementTwo = " << elementTwo << std::endl;
        pairs.emplace_back(elementOne, elementTwo); // now have to move the pair iterator 2 ahead
        std::cout << "pair = {" << pairs.back().first << ", " << pairs.back().second << "}" << std::endl;
        
        // sort each pair (left should be smaller, right should be bigger) (back() accesses the last element pair in the vector)
        if (!(pairs.back().first < pairs.back().second))
            std::swap(pairs.back().first, pairs.back().second);
        std::cout << "sorted pair = {" << pairs.back().first << ", " << pairs.back().second << "}" << std::endl;
        std::cout << ORANGE << "$comparison$" << RESET << std::endl;
        
        // **** 3.2: "split up" each pair internally (create two sequences: larger elements sequence, smaller elements sequence)
        // put left num in A sequence, and right num in B sequence
        smallerElementSequence.push_back(pairs.back().first);
        std::cout << "smallerElementSequence = " << smallerElementSequence << std::endl;
        largerElementSequence.push_back(pairs.back().second);
        std::cout << "largerElementSequence = " << largerElementSequence << std::endl;
    }
}

// @@@@ part ONE [decide order of insertion]
// generate the amount of jacobsthal numbers needed
void PmergeMe::calculateJacobsthalSequence(std::vector<unsigned int> &jacobsthalSequence, std::vector<unsigned int> &smallerElementSequence)
{   
    unsigned int prevPrevNum = 0; // jt formula needs those two numbers (0, 1) as base to calculate next numbers in following loop
    unsigned int prevNum = 1;

    // building the sequence number by number (0, 1, 1, 3, 5, 11, ...) (without 0, 1) (basically defining ranges (each num is a starting point))
    while (true)
    {
        unsigned int nextJtNum = prevNum + 2 * prevPrevNum; // b -> previous number, a -> previous previous number
        if (nextJtNum > static_cast<unsigned int>(smallerElementSequence.size())) // .
            break;

        jacobsthalSequence.push_back(nextJtNum); // add next number to JT sequence

        prevPrevNum = prevNum;
        prevNum = nextJtNum;
    }
    std::cout << LIGHT_GREEN << "jacobsthalSequence: " << jacobsthalSequence << RESET << std::endl;
}

// take numbers from above and with that insert each range in reverse (1.       3, 2.     5, 4.     11, 10, 9, 8, 7, 6.)
void PmergeMe::generateJacobsthalInsertionOrder(std::vector<unsigned int> &insertionOrder, std::vector<unsigned int> &jacobsthalSequence, std::vector<unsigned int> &smallerElementSequence)
{
    unsigned int previousJtNum = 1;

    for (size_t i = 0; i < jacobsthalSequence.size(); ++i)
    {
        unsigned int currentJtNum = jacobsthalSequence[i];

        for (unsigned int j = currentJtNum; j > previousJtNum; --j) // start at current Jt num, go backwards, until previous jacobsthal num -> for (int j = 5; j > 3; --j) add 4 (so 1 3 2 5 4)
            insertionOrder.push_back(j);

        // if (currentJtNum == 1)
        //     insertionOrder.push_back(1);

        previousJtNum = currentJtNum;
    }

    for (unsigned int j = static_cast<unsigned int>(smallerElementSequence.size()); j > previousJtNum; --j) // since jt only defines blocks (1, 2-3, 4-5, 6-11,...) but possible to have 8 elements so insert everything thats missing depending on sequence size // ex. 1 3 2 5 4 8 7 6 (even tho next block would be at 11)
        insertionOrder.push_back(j);
    
    std::cout << LIGHT_GREEN << "insertionOrder: " << insertionOrder << RESET << std::endl;
}

// @@@@ part TWO [do actual sorting & insertion]
// --NOW: that i got the order that needs to be implemented (1, 3, 2, 5, 4,  ...) ,
// using jacobsthal and binary search together (less comparisons overall)
void PmergeMe::insertPendElementsIntoMainChain(std::vector<unsigned int> &insertionOrder, std::vector<std::pair<unsigned int, unsigned int>> &pairs, std::vector<unsigned int> &smallerElementSequence, std::vector<unsigned int> &largerElementSequence)
{
    // insert first pend element directly according to algorithm
    // if (!smallerElementSequence.empty())
    // {
    //  // not needed in loop bc doesnt even enter loop if size is 0/empty
    //     largerElementSequence.insert(largerElementSequence.begin(), smallerElementSequence[insertionOrder[0] - 1]);
    // std::cout << "paula " << *largerElementSequence.begin() << std::endl;
    // std::cout << "pppp " << smallerElementSequence[insertionOrder[0] - 1] << std::endl;
    // }

    for (int i = 0; i < static_cast<int>(insertionOrder.size()); i++) // loop goes thru jacobsthal insertion order (1, 3, 2, 5, 4, ...)
    {
        // TODO: apparently here and above is a bug somewhere here. ./PmergeMe 5 2 6 9 4 3 7 4 2 3 1 2 3 4 8 9 4 3 2 4 2 5 8 2 3 5 6 does not get sorted.
        if (insertionOrder[i] == 1)
        {
            if (!smallerElementSequence.empty())
            {
                largerElementSequence.insert(largerElementSequence.begin(), smallerElementSequence[0]);
                std::cout << "*begin oben " << *largerElementSequence.begin() << std::endl;
                std::cout << "element to add oben " << smallerElementSequence[0] << std::endl;
            }
            continue;       
        }
    
        int index = insertionOrder[i] - 1; // index needs to be -1 bc (vector) indexes start w 0 // (-1) bc ex. looking for third element in smallerElementSequence which has index 2
        unsigned int elementToInsert = smallerElementSequence[index]; // this needs to be inserted in he largerElemenSequence/mainChain (with .insert) 
        std::cout << PINK << "next smaller Element to be inserted into mainChain: " << elementToInsert << RESET << std::endl;

        // at this point, we have the actual number that we want to insert.
        // NOW, we need to find its larger partner from initial pair (which also appears in the largerElementsequence)
        unsigned int largerPairPartner = pairs[index].second; // the index in the smallerElementSequence is the same index in vec pairs for the same number.
        std::cout << PINK << "pairLargerPartner: " << largerPairPartner << RESET << std::endl;
        
        // look for position of largerPairPartner in largerElementSequence/main chain
        auto positionLargerPairPartner = std::find(largerElementSequence.begin(), largerElementSequence.end(), largerPairPartner); 

        // find where to insert smaller element based on its number in the range of beginning to larger pair element in main chain
        auto positionElementToInsert = std::lower_bound(largerElementSequence.begin(), positionLargerPairPartner, elementToInsert);

        // insert smaller element
        largerElementSequence.insert(positionElementToInsert, elementToInsert);
        
        std::cout << "* begin unten " << *largerElementSequence.begin() << std::endl;
        std::cout << "element to instert unetn " << elementToInsert << std::endl;
        std::cout << "*position unten " << *positionElementToInsert << std::endl;
        // exit(0);
    }
}

void PmergeMe::addLeftoverElement(unsigned int &leftoverElement, bool &leftoverFound, std::vector<unsigned int> &largerElementSequence)
{
    if (leftoverFound)
    {
        std::vector<unsigned int>::iterator pos = std::lower_bound(largerElementSequence.begin(), largerElementSequence.end(), leftoverElement);
        largerElementSequence.insert(pos, leftoverElement); // inserted at the position that lower_bound found closest        
        std::cout << "leftoverElement = " << leftoverElement << std::endl;
    }
}
