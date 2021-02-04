# Tree Spawner Project

This is a application that demonstrates spawning large numbers of trees at randomly generated locations and dimensions.

[Demo video can be viewed here.](https://youtu.be/_Iyv76pFPLo)

### Instructions

**WASD** to move around, **Q** and **E** to change elevation.

**Mouse wheel down** to increase movement speed, **mouse wheel up** to decrease movement speed.

**Left click** to display height and canopy radius info.

**Middle click** or **F** to place new trees.

By default, the spawner will load 10,000 trees on begin play. This value can be tweaked to any value in `BP_TreeSpawner`. The screenshot below demonstrates 200,000 trees with FPS ranging from 30-100.

![screenshot](Screenshot.png)

## Notes

I used a Hierarchial Static Mesh Component (HISM) to store the tree instances.

As the number of trees grew large (100,000+) I made some tweaks to improve performance. I disabled shadows, lowered the LOD of the tree's static mesh, and enabled distance culling (as can be seen in the video).

Adding a new tree with a very large number of trees (e.g. 200,000) in the level caused a lag spike. I believe this is due to the effect of adding another leaf to the HISM "cluster tree" structure.

The project hanged when compiling with the 100,000 header file included, so I rewrote the generator in `TreeGenerator.cpp`
