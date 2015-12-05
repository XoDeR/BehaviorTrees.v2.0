#pragma once

#include <random>

namespace Bt
{
	class RandomHelper
	{
	public:
		template<typename T>
		static inline T random_real(T min, T max)
		{
			std::uniform_real_distribution<T> dist(min, max);
			auto &mt = RandomHelper::getEngine();
			return dist(mt);
		}

		template<typename T>
		static inline T random_int(T min, T max)
		{
			std::uniform_int_distribution<> dist(min, max);
			auto &mt = RandomHelper::getEngine();
			return dist(mt);
		}
	private:
		static std::mt19937 &getEngine();
	};

	// returns a random value between min and max
	template<typename T>
	inline T random(T min, T max)
	{
		return RandomHelper::random_int(min, max);
	}

	template<>
	inline float random(float min, float max) 
	{
		return RandomHelper::random_real(min, max);
	}

	template<>
	inline long double random(long double min, long double max)
	{
		return RandomHelper::random_real(min, max);
	}

	template<>
	inline double random(double min, double max)
	{
		return RandomHelper::random_real(min, max);
	}
}

// returns a random int between 0 and RAND_MAX
inline int _random()
{
	return Bt::random(0, RAND_MAX);
};

// returns a random float between -1 and 1
inline float rand_minus1_1() 
{
	return Bt::random(-1.f, 1.f);
};

// returns a random float between 0 and 1
inline float rand_0_1() 
{
	return Bt::random(0.f, 1.f);
};
