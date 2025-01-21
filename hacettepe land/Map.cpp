#include "Map.h"
#include <iostream>
#include <queue>
#include <vector>
#include <functional>


Map::Map()
{
    this->root = nullptr;
}
void Map::deleteTree(MapNode *node)
{
    if (!node)
        return;

    deleteTree(node->left);
    deleteTree(node->right);

    delete node->isle;
    delete node;
}

Map::~Map()
{
    deleteTree(root);
}


void Map::initializeMap(std::vector<Isle *> isles)
{
    for (Isle *isle : isles)
    {
        insert(isle);
    }
    populateWithItems();
}

MapNode *Map::rotateRight(MapNode *current)
{
    MapNode *newRoot = current->left;
    current->left = newRoot->right;
    newRoot->right = current;

    current->height = std::max(height(current->left), height(current->right)) + 1;
    newRoot->height = std::max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

MapNode *Map::rotateLeft(MapNode *current)
{
    MapNode *newRoot = current->right;
    current->right = newRoot->left;
    newRoot->left = current;

    current->height = std::max(height(current->left), height(current->right)) + 1;
    newRoot->height = std::max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

int Map::calculateMinMapDepthAccess(int playerDepth, int totalShaperTreeHeight, int totalMapDepth)
{

    double depthRatio = static_cast<double>(playerDepth) / totalShaperTreeHeight;

    int minDepthAccess = static_cast<int>(totalMapDepth * depthRatio);

    return std::max(minDepthAccess, 0);
}



int Map::height(MapNode *node)
{
    return node ? node->height : 0;
}

MapNode *Map::insert(MapNode *node, Isle *isle)
{
    MapNode *newNode = nullptr;

    if (!node)
        return new MapNode(isle);

    if (*isle < *(node->isle))
        node->left = insert(node->left, isle);
    else if (*isle > *(node->isle))
        node->right = insert(node->right, isle);
    else
        return node;

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = height(node->left) - height(node->right);

    switch (balance)
    {
        case 2:
            if (*isle < *(node->left->isle))
                return rotateRight(node);
        if (*isle > *(node->left->isle))
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        break;

        case -2:
            if (*isle > *(node->right->isle))
                return rotateLeft(node);
        if (*isle < *(node->right->isle))
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        break;

        default:
            break;
    }

    return node;
}



void Map::insert(Isle *isle)
{
    root = insert((root), isle);

    // you might need to insert some checks / functions here depending on your implementation
}

MapNode *Map::remove(MapNode *node, Isle *isle)
{

    // TODO: Recursively delete isle from the tree
    // Will be called if there is overcrowding
    // returns node
    // Use std::cout << "[Remove] " << "Tree is Empty" << std::endl;

    return node;
}


void Map::remove(Isle *isle)
{
    root = remove((root), isle);
    // you might need to insert some checks / functions here depending on your implementation
}

void Map::postOrderItemDrop(MapNode *current, int &count)
{
    if (!current) return;

    postOrderItemDrop(current->left, count);
    postOrderItemDrop(current->right, count);

    count++;
    if (count % 3 == 0)
    {
        current->isle->setItem(GOLDIUM);
        std::cout << "[Item Drop] GOLDIUM dropped on Isle: " << current->isle->getName() << std::endl;
    }
}

void Map::preOrderItemDrop(MapNode *current, int &count)
{
    if (!current) return;

    count++;
    if (count % 5 == 0)
    {
        current->isle->setItem(EINSTEINIUM);
        std::cout << "[Item Drop] EINSTEINIUM dropped on Isle: " << current->isle->getName() << std::endl;
    }

    preOrderItemDrop(current->left, count);
    preOrderItemDrop(current->right, count);
}



MapNode *Map::findFirstEmptyIsle(MapNode *node)
{
    if (!node)
        return nullptr;

    std::queue<MapNode *> q;
    q.push(node);

    do
    {
        MapNode *current = q.front();
        q.pop();


        if (current->isle->getItem() == EMPTY)
        {
            return current;
        }
        else if (current->left)
        {
            q.push(current->left);
        }
        else if (current->right)
        {
            q.push(current->right);
        }

    } while (!q.empty());

    return nullptr;
}



void Map::dropItemBFS()
{
    if (!root) return;

    std::queue<MapNode *> q;
    q.push(root);

    do
    {
        MapNode *current = q.front();
        q.pop();

        if (current->isle->getItem() == EMPTY)
        {
            current->isle->setItem(AMAZONITE);
            std::cout << "[BFS Drop] AMAZONITE dropped on Isle: " << current->isle->getName() << std::endl;
            return;
        }

        if (current->left)
        {
            q.push(current->left);
        }
        else if (current->right)
        {
            q.push(current->right);
        }

    } while (!q.empty());

    std::cout << "[BFS Drop] No eligible Isle found for AMAZONITE drop." << std::endl;
}



void Map::displayMap()
{
    std::cout << "[World Map]" << std::endl;
    display(root, 0, 0);
}

int Map::getDepth(MapNode *node)
{


    MapNode *current = root;
    int depth = 0;

    do
    {
        if (node->isle->getName() == current->isle->getName())
            return depth;

        current = (*node->isle < *current->isle) ? current->left : current->right;
        depth++;
    } while (current);

    return -1;
}

int Map::getIsleDepth(Isle *isle)
{
    MapNode *current = root;
    int depth = 0;

    do
    {
        if (isle->getName() == current->isle->getName())
            return depth;

        current = (*isle < *current->isle) ? current->left : current->right;
        depth++;
    } while (current);

    return -1;
}




int Map::getDepth()
{
    return calculateDepth(root);
}

int Map::calculateDepth(MapNode *node)
{
    if (!node)
        return 0;

    int leftDepth = calculateDepth(node->left);
    int rightDepth = calculateDepth(node->right);

    return std::max(leftDepth, rightDepth) + 1;
}



void Map::populateWithItems()
{
    int postOrderCount = 0;
    int preOrderCount = 0;

    postOrderItemDrop(root, postOrderCount);
    preOrderItemDrop(root, preOrderCount);
}

Isle *Map::findIsle(Isle isle)
{
    MapNode *current = root;

    do
    {
        if (!current)
            return nullptr;

        if (*current->isle == isle)
            return current->isle;

        current = (isle < *current->isle) ? current->left : current->right;

    } while (current);

    return nullptr;
}



Isle *Map::findIsle(std::string name)
{
    MapNode *current = root;

    do
    {
        if (!current)
            return nullptr;

        if (current->isle->getName() == name)
            return current->isle;

        current = (name < current->isle->getName()) ? current->left : current->right;

    } while (current);

    return nullptr;
}



MapNode *Map::findNode(Isle isle)
{
    if (!root) return nullptr;

    if (*root->isle == isle)
        return root;

    if (isle < *root->isle)
    {
        root = root->left ? root->left : nullptr;
        return findNode(isle);
    }

}
MapNode *Map::findNode(std::string name)
{
    if (!root) return nullptr;

    if (root->isle->getName() == name)
        return root;

    if (name < root->isle->getName())
    {

        root = root->left ? root->left : nullptr;
        return findNode(name);
    }

}

void Map::display(MapNode *current, int depth, int state)
{
    // SOURCE:

    if (current->left)
        display(current->left, depth + 1, 1);

    for (int i = 0; i < depth; i++)
        printf("     ");

    if (state == 1) // left
        printf("   ┌───");
    else if (state == 2) // right
        printf("   └───");

    std::cout << "[" << *current->isle << "] - (" << current->height << ")\n"
              << std::endl;

    if (current->right)
        display(current->right, depth + 1, 2);
}

void Map::writeToFile(const std::string &filename)
{
    // TODO: Write the tree to filename output level by level
}

void Map::writeIslesToFile(const std::string &filename)
{
    // TODO: Write Isles to output file in alphabetical order
    // Use std::cout << "[Output] " << "Isles have been written to " << filename << " in in alphabetical order." << std::endl;
}