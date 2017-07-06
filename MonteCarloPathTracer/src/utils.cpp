#include "utils.h"
using namespace std;


bool isEqualf(float a, float b)
{
	if (fabs(a - b) < EPS)
	{
		return true;
	}
	return false;

}
