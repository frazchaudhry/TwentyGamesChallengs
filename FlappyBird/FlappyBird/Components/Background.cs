using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using MonoGame.Extended;

namespace FlappyBird.Components;

public class Background(Game game)
{
    private readonly FlappyBird _game = (FlappyBird)game;
    private Texture2D? skyTexture;

    public void LoadContent()
    {
        skyTexture = game.Content.Load<Texture2D>("sky");
    }

    public void UnloadContent()
    {
        skyTexture?.Dispose();
    }

    public void Update(GameTime gameTime)
    {
    }

    public void Draw(GameTime gameTime)
    {
        _game.SpriteBatch?.Draw(skyTexture, Vector2.Zero, Color.White);
    }
}