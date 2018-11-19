#ifndef UTILITY_H
#define UTILITY_H
#include <cstdlib>
#include <GLM/glm.hpp>
namespace RandomNum
{
	template<typename T>
	inline T getRandomNumber(const T& lowerBound, const T& upperBound)
	{
		if (lowerBound == upperBound)
		{
			return upperBound;
		}

		//T magicNumber = (rand()) % (int)(upperBound - lowerBound) + (lowerBound + 1);
		T magicNumber = (rand()) % (int)(upperBound - lowerBound + 1) + lowerBound;
		return magicNumber;
	}


	template<typename T>
	inline glm::vec3 getRandomVector(const T& lowerBound, const T& upperBound)
	{
		glm::vec3 magicVector = glm::vec3(getRandomNumber(lowerBound, upperBound), getRandomNumber(lowerBound, upperBound), getRandomNumber(lowerBound, upperBound));

		return magicVector;
	}

}


#endif

