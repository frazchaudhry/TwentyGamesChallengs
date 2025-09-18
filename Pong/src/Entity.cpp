#include "Entity.hpp"

Entity::Entity(std::string id, LC_Rect pos, LC_Color color) : id(id), transform(pos), velocity{ 0.0f, 0.0f }, color(color) {
}

void Entity::ProcessInput([[maybe_unused]]const SDL_Event *event) {}

void Entity::Update([[maybe_unused]]double deltaTime, [[maybe_unused]]const int32 screenHeight) {}

void Entity::Render(LC_GL_Renderer *renderer) {
    LC_GL_RenderRectangle(renderer, &transform, &color, false);
}

Wall::Wall(std::string id, LC_Rect pos, LC_Color color, bool isVisible) : Entity(id ,pos, color), isVisible(isVisible) {

}

void Wall::Render(LC_GL_Renderer *renderer) {
    if (!isVisible) return;

    this->Entity::Render(renderer);
}

Divider::Divider(std::string id, LC_Rect pos, LC_Color color) : Entity(id, pos, color) {
}

void Divider::Render(LC_GL_Renderer *renderer) {
    LC_GL_RenderRectangle(renderer, &transform, &color, true);
}

Paddle::Paddle(std::string id, LC_Rect pos, LC_Color color) : Entity(id, pos, color) {}

void Paddle::ProcessInput(const SDL_Event *event) {
    if (id == "leftPaddle") {
        if (event->key.key == SDLK_W && event->type == SDL_EVENT_KEY_DOWN) {
            state = Paddle::UP;
        } else if ((event->key.key == SDLK_W && event->type == SDL_EVENT_KEY_UP) ||
            (event->key.key == SDLK_S && event->type == SDL_EVENT_KEY_UP)) {
            state = Paddle::STOP;
        } else if (event->key.key == SDLK_S && event->type == SDL_EVENT_KEY_DOWN) {
            state = Paddle::DOWN;
        } 
    } else if (id == "rightPaddle") {
        if (event->key.key == SDLK_UP && event->type == SDL_EVENT_KEY_DOWN) {
            state = Paddle::UP;
        } else if ((event->key.key == SDLK_UP && event->type == SDL_EVENT_KEY_UP) ||
            (event->key.key == SDLK_DOWN && event->type == SDL_EVENT_KEY_UP)) {
            state = Paddle::STOP;
        } else if (event->key.key == SDLK_DOWN && event->type == SDL_EVENT_KEY_DOWN) {
            state = Paddle::DOWN;
        }
    }
}

void Paddle::Update(double deltaTime, const int32 screenHeight) {
    if (state == UP && transform.y >= Wall::HEIGHT) {
        transform.y -= static_cast<int32>(static_cast<float>(PADDLE_VELOCITY) * deltaTime);
    } else if (state == DOWN && transform.y <= screenHeight - (PADDLE_HEIGHT + Wall::HEIGHT)) {
        transform.y += static_cast<int32>(static_cast<float>(PADDLE_VELOCITY) * deltaTime);
    }
}
