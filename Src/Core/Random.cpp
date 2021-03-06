#include "Random.h"

namespace Bt
{
	std::mt19937& RandomHelper::getEngine()
	{
		static std::random_device seed_gen;
		static std::mt19937 engine(seed_gen());
		return engine;
	}
} // namespace Bt
