#include "GameWorld.h"

GameWorld::GameWorld() : mapTree(), shaperTree() {}

void GameWorld::initializeGame(std::vector<Isle *> places, std::vector<RealmShaper *> players)
{
    shaperTree.initializeTree(players);
    mapTree.initializeMap(places);
}

Map& GameWorld::getMapTree()
{
    return mapTree;
}
ShaperTree& GameWorld::getShaperTree()
{
    return shaperTree;
}

void GameWorld::exploreArea(RealmShaper *realmShaper, Isle *isle)
{
    if (!realmShaper || !isle || !hasAccess(realmShaper, isle))
    {
        return;
    }

    realmShaper->collectItem(isle->getItem());

    bool isFull = isle->increaseShaperCount();

    if (isFull)
    {
        mapTree.remove(isle);
    }
}

bool GameWorld::hasAccess(RealmShaper *realmShaper, Isle *isle)
{
    bool hasAccess = false;

    int playerDepth = shaperTree.getDepth(realmShaper);
    int mapDepth = mapTree.getDepth();
    int totalShaperTreeHeight = shaperTree.getDepth();
    int requiredDepth = mapTree.calculateMinMapDepthAccess(playerDepth, totalShaperTreeHeight, mapDepth);
    int isleDepth = mapTree.getIsleDepth(isle);

    hasAccess = (isleDepth <= requiredDepth);

    return hasAccess;
}

void GameWorld::craft(RealmShaper *shaper, const std::string &isleName)
{
    // TODO: Check energy and craft new isle if possible
    // Use std::cout << "[Energy] " << shaperName << " has enough energy points: " << shaperEnergyLevel << std::endl;
    // Use std::cout << "[Craft] " << shaperName << " crafted new Isle " << isleName << std::endl;
    // Use std::cout << "[Energy] " << shaperName << " does not have enough energy points: " << shaperEnergyLevel << std::endl;
}


void GameWorld::displayGameState()
{
    //mapTree.displayMap();
    //shaperTree.displayTree();
}

// TODO: Implement functions to read and parse Access and Duel logs


void GameWorld::processGameEvents(const std::string &accessLogsFile, const std::string &duelLogsFile)
{
    // TODO:
    // Read logs
    // For every 5 access, 1 duel happens
    // If there are still duel logs left after every access happens duels happens one after other

    // This function should call exploreArea and craft functions

    // Use displayGameState();
}



void GameWorld::saveGameState(const std::string &currentIsles, const std::string &currentWorld, const std::string &currentShapers, const std::string &currentPlayerTree)
{
    mapTree.writeIslesToFile(currentIsles);
    mapTree.writeToFile(currentWorld);
    shaperTree.writeToFile(currentPlayerTree);
    shaperTree.writeShapersToFile(currentShapers);
}