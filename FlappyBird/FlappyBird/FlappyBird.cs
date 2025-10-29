using FlappyBird.Components;
using FlappyBird.Screens;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using MonoGame.Extended.Screens;

namespace FlappyBird;

public class FlappyBird : Game
{
    private readonly GraphicsDeviceManager _graphicsDeviceManager;
    private readonly Dictionary<ScreenName, GameScreen> _screens = new();
    
    private readonly ScreenManager _screenManager;
    private ScreenName _currentScreen;

    public SpriteBatch? SpriteBatch;
    public readonly Background _background;

    public FlappyBird()
    {
        _graphicsDeviceManager = new GraphicsDeviceManager(this)
        {
            IsFullScreen = false,
            PreferredBackBufferWidth = 640,
            PreferredBackBufferHeight = 360,
            SynchronizeWithVerticalRetrace = true,
        };

        _graphicsDeviceManager.ApplyChanges();
        Content.RootDirectory = "Content";
        Window.AllowUserResizing = true;

        _screenManager = new ScreenManager();
        Components.Add(_screenManager);
        _background = new Background(this);
    }

    protected override void Initialize()
    {
        // Initialize Screens
        _screens.Add(ScreenName.Title, new Title(this, _background));
        
        base.Initialize();
    }

    protected override void LoadContent()
    {
        SpriteBatch = new SpriteBatch(GraphicsDevice);
        
        LoadScreen(ScreenName.Title);
        base.LoadContent();
    }

    private void LoadScreen(ScreenName screen)
    {
        _screenManager.LoadScreen(_screens[screen]);
        _currentScreen = screen;
    }

    protected override void UnloadContent()
    {
        SpriteBatch?.Dispose();
        base.UnloadContent();
    }

    protected override void Update(GameTime gameTime)
    {
        base.Update(gameTime);
    }

    protected override void Draw(GameTime gameTime)
    {
        GraphicsDevice.Clear(Color.Black);
        base.Draw(gameTime);
    }
}