#include <iostream>
#include <vector>
#include <algorithm>

struct IGameObject;
struct Enemy;

struct Scene
{
    using GameObjectList = std::vector<IGameObject*>;
    GameObjectList allGameObjects;

    Scene();
    Enemy* findTarget();
    void update();
    void removeObject(IGameObject* go);
};
Scene scene;

struct IGameObject
{
    virtual ~IGameObject() = default;
    virtual void update() = 0;
    virtual bool isDead() { return false; }
};

struct Enemy : public IGameObject
{
    void update() override {}
    bool isDead() override { return PV <= 0; }
    
public:
    int PV = 3;
};

struct Turret : public IGameObject
{
    void update() override
    {
        if (target == nullptr)
        {
            target = scene.findTarget();
            if (!target)
                return;
        }

        if (target == nullptr)
            return;

        fire();
        if (target->isDead())
            target = nullptr;
    }

    void fire()
    {
        std::cout << "fire!" << std::endl;
        target->PV--;
    }

    Enemy* target = nullptr;
};

Enemy* Scene::findTarget()
{
    for (auto& go : allGameObjects)
    {
        if (auto* toto = dynamic_cast<Enemy*>(go))
            return toto;
    }
    return nullptr;
}


Scene::Scene()
{
    allGameObjects = { new Turret, new Turret, new Turret, new Enemy, new Enemy, new Enemy, new Enemy, new Enemy };
}

void Scene::removeObject(IGameObject* go)
{
    std::cout << "on vire un mort!" << std::endl;
    auto it = std::find(allGameObjects.begin(), allGameObjects.end(), go);
    if (it == allGameObjects.end())
        throw;

    delete* it;
    allGameObjects.erase(it);
}

void Scene::update()
{
    for (auto& go : allGameObjects)
        go->update();

    auto copyAllGameObjects = allGameObjects;
    for (auto& go : copyAllGameObjects)
    {
        if (go->isDead())
            removeObject(go);
    }
}

int main()
{
    while (true)
    {
        scene.update();
    }
}
