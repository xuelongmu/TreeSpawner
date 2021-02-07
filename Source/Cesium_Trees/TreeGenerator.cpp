#include "TreeGenerator.h"

TreeGenerator::TreeGenerator()
{
}

void TreeGenerator::GenerateTrees(size_t Count)
{
	trees.reserve(Count);
	std::default_random_engine generator;
	std::uniform_real_distribution<float> positionDistribution(0.0, 100000.0);
	std::uniform_real_distribution<float> heightDistribution(2.0, 10000.0);
	std::uniform_real_distribution<float> canopyRadiusDistribution(1.0, 5000.0);

	for (size_t i = 0; i < Count; i++)
	{
		Tree tree
		{
			positionDistribution(generator),
			positionDistribution(generator),
			positionDistribution(generator),
			heightDistribution(generator),
			canopyRadiusDistribution(generator)
		};
		trees.push_back(tree);
	}
	return;
}
