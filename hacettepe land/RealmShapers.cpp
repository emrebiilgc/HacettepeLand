#include "RealmShapers.h"
#include <cmath>
#include <algorithm>
#include <queue>

ShaperTree::ShaperTree()
{
}

ShaperTree::~ShaperTree() {
    for (size_t i = 0; i < realmShapers.size(); ++i) {
        delete realmShapers[i];
    }
    realmShapers.clear();
}



void ShaperTree::initializeTree(std::vector<RealmShaper *> shapers) {
    for (size_t i = 0; i < shapers.size(); ++i) {
        insert(shapers[i]);
    }
}


int ShaperTree::getSize() {
    return realmShapers.size();
}


std::vector<RealmShaper *> ShaperTree::getTree()
{
    return realmShapers;
}

bool ShaperTree::isValidIndex(int index)
{
    bool isValid = false;

    if(index >= 0 && index < realmShapers.size()) {
        isValid = true;
    }

    return isValid;
}

void ShaperTree::insert(RealmShaper *shaper) {
    realmShapers.push_back(shaper);
}

int ShaperTree::findIndex(RealmShaper *shaper) {
    for (size_t i = 0; i < realmShapers.size(); ++i) {
        if (*realmShapers[i] == *shaper) {
            return i;
        }
    }
    return -1;
}

int ShaperTree::getDepth(RealmShaper *shaper) {
    int index = findIndex(shaper);
    if (index == -1) {
        return -1;
    }
}

int ShaperTree::getDepth() {

    int size = static_cast<int>(realmShapers.size());

    if (size == 0) {
        return -1;
    }

    double depthValue = std::log2(size + 1);

    int depth = static_cast<int>(std::ceil(depthValue));

    return depth - 1;
}

RealmShaper *ShaperTree::getParent(RealmShaper *shaper)
{
    RealmShaper *parent = nullptr;

    // TODO: return parent of the shaper

    return parent;
}

void ShaperTree::replace(RealmShaper *player_low, RealmShaper *player_high) {
    int lowIndex = findIndex(player_low);
    int highIndex = findIndex(player_high);

    if (lowIndex != -1 && highIndex != -1) {
        std::swap(realmShapers[lowIndex], realmShapers[highIndex]);
    }
}


RealmShaper *ShaperTree::findPlayer(RealmShaper shaper) {
    for (size_t i = 0; i < realmShapers.size(); ++i) {
        if (*realmShapers[i] == shaper) {
            return realmShapers[i];
        }
    }
    return nullptr;
}

RealmShaper *ShaperTree::findPlayer(std::string name) {
    for (size_t i = 0; i < realmShapers.size(); ++i) {
        if (realmShapers[i]->getName() == name) {
            return realmShapers[i];
        }
    }
    return nullptr;
}


int ShaperTree::remove(RealmShaper *shaper) {

    int index = findIndex(shaper);
    if (index == -1) {
        return -1;
    }

    delete realmShapers[index];

    for (size_t i = index; i < realmShapers.size() - 1; ++i) {
        realmShapers[i] = realmShapers[i + 1];
    }

    realmShapers.pop_back();

    return index;
}


RealmShaper ShaperTree::duel(RealmShaper *challenger, bool result) {
    int defiant = findIndex(challenger);
    int parent = (defiant - 1) / 2;
    RealmShaper *opponent = realmShapers[parent];

    int outcome = result;

    switch (outcome) {
        case 1: {
            challenger->gainHonour();
            opponent->loseHonour();

            if (opponent->getHonour() <= 0) {
                remove(opponent);
            } else {
                replace(challenger, opponent);
            }
            return *challenger;
        }
        case 0: {
            challenger->loseHonour();
            opponent->gainHonour();

            if (challenger->getHonour() <= 0) {
                remove(challenger);
            }
            return *opponent;
        }
        default:
                std::cerr << "[Error] Invalid duel result." << std::endl;
        return *challenger;
    }
}


std::vector<std::string> ShaperTree::inOrderTraversal(int index) {
    if (!isValidIndex(index)) {
        return {};
    }

    std::vector<std::string> result;

    for (const std::string &name : inOrderTraversal(2 * index + 1)) {result.push_back(name);}

    result.push_back(realmShapers[index]->getName());

    for (const std::string &name : inOrderTraversal(2 * index + 2)) {result.push_back(name);}

    return result;
}


std::vector<std::string> ShaperTree::preOrderTraversal(int index) {
    if (!isValidIndex(index)) {
        return {};
    }

    std::vector<std::string> result;

    result.push_back(realmShapers[index]->getName());

    for (const std::string &name : preOrderTraversal(2 * index + 1)) {result.push_back(name);}

    for (const std::string &name : preOrderTraversal(2 * index + 2)) {result.push_back(name);}

    return result;
}

std::vector<std::string> ShaperTree::postOrderTraversal(int index) {
    if (!isValidIndex(index)) {
        return {};
    }

    std::vector<std::string> result;

    for (const std::string &name : postOrderTraversal(2 * index + 1)) {result.push_back(name);}

    for (const std::string &name : postOrderTraversal(2 * index + 2)) {result.push_back(name);}

    result.push_back(realmShapers[index]->getName());

    return result;
}

void ShaperTree::preOrderTraversal(int index, std::ofstream &outFile) {

    if (!isValidIndex(index)) return;

    outFile << realmShapers[index]->getName() << std::endl;

    preOrderTraversal(2 * index + 1, outFile);
    preOrderTraversal(2 * index + 2, outFile);
}

void ShaperTree::breadthFirstTraversal(std::ofstream &outFile) {
    if (!isValidIndex(0)) {
        return;
    }

    std::queue<int> bfsQueue;
    bfsQueue.push(0);

    do {
        int currentIndex = bfsQueue.front();
        bfsQueue.pop();

        if (outFile.is_open()) {
            outFile << realmShapers[currentIndex]->getName() << " ";
        }

        int leftChildIndex = 2 * currentIndex + 1;
        if (isValidIndex(leftChildIndex)) {
            bfsQueue.push(leftChildIndex);
        }

        int rightChildIndex = 2 * currentIndex + 2;
        if (isValidIndex(rightChildIndex)) {
            bfsQueue.push(rightChildIndex);
        }
    } while (!bfsQueue.empty());

    if (outFile.is_open()) {
        outFile << std::endl;
    }
}


void ShaperTree::displayTree()
{
    std::cout << "[Shaper Tree]" << std::endl;
    printTree(0, 0, "");
}

// Helper function to print tree with indentation
void ShaperTree::printTree(int index, int level, const std::string &prefix)
{
    if (!isValidIndex(index))
        return;

    std::cout << prefix << (level > 0 ? "   └---- " : "") << *realmShapers[index] << std::endl;
    int left = 0;  // TODO: Calculate left index
    int right = 0; // TODO: Calculate right index

    if (isValidIndex(left) || isValidIndex(right))
    {
        printTree(left, level + 1, prefix + (level > 0 ? "   │   " : "")); // ╎
        printTree(right, level + 1, prefix + (level > 0 ? "   │   " : ""));
    }
}

void ShaperTree::writeShapersToFile(const std::string &filename)
{
    // TODO: Write the shapers to filename output level by level
    // Use std::cout << "[Output] " << "Shapers have been written to " << filename << " according to rankings." << std::endl;
}

void ShaperTree::writeToFile(const std::string &filename)
{
    // TODO: Write the tree to filename output pre-order
    // Use std::cout << "[Output] " << "Tree have been written to " << filename << " in pre-order." << std::endl;
}
