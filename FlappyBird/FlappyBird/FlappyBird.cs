using FlappyBird.Render;
using FlappyBird.Utilities;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace FlappyBird;

internal class FlappyBird : Game
{
    [STAThread]
    static void Main(string[] _)
    {
        using var flappyBird = new FlappyBird();
        flappyBird.Run();
    }

    private ResolutionIndependentRenderer _renderer;
    private SpriteFont? _font;
    private SpriteBatch? _spriteBatch;
    private readonly FpsCounter _fpsCounter;
    private Texture2D? _background;
    private KeyboardState _keyboardPrev;
    private MouseState _mousePrev;
    private GamePadState _gpPrev;

    private FlappyBird()
    {
        // This gets assigned to something internally, don't worry...
        var gdm = new GraphicsDeviceManager(this);
        
        // All content loaded will be in a "Content" folder
        Content.RootDirectory = "Content";
        
        // Typically you would load a config here...
        gdm.SynchronizeWithVerticalRetrace = true;
        _renderer = new ResolutionIndependentRenderer(ref gdm);
        _renderer.SetVirtualResolution(640, 360);
        _renderer.SetResolution(800, 600, false);
        
        IsFixedTimeStep = false;
        _fpsCounter = new FpsCounter();

    }
    
    protected override void Initialize()
    {
        base.Initialize();
    }

    protected override void LoadContent()
    {
        _spriteBatch = new SpriteBatch(GraphicsDevice);
        _font = Content.Load<SpriteFont>("Hud");
        _background = Content.Load<Texture2D>("grass-field");
        base.LoadContent();
    }

    protected override void UnloadContent()
    {
        base.UnloadContent();
    }

    protected override void Update(GameTime gameTime)
    {
        // Poll Input
        KeyboardState keyboardCur = Keyboard.GetState();
        MouseState mouseCur = Mouse.GetState();
        GamePadState gpCur = GamePad.GetState(PlayerIndex.One);
        
        // Check for presses
        if (keyboardCur.IsKeyDown(Keys.Escape))
        {
            Exit();
        }
        
        // current is now previous!
        _keyboardPrev = keyboardCur;
        _mousePrev = mouseCur;
        _gpPrev = gpCur;
        
        // Run game logic in here. Do NOT render anything here!
        _fpsCounter.Update(gameTime);
        base.Update(gameTime);
    }

    protected override void Draw(GameTime gameTime)
    {
        // Render stuff in here. Do NOT run game logic in here!
        GraphicsDevice.Clear(Color.CornflowerBlue);
        
        // Draw the texture to the corner of the screen
        if (_spriteBatch is null) return;
        _renderer.BeginDraw();
        _spriteBatch.Begin(SpriteSortMode.BackToFront, BlendState.AlphaBlend, SamplerState.LinearWrap, 
            DepthStencilState.None, RasterizerState.CullNone, null, _renderer.GetTransformationMatrix());
        
        _spriteBatch.Draw(_background, Vector2.Zero, new Rectangle(0, 0, 640, 360), Color.White);
        if (_font != null) _fpsCounter.Draw(_spriteBatch, _font, new Vector2(_renderer.GetVirtualResolution().X - 90, 10), Color.White);
        
        _spriteBatch.End();
        base.Draw(gameTime);
    }
}