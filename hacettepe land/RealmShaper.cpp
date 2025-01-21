#include "RealmShaper.h"
#include <fstream>
#include <sstream>
#include <iostream>

#define NECESSARY_ENERGY 2000 // Necessary energy to craft an Isle

RealmShaper::RealmShaper(std::string name, int honour) : name(name)
{
    this->honour = honour;
}

const std::string &RealmShaper::getName() const
{
    return this->name;
}

int RealmShaper::getEnergyLevel()
{
    return this->collectedEnergyPoints;
}

int RealmShaper::getHonour()
{
    return this->honour;
}

void RealmShaper::gainHonour()
{
    this->honour += 150;
}

void RealmShaper::loseHonour()
{
    this->honour -= 150;
}

void RealmShaper::collectItem(Item item)
{
    this->collectedEnergyPoints += item;
}

void RealmShaper::loseEnergy()
{
    this->collectedEnergyPoints -= NECESSARY_ENERGY;
}

bool RealmShaper::hasEnoughEnergy()
{
    return this->collectedEnergyPoints >= NECESSARY_ENERGY;
}


std::vector<RealmShaper *> RealmShaper::readFromFile(const std::string &filename) {
    std::vector<RealmShaper *> players;

    std::ifstream file(filename);

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string player;
        int honor;

        if (lineStream >> player >> honor) {
            players.push_back(new RealmShaper(player, honor));
        }
    }

    file.close();
    return players;
}



bool RealmShaper::operator==(const RealmShaper &other) const {
    return this->name == other.name;
}


std::ostream &operator<<(std::ostream &os, const RealmShaper &p) {
    return os << "Name: " << p.name << ", Honour: " << p.honour;
}

