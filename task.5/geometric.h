#pragma once
#define PI 3.1415926535
class Geometric{
public:
    virtual float area()=0;
    virtual float volume()=0;
    virtual ~Geometric(){}
};

class Cube:public Geometric{
private:
    float m_side;
public:
    virtual float area()
    {
        return 6*m_side*m_side;
    }

    virtual float volume()
    {
        return m_side*m_side*m_side;
    }

    Cube(float side)
    {
        m_side=side;
    }
};

class Sphere:public Geometric{
private:
    float m_r;
public:
    virtual float area()
    {
        return 4*PI*m_r*m_r;
    }

    virtual float volume()
    {
        return (4/3)*PI*m_r*m_r*m_r;
    }

    Sphere(float r)
    {
        m_r=r;
    }
};
