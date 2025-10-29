using FlappyBird.Components;
using Microsoft.Xna.Framework;
using MonoGame.Extended.Screens;

namespace FlappyBird.Screens;

public class Title(Game game, Background background) : GameScreen(game)
{
    private readonly FlappyBird _game = (FlappyBird)game;

    public override void LoadContent()
    {
        background.LoadContent();
    }

    public override void Update(GameTime gameTime)
    {
    }

    public override void Draw(GameTime gameTime)
    {
        if (_game.SpriteBatch is null) return;
        
        _game.SpriteBatch.Begin();
        background.Draw(gameTime);
        _game.SpriteBatch.End();
    }
}