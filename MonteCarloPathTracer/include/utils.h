#ifndef __UTILS_H
#define __UTILS_H

#include<cmath>
#include <io.h>
#include <string>
#include <vector>
#include <iostream>
#include <climits>

//这个参数用于控制2个交点之间最小的距离，如果这个距离小于EPS，那么认为这2个点为同一个点。
//并且这个点不再继续往后递归（EPS不能设置得太小，否则，会出现很多暗纹/暗点，
//例如EPS = 1e-7f就会出现这种现象
//原因：这个求交是不正确的，（交点集中在一个很小的区域内）
//但是为什么会变暗(可能原因：)
const float EPS = 1e-5f;//十分重要！！！

const float PI = 3.1415926f;

bool isEqualf(float a, float b);

std::vector<std::string> getListFiles(std::string path, std::string suffix);


#endif