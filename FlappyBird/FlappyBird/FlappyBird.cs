using Microsoft.Xna.Framework;

namespace FlappyBird;

public class FlappyBird : Game
{
    private readonly GraphicsDeviceManager _graphicsDeviceManager;

    public FlappyBird()
    {
        _graphicsDeviceManager = new GraphicsDeviceManager(this)
        {
            IsFullScreen = false,
            PreferredBackBufferWidth = 640,
            PreferredBackBufferHeight = 360,
            SynchronizeWithVerticalRetrace = true
        };

        Content.RootDirectory = "Content";
    }

    protected override void Initialize()
    {
        base.Initialize();
    }

    protected override void LoadContent()
    {
        base.LoadContent();
    }

    protected override void UnloadContent()
    {
        base.UnloadContent();
    }

    protected override void Update(GameTime gameTime)
    {
        base.Update(gameTime);
    }

    protected override void Draw(GameTime gameTime)
    {
        GraphicsDevice.Clear(Color.CornflowerBlue);
        base.Draw(gameTime);
    }
}