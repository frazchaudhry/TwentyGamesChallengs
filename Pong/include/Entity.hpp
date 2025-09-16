#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

extern "C" {
#include <libraVideo.h>
}

class Entity {
public:
    std::string id;
    LC_Rect transform;
    vec2 velocity;
    LC_Color color;

    Entity() = default;
    Entity(std::string id, LC_Rect pos, LC_Color color);

    virtual ~Entity() = default;

    virtual void Render(LC_GL_Renderer *renderer);
};

class Wall final : public Entity {
public: 
    bool isVisible;

    Wall() = default;
    Wall(std::string id, LC_Rect pos, LC_Color color, bool isVisible);

    void Render(LC_GL_Renderer *renderer) override;
};

class Divider final : public Entity {
public:
    Divider() = default;
    Divider(std::string id, LC_Rect pos, LC_Color color);
    void Render(LC_GL_Renderer *renderer) override;
};

#endif // ENTITY_HPP

