#ifndef _Engine_Base_h
#define _Engine_Base_h

#include <boost/noncopyable.hpp>
#include <cassert>

namespace Engine {

class Base : boost::noncopyable
{
public:

    Base() : refCount(0) {}
    virtual ~Base() {}

    void incRef() const
    {
        ++refCount;
    }

    void decRef() const
    {
	if (refCount <= 1)
	{
	    delete this;
	    return; 
	}
	--refCount;
    }

    int getRefCount() const
    {
        return refCount;
    }

private:

    mutable int refCount;
};

} // namespace Engine

#endif // _Engine_Base_h
