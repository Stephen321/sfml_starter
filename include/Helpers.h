#pragma once
#include <vector>
#include "SFML\Graphics.hpp"

namespace Helpers {
	//clamps a value between min and max-1
	inline int clamp(int value, int min, int max) {
		if (value < 0) {
			return max - 1;
		}
		if (value >= max) {
			return 0;
		}

		return value;
	}

	inline float getLength(const sf::Vector2f & v) {
		float length = sqrt(v.x * v.x + v.y * v.y);
		return length;
	}

	inline sf::Vector2f normaliseCopy(const sf::Vector2f & v) {
		sf::Vector2f n;
		float length = getLength(v);
		if (length != 0) {
			n.x = v.x / length;
			n.y = v.y / length;
		}
		return n;
	}

	inline void normalise(sf::Vector2f & v) {
		v = normaliseCopy(v);
	}
	
	inline float randomNumberF(float min, float max) {
		return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
	}

	inline int randomNumber(int min, int max) {
		return rand() % (max - min + 1) + min;
	}


	inline void limit(sf::Vector2f& v, float max) {
		if (Helpers::getLength(v) > max) {
			v = Helpers::normaliseCopy(v) * max;
		}
	}
	template<typename T, typename Comparer1, typename Comparer2 = Comparer1>
	inline int binarySearch(const std::vector<T>& v, const T& target, Comparer1 equals, Comparer2 lessThanEquals) {
		int low = 0;
		int high = v.size();
		while (low <= high) {
			int mid = low + (high - low) / 2;
			if (mid == low)
				return (mid < low) ? mid : low;
			if (equals(v[mid], target))
				return mid;
			else if (lessThanEquals(v[mid], target)) 
				low = mid + 1;
			else
				high = mid - 1;
		}
		return -1; //not found
	}
}