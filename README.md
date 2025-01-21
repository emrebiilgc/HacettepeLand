# HacettepeLand
The Realm Shapers RPG System uses binary and AVL trees to manage player rankings, dynamic Isle exploration, and crafting mechanics, emphasizing strategic gameplay, efficient data structures, and real-time world updates.
The Realm Shapers RPG System introduces a new gameplay mechanic where players manage a dynamic game world using advanced data structures like binary trees and AVL trees. The game features two interconnected systems: the Shaper Tree for ranking players and the World Tree for managing Isles in the game world.

Shaper Tree: This is a complete binary tree implemented as an array or vector to rank players. Players can challenge their parents to duels to improve their rankings. Winning or losing duels affects a player’s honor points, and those with zero honor points are removed from the tree. The system supports insertion, deletion, and traversal operations for managing rankings.

World Tree: This AVL tree dynamically manages Isles in the game world, maintaining balance for efficient access and updates. Isles are enriched with items using traversal techniques like post-order, pre-order, and BFS. Overcrowding in Isles results in self-destruction, triggering rebalancing operations.

Gameplay: Players interact with the system by attempting to access Isles, collect items, or craft new Isles. Access is governed by player rank and Isle availability. Duels and crafting mechanics add strategic depth to the game, while logs track player actions for simulation and testing.

The program handles file I/O for initializing data, logging actions, and saving results. It emphasizes dynamic memory allocation, operator overloading, and efficient traversal techniques, creating a robust simulation for real-time strategy and RPG mechanics.
