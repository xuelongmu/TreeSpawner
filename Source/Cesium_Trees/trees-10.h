#pragma once

#include <vector>

struct Tree {
    // Values are in standard Unreal Engine coordinates (centimeters)
    float positionX;
    float positionY;
    float positionZ;
    float height;
    float canopyRadius;
};

std::vector<Tree> trees {
    { 12698.7f, 83500.9f, 90579.2f, 1356.5f, 4073.8f },
    { 30816.7f, 63235.9f, 22103.4f, 9133.9f, 4844.4f },
    { 54688.1f, 18838.2f, 27849.8f, 5473.1f, 488.6f },
    { 96769.5f, 96488.9f, 99646.1f, 9575.2f, 4964.4f },
    { 95716.7f, 98111.0f, 97059.3f, 7258.9f, 788.9f },
    { 29702.9f, 80028.0f, 79810.6f, 4854.8f, 550.2f },
    { 91573.6f, 11246.5f, 42176.1f, 49.8f, 710.3f },
    { 50366.3f, 95949.2f, 87843.1f, 7922.5f, 3199.2f },
    { 84912.9f, 36129.4f, 3571.2f, 7979.7f, 3279.0f },
    { 39873.9f, 67873.5f, 68136.0f, 9340.1f, 1060.4f },
};
