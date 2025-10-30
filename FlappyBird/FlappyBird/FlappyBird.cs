using FlappyBird.Components;
using FlappyBird.Screens;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using MonoGame.Extended.Screens;
using MonoGame.Extended.ViewportAdapters;

namespace FlappyBird;

public class FlappyBird : Game
{
    private readonly Dictionary<ScreenName, GameScreen> _screens = new();
    
    private readonly ScreenManager _screenManager;
    private ScreenName _currentScreen;
    private readonly Background _background;

    public SpriteBatch? SpriteBatch;
    public ViewportAdapter? ViewportAdapter;

    // This is the working resolution of the game. Game coordinates will be according to this resolution
    public static readonly int VirtualWidth = 640;
    public static readonly int VirtualHeight = 360;
    
    // This is the size of the view port and will be scaled from the virtual (working) resolution
    public static readonly int BackBufferWidth = 1280;
    public static readonly int BackBufferHeight = 720;

    public FlappyBird()
    {
        var graphicsDeviceManager = new GraphicsDeviceManager(this)
        {
            IsFullScreen = false,
            PreferredBackBufferWidth = BackBufferWidth,
            PreferredBackBufferHeight = BackBufferHeight,
            SynchronizeWithVerticalRetrace = true,
        };

        graphicsDeviceManager.ApplyChanges();
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

        ViewportAdapter = new BoxingViewportAdapter(Window, GraphicsDevice, VirtualWidth, VirtualHeight);
        
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