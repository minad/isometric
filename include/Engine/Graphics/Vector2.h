#ifndef _Engine_Graphics_Vector2_h
#define _Engine_Graphics_Vector2_h

namespace Engine {
namespace Graphics {

template<class _T>
class BaseVector2
{
public:

    _T x, y;
    typedef BaseVector2<_T> _VectorType;

    BaseVector2()
        : x(0), y(0) { }

    BaseVector2(_T x, _T y)
        : x(x), y(y) { }

    bool operator==(const _VectorType& v) const
    {
        return (x == v.x && y == v.y);
    }

    bool operator<(const _VectorType& v) const
    {
        return (x < v.x && y < v.y);
    }

    bool operator<=(const _VectorType& v) const
    {
        return (x <= v.x && y <= v.y);
    }
    
    bool operator>(const _VectorType& v) const
    {
        return !(*this <= v);
    }

    bool operator>=(const _VectorType& v) const
    {
        return !(*this < v);
    }

    _VectorType& operator+=(const _VectorType& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    _VectorType& operator-=(const _VectorType& v)
    {
        x -= v.x;
	y -= v.y;
	return *this;
    }

    _VectorType& operator*=(_T s)
    {
        x *= s;
	y *= s;
	return *this;
    }

    _VectorType& operator/=(_T s)
    {
        x /= s;
	y /= s;
	return *this;
    }
    
    _VectorType operator+(const _VectorType& v)
    {
        return _VectorType(x + v.x, y + v.y);
    }
    
    _VectorType operator-(const _VectorType& v)
    {
        return _VectorType(x - v.x, y - v.y);
    }
    
    _VectorType operator*(_T s)
    {
        return _VectorType(x * s, y * s);
    }
    
    _VectorType operator/(_T s)
    {
        return _VectorType(x / s, y / s);
    }
};

typedef BaseVector2<int> Vector2;

} // namespace Graphics
} // namespace Engine

#endif // _Engine_Graphics_Vector2_h

