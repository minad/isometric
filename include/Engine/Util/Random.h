#ifndef _Engine_Util_Random_h
#define _Engine_Util_Random_h

#include <boost/random/variate_generator.hpp>
#include <boost/random/inversive_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/normal_distribution.hpp>
#include <ctime>

namespace Engine {
namespace Util {
namespace Random {

typedef boost::hellekalek1995 _DefaultEngine;

using boost::variate_generator;
using boost::uniform_int;
using boost::uniform_real;
using boost::normal_distribution;

template<class _T = int>
struct UniformInt : public variate_generator<_DefaultEngine, uniform_int<_T> >
{
    UniformInt(const _T& min, const _T& max)
        : variate_generator<_DefaultEngine, uniform_int<_T> >
	      (_DefaultEngine(std::time(0)), distribution_type(min, max)) { }
};

template<class _T = double>
struct UniformReal : public variate_generator<_DefaultEngine, uniform_real<_T> >
{
    UniformReal(const _T& min, const _T& max)
        : variate_generator<_DefaultEngine, uniform_int<_T> >
	      (_DefaultEngine(std::time(0)), distribution_type(min, max)) { }
};

template<class _T = double>
struct NormalReal : public variate_generator<_DefaultEngine, normal_distribution<_T> >
{
    NormalReal(const _T& mean, const _T& sigma)
        : variate_generator<_DefaultEngine, normal_distribution<_T> >
	      (_DefaultEngine(std::time(0)), distribution_type(mean, sigma)) { }
};

} // namespace Random
} // namespace Util
} // namespace Engine

#endif // _Engine_Util_Random_h
