#include "Entity.hpp"

Entity::Entity(std::string id, LC_Rect pos, LC_Color color) : id(id), transform(pos), velocity{ 0.0f, 0.0f }, color(color) {
}

void Entity::Render(LC_GL_Renderer *renderer) {
    LC_GL_RenderRectangle(renderer, &transform, &color, false);
}

Wall::Wall(std::string id, LC_Rect pos, LC_Color color, bool isVisible) : Entity(id ,pos, color), isVisible(isVisible) {

}

void Wall::Render(LC_GL_Renderer *renderer)  {
    if (!isVisible) return;

    this->Entity::Render(renderer);
}

Divider::Divider(std::string id, LC_Rect pos, LC_Color color) : Entity(id, pos, color) {
}

void Divider::Render(LC_GL_Renderer *renderer) {
    LC_GL_RenderRectangle(renderer, &transform, &color, true);
}
