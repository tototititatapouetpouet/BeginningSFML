#include <iostream>
#include <vector>

class ShapeContainer;

class IShape
{
public:
    IShape(ShapeContainer& owner);
    virtual ~IShape();
    virtual void draw() = 0;

protected:
    ShapeContainer& m_owner;
};

class Square : public IShape
{
public:
    Square(ShapeContainer& owner) : IShape(owner) {}
    void draw() override { std::cout << "Square\n"; }
};

class Circle : public IShape
{
public:
    Circle(ShapeContainer& owner) : IShape(owner) {}
    void draw() override { std::cout << "Circle\n"; }
};

class ShapeContainer
{
public:
    friend class IShape;
    ~ShapeContainer()
    {
        /*
        auto shapes = m_shapes;
        for (auto& shape : shapes)
            delete shape;
            */

        for (size_t shapeIdx = m_shapes.size() - 1; shapeIdx > 0; --shapeIdx)
            delete m_shapes[shapeIdx];
    }

protected:
    std::vector<IShape*> m_shapes;
};




IShape::IShape(ShapeContainer& owner) : m_owner(owner)
{
    m_owner.m_shapes.push_back(this);
}

IShape::~IShape()
{
    auto it = std::find(m_owner.m_shapes.begin(), m_owner.m_shapes.end(), this);
    if (it == m_owner.m_shapes.end())
        throw;

    m_owner.m_shapes.erase(it);
}



class CompoundShape : public IShape, public ShapeContainer
{
public:
    CompoundShape(ShapeContainer& owner) : IShape(owner) {}
    void draw() { for (auto& shape : m_shapes) shape->draw(); }
};

int main()
{
    ShapeContainer container;

    auto cercleCarre = new CompoundShape(container);
    new Square(*cercleCarre);
    new Circle(*cercleCarre);

    auto cercleCercleCarre = new CompoundShape(container);
    new Square(*cercleCercleCarre);
    new Circle(*cercleCercleCarre);
    new Circle(*cercleCercleCarre);

    cercleCarre->draw();

    cercleCercleCarre->draw();

    delete cercleCercleCarre;
}
