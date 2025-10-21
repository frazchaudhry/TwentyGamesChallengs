using System.Runtime.CompilerServices;
using FlappyBird.Render;
using FlappyBird.Utilities;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Nez;
using Nez.Sprites;
using Nez.Textures;

namespace FlappyBird;

internal class FlappyBird : Core
{
    private Scene.SceneResolutionPolicy _sceneResolutionPolicy;
    [STAThread]
    static void Main(string[] _)
    {
        using var flappyBird = new FlappyBird();
        flappyBird.Run();
    }

    private FlappyBird() : base()
    {
        _sceneResolutionPolicy = Scene.SceneResolutionPolicy.BestFit;
        Scene.SetDefaultDesignResolution(640, 360, _sceneResolutionPolicy);
        Window.AllowUserResizing = false;
    }
    
    protected override void Initialize()
    {
        base.Initialize();

        var scene = new Scene
        {
            ClearColor = Color.CornflowerBlue,
            LetterboxColor = Color.Black
        };

        var background = scene.Content.Load<Texture2D>("grass-field");
        var bgEntity = scene.CreateEntity("background");
        var bgSprite = new Sprite(background)
        {
            Origin = Vector2.Zero
        };
        var spriteRenderer = new SpriteRenderer(bgSprite);
        bgEntity.AddComponent(spriteRenderer);
        bgEntity.Transform.SetScale(new Vector2(640 / (float)background.Width,
            360 / (float)background.Height));

        var textEntity = scene.CreateEntity("text");
        textEntity.Transform.Scale = new Vector2(3.0f, 3.0f);
        textEntity.AddComponent(new TextComponent(Graphics.Instance.BitmapFont, _sceneResolutionPolicy.ToString(),
            Vector2.Zero, Color.Black));
        
        Scene = scene;
    }
}