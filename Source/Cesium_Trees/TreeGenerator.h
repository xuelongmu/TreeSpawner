#pragma once
#include <random>
#include <vector>


struct Tree
{
	// Values are in standard Unreal Engine coordinates (centimeters)
	float positionX;
	float positionY;
	float positionZ;
	float height;
	float canopyRadius;
};


class TreeGenerator
{
public:
	TreeGenerator();

	std::vector<Tree>& GenerateTrees(size_t Size);

	std::vector<Tree> trees;
};
