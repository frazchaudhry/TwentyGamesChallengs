#include "Game.hpp"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keycode.h"

bool Game::Init(const int32 width, const int32 height) {
    backingBuffer = malloc(100 * 1024);
    arena = new LC_Arena();
    LC_Arena_Initialize(arena, backingBuffer, 100 * 1024);

    renderer = static_cast<LC_GL_Renderer*>(LC_Arena_Allocate(arena, sizeof(LC_GL_Renderer)));
    this->screenWidth = width;
    this->screenHeight = height;
    LC_GL_InitializeRenderer(arena, renderer, width, height);

    fontFilePath = "assets/fonts/pong-score-extended.ttf";

    if (LC_GL_InitializeVideo(arena, renderer, "Pong", fontFilePath.c_str(), errorLog)) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not initialize Video.%s", errorLog);
        return false;
    }

    // Enabling Vsync
    if (!SDL_GL_SetSwapInterval(1)) {
        SDL_Log("Failed to enable Vsync.");
        return false;
    }

    Setup();

    return true;
}

void Game::Setup() {
    const LC_Color white = LC_Color_Create(255.0f, 255.0f, 255.0f, 1.0f);
    // Setup Walls
    topWall = Wall("top", (LC_FRect){ 0, 0, static_cast<float>(screenWidth), 25 }, white, true);
    bottomWall = Wall("bottom", (LC_FRect){ 0, static_cast<float>(screenHeight) -25, 
        static_cast<float>(screenWidth), 25}, white, true);

    // Setup Divider
    for (int32 i = 0, y = 40; i < NUM_DIVIDERS; i++, y += 30) {
        Divider divider;
        divider.id = "divider-" + std::to_string(i + 1);
        divider.transform = { 400 - 5 / 2.0f, static_cast<float>(y), 5, 20 };
        divider.color = LC_Color_Create(255.0f, 255.0f, 255.0f, 0.3f);

        dividers[i] = divider;
    }

    // Setup Paddles
    leftPaddle = Paddle("leftPaddle", LEFT_PADDLE_STARTING_POS, white);
    rightPaddle = Paddle("rightPaddle", RIGHT_PADDLE_STARTING_POS, white);

    // Setup Ball
    ball = Ball("Ball", BALL_STARTING_POS, white);
}

SDL_AppResult Game::ProcessInput(const SDL_Event *event) {
    SDL_AppResult result = SDL_APP_CONTINUE;
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
    }

    if (renderer && event->type == SDL_EVENT_WINDOW_RESIZED) {
        SDL_GetWindowSize(renderer->window, &screenWidth, &screenHeight);
        LC_GL_FramebufferSizeCallback(screenWidth, screenHeight);
    }

    if (state == GameState::TITLE) {
        result = ProcessTitleInput(event);
    } else if (state == GameState::ACTIVE || state == GameState::START) {
        result = ProcessGameInput(event);
    } else if (state == GameState::PAUSED) {
        result = ProcessPausedInput(event);
    } else if (state == GameState::END) {
        result = ProcessEndInput(event);
    }
    return result;
}

void Game::Update(const double deltaTime) {
    leftPaddle.Update(deltaTime, screenHeight);
    rightPaddle.Update(deltaTime, screenHeight);

    if (state == GameState::ACTIVE) {
        HandleCollisions();
        ball.Update(deltaTime, screenHeight);
        if (static_cast<int32>(ball.transform.x) > screenWidth) {
            player1Score++;
            ResetGame();
        }
        else if (static_cast<int32>(ball.transform.x < 0.0f)) {
            player2Score++;
            ResetGame();
        }
        if (player1Score >= 7 || player2Score >= 7) {
            state = GameState::END;
            winnerText = player1Score >= 7 ? "PLAYER 1 WINS" : "PLAYER 2 WINS";
        }
    }
}

void Game::Render() {
    // Clear background
    LC_GL_ClearBackground(LC_Color_Create(0.0f, 0.0f, 0.0f, 1.0f));

    if (state == GameState::TITLE) {
        // Render Entities
        topWall.Render(renderer);
        bottomWall.Render(renderer);

        leftPaddle.Render(renderer);
        rightPaddle.Render(renderer);
        LC_GL_RenderText(renderer, &title);
        if (titleState == TitleMenuState::Play) {
            playText.color[2] = 0.0f;
        } else {
            exitText.color[2] = 0.0f;
        }
        LC_GL_RenderText(renderer, &playText);
        LC_GL_RenderText(renderer, &exitText);
        playText.color[2] = 255.0f;
        exitText.color[2] = 255.0f;
    } else if (state == GameState::ACTIVE || state == GameState::START) {
        // Render Entities
        topWall.Render(renderer);
        bottomWall.Render(renderer);
        for (auto& divider : dividers) {
            divider.Render(renderer);
        }
        leftPaddle.Render(renderer);
        rightPaddle.Render(renderer);
        ball.Render(renderer);

        // Render Score
        constexpr vec3 player1ScorePos = { 400.0f - 60.0f, 110.0f, 0.0f };
        constexpr vec3 player2ScorePos = { 400.0f + 25.0f, 110.0f, 0.0f };
        RenderScore(player1Score, player1ScorePos);
        RenderScore(player2Score, player2ScorePos);
    } else if (state == GameState::PAUSED) {
        // Render Entities
        topWall.Render(renderer);
        bottomWall.Render(renderer);
        leftPaddle.Render(renderer);
        rightPaddle.Render(renderer);
        ball.Render(renderer);

        // Render Score
        constexpr vec3 player1ScorePos = { 400.0f - 60.0f, 110.0f, 0.0f };
        constexpr vec3 player2ScorePos = { 400.0f + 25.0f, 110.0f, 0.0f };
        RenderScore(player1Score, player1ScorePos);
        RenderScore(player2Score, player2ScorePos);

        menuTitle.string = const_cast<char*>("PAUSED");
        option1.string = const_cast<char*>("RESUME");
        option2.string = const_cast<char*>("TITLE SCREEN");
        LC_GL_RenderText(renderer, &menuTitle);
        if (pausedState == PauseMenuState::Resume) {
            option1.color[2] = 0.0f;
        } else {
            option2.color[2] = 0.0f;
        }
        LC_GL_RenderText(renderer, &option1);
        LC_GL_RenderText(renderer, &option2);
        option1.color[2] = 255.0f;
        option2.color[2] = 255.0f;
    } else if (state == GameState::END) {
        // Render Entities
        topWall.Render(renderer);
        bottomWall.Render(renderer);
        leftPaddle.Render(renderer);
        rightPaddle.Render(renderer);
        menuTitle.string = const_cast<char*>(winnerText.c_str());
        option1.string = const_cast<char*>("TITLE SCREEN");
        option2.string = const_cast<char*>("PLAY AGAIN");
        LC_GL_RenderText(renderer, &menuTitle);
        if (endState == EndMenuState::TitleScreen) {
            option1.color[2] = 0.0f;
        } else {
            option2.color[2] = 0.0f;
        }
        LC_GL_RenderText(renderer, &option1);
        LC_GL_RenderText(renderer, &option2);
        option1.color[2] = 255.0f;
        option2.color[2] = 255.0f;
    }

    // Swap buffers
    if (!LC_GL_SwapBuffer(renderer->window, errorLog)) {
        SDL_Log("%s\n", errorLog);
    }
}

void Game::RenderScore(const int32 score, const vec3 pos) const {
    char scoreString[2];
    snprintf(scoreString, 2, "%d", score);
    LC_GL_Text scoreText = {
        .string = scoreString,
        .position{ pos[0], pos[1], pos[2] },
        .color{ 255.0f, 255.0f, 255.0f, 1.0f },
        .scale = 2.0f,
        .width = 0,
        .height = 0
    };

    LC_GL_RenderText(renderer, &scoreText);
}

void Game::Unload() const {
    LC_GL_FreeResources(renderer);

    LC_Arena_FreeAll(arena);
    delete arena;
    free(backingBuffer);
}

void Game::HandleCollisions() {
    bool isCollided = false;
    if (ball.transform.x > static_cast<float>(screenWidth) / 2) {
        isCollided = LC_FRect_CheckCollisionAABB(&ball.transform, &rightPaddle.transform);
        if (isCollided) {
            CalculateBallDirection(rightPaddle);
            ball.speed += 10;
            if (ball.speed > ball.MAX_BALL_SPEED) ball.speed = ball.MAX_BALL_SPEED;
            ball.transform.x = rightPaddle.transform.x - ball.transform.w;
            glm_vec2_normalize(ball.velocity);
        }
    }
    else {
        isCollided = LC_FRect_CheckCollisionAABB(&ball.transform, &leftPaddle.transform);
        if (isCollided) {
            CalculateBallDirection(leftPaddle);
            ball.speed += 10;
            if (ball.speed > ball.MAX_BALL_SPEED) ball.speed = ball.MAX_BALL_SPEED;
            ball.transform.x = leftPaddle.transform.x + leftPaddle.transform.w + 1;
            glm_vec2_normalize(ball.velocity);
        }
    }
    if (ball.transform.y > static_cast<float>(screenHeight) / 2) {
        isCollided = LC_FRect_CheckCollisionAABB(&ball.transform, &bottomWall.transform);
        if (isCollided) {
            ball.velocity[1] *= -1;
            ball.transform.y = bottomWall.transform.y - ball.transform.h;
            glm_vec2_normalize(ball.velocity);
        }
    }
    else {
        isCollided = LC_FRect_CheckCollisionAABB(&ball.transform, &topWall.transform);
        if (isCollided) {
            ball.velocity[1] *= -1;
            ball.transform.y = topWall.transform.h;
            glm_vec2_normalize(ball.velocity);
        }
    }
}

void Game::CalculateBallDirection(const Paddle& paddle) {
    const float centerPaddle = paddle.transform.y + paddle.transform.h / 2.0f;
    const float distance = (ball.transform.y + ball.transform.h / 2.0f) - centerPaddle;
    const float percentage = distance / (paddle.transform.h / 2.0f);
    constexpr float strength = 1.0f;
    ball.velocity[1] = percentage * strength;
    ball.velocity[0] *= -1;
}

void Game::ResetGame() {
    leftPaddle.transform = LEFT_PADDLE_STARTING_POS;
    rightPaddle.transform = RIGHT_PADDLE_STARTING_POS;
    ball.transform = BALL_STARTING_POS;
    state = GameState::START;
    winnerText = "";
    ball.speed = ball.INITIAL_BALL_SPEED;
}

SDL_AppResult Game::ProcessTitleInput(const SDL_Event *event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_UP:
                titleState = titleState == TitleMenuState::Play ? TitleMenuState::Exit : TitleMenuState::Play;
                break;
            case SDLK_DOWN:
                titleState = titleState == TitleMenuState::Play ? TitleMenuState::Exit : TitleMenuState::Play;
                break;
            case SDLK_RETURN:
                if (titleState == TitleMenuState::Exit) return SDL_APP_SUCCESS;
                else if (titleState == TitleMenuState::Play) state = GameState::START;
                break;
            default:
                break;
        }
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult Game::ProcessGameInput(const SDL_Event *event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_SPACE:
                state = GameState::ACTIVE;
                break;
            case SDLK_RETURN:
                ResetGame();
                break;
            case SDLK_ESCAPE:
                state = GameState::PAUSED;
            default:
                break;
        }
    }

    leftPaddle.ProcessInput(event);
    rightPaddle.ProcessInput(event);
    return SDL_APP_CONTINUE;
}

SDL_AppResult Game::ProcessPausedInput(const SDL_Event *event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_UP:
                pausedState = pausedState == PauseMenuState::Resume ? PauseMenuState::TitleScreen : PauseMenuState::Resume;
                break;
            case SDLK_DOWN:
                pausedState = pausedState == PauseMenuState::Resume ? PauseMenuState::TitleScreen : PauseMenuState::Resume;
                break;
            case SDLK_RETURN:
                if (pausedState == PauseMenuState::Resume) {
                    state = GameState::ACTIVE;
                }
                else if (pausedState == PauseMenuState::TitleScreen) {
                    ResetGame();
                    state = GameState::TITLE;
                }
                break;
            default:
                break;
        }
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult Game::ProcessEndInput(const SDL_Event *event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_UP:
                endState = endState == EndMenuState::TitleScreen ? EndMenuState::PlayAgain : EndMenuState::TitleScreen;
                break;
            case SDLK_DOWN:
                endState = endState == EndMenuState::TitleScreen ? EndMenuState::PlayAgain : EndMenuState::TitleScreen;
                break;
            case SDLK_RETURN:
                if (endState == EndMenuState::TitleScreen) {
                    state = GameState::TITLE;
                    player1Score = 0;
                    player2Score = 0;
                    ball.speed = ball.INITIAL_BALL_SPEED;
                }
                else if (endState == EndMenuState::PlayAgain) {
                    state = GameState::START;
                    player1Score = 0;
                    player2Score = 0;
                    ResetGame();
                }
                break;
            default:
                break;
        }
    }
    return SDL_APP_CONTINUE;
}
