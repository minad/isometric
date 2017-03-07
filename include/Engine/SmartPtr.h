#ifndef _Engine_SmartPtr_h
#define _Engine_SmartPtr_h

#include <cassert>

namespace Engine {

template<class _T>
class SmartPtr
{
public:

    typedef _T           _ObjType;
    typedef SmartPtr<_T> _SmartPtrType;
  
    SmartPtr()
        : obj(0) {}
    
    explicit SmartPtr(_ObjType* obj)
        : obj(obj)
    {
        if (obj)
	    obj->incRef();
    }
    
    explicit SmartPtr(const _SmartPtrType& ptr)
        : obj(ptr.obj)
    {
        if (obj)
            obj->incRef();
    }
    
    ~SmartPtr()
    {
        if (obj)
	    obj->decRef();
    }
    
    _SmartPtrType& operator=(const _SmartPtrType& ptr)
    {
	return *this = ptr.obj;
    }

    _SmartPtrType& operator=(_ObjType* o)
    {
        if (obj) obj->decRef();
        obj = o;
        if (obj) obj->incRef(); 
        return *this;
    }

    _ObjType* operator*() const
    {
        assert(obj);
        return obj;
    }

    _ObjType* operator->() const
    {
        assert(obj);
        return obj;
    }

    bool operator==(const _SmartPtrType& ptr) const
    {
        return (obj == ptr.obj);
    }

    operator _ObjType*() const
    {
        return obj;
    }

    operator bool() const
    {
        return (obj != 0);
    }

private:

    _ObjType* obj;
};

} // namespace Engine

#endif // _Engine_SmartPtr_h

