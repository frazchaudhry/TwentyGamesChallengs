#include "Entity.hpp"

Entity::Entity(std::string id, const LC_Rect pos, const LC_Color color) : id(std::move(id)), transform(pos), velocity{ 0.0f, 0.0f }, color(color) {
}

void Entity::ProcessInput([[maybe_unused]]const SDL_Event *event) {}

void Entity::Update([[maybe_unused]]double deltaTime, [[maybe_unused]]const int32 screenHeight) {}

void Entity::Render(LC_GL_Renderer *renderer) {
    LC_GL_RenderRectangle(renderer, &transform, &color, false);
}

Wall::Wall(std::string id, const LC_Rect pos, const LC_Color color, const bool isVisible) : Entity(std::move(id) ,pos, color), isVisible(isVisible) {

}

void Wall::Render(LC_GL_Renderer *renderer) {
    if (!isVisible) return;

    this->Entity::Render(renderer);
}

Divider::Divider(std::string id, const LC_Rect pos, const LC_Color color) : Entity(std::move(id), pos, color) {
}

void Divider::Render(LC_GL_Renderer *renderer) {
    LC_GL_RenderRectangle(renderer, &transform, &color, true);
}

Paddle::Paddle(std::string id, const LC_Rect pos, const LC_Color color) : Entity(std::move(id), pos, color) {}

void Paddle::ProcessInput(const SDL_Event *event) {
    if (id == "leftPaddle") {
        if (event->key.key == SDLK_W && event->type == SDL_EVENT_KEY_DOWN) {
            state = PADDLE_UP;
        } else if (event->type == SDL_EVENT_KEY_UP && (event->key.key == SDLK_W || event->key.key == SDLK_S)) {
            state = PADDLE_STOP;
        } else if (event->key.key == SDLK_S && event->type == SDL_EVENT_KEY_DOWN) {
            state = PADDLE_DOWN;
        } 
    } else if (id == "rightPaddle") {
        if (event->key.key == SDLK_UP && event->type == SDL_EVENT_KEY_DOWN) {
            state = PADDLE_UP;
        } else if (event->type == SDL_EVENT_KEY_UP && (event->key.key == SDLK_UP || event->key.key == SDLK_DOWN)) {
            state = PADDLE_STOP;
        } else if (event->key.key == SDLK_DOWN && event->type == SDL_EVENT_KEY_DOWN) {
            state = PADDLE_DOWN;
        }
    }
}

void Paddle::Update(const double deltaTime, const int32 screenHeight) {
    if (state == PADDLE_UP && transform.y >= Wall::HEIGHT) {
        transform.y -= static_cast<int32>(static_cast<float>(PADDLE_VELOCITY) * deltaTime);
    } else if (state == PADDLE_DOWN && transform.y <= screenHeight - (PADDLE_HEIGHT + Wall::HEIGHT)) {
        transform.y += static_cast<int32>(static_cast<float>(PADDLE_VELOCITY) * deltaTime);
    }
}

Ball::Ball(std::string id, const LC_Rect pos, const LC_Color color) : Entity(std::move(id), pos, color) {
    velocity[0] = 1.0f;
}

void Ball::Update(const double deltaTime, [[maybe_unused]]const int32 screenHeight) {
    const float speed = currentSpeed * static_cast<float>(deltaTime);
    vec2 currentPos = { static_cast<float>(transform.x), static_cast<float>(transform.y) };
    glm_vec2_muladds(velocity, speed, currentPos);
    transform.x = static_cast<int32>(currentPos[0]);
    transform.y = static_cast<int32>(currentPos[1]);
}
