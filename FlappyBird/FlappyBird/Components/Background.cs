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
        for (var i = 0; i < 640; i += 64)
        {
            _game.SpriteBatch?.Draw(skyTexture, new Rectangle(i, 0, 64, 360), Color.White);
        }
    }
}