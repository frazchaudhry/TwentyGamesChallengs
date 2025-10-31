using FlappyBird.Components;
using Gum.Forms.Controls;
using Gum.Wireframe;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using MonoGame.Extended.Screens;
using MonoGameGum;

namespace FlappyBird.Screens;

public class Title(Game game, Background background) : GameScreen(game)
{
    private readonly FlappyBird _game = (FlappyBird)game;

    public override void Initialize()
    {
        background.Initialize();
        
        var mainPanel = new StackPanel();
        mainPanel.Visual.AddToRoot();
        mainPanel.Anchor(Anchor.Center);
        mainPanel.Y += 50.0f;
        
        // Creates a button instance
        var button = new Button();
        // Adds the button as a child so that it is drawn and has its events raised
        mainPanel.AddChild(button);
        // Initial button text before being clicked
        button.Text = "Play";
        // Makes the button wider so the text fits
        button.Width = 150.0f;
        // Click event can be handled with a lambda
        button.Click += (_, _) =>
        {
            button.Text = $"Clicked at {DateTime.Now}";
        };
        
    }

    public override void UnloadContent()
    {
        background.Dispose();
    }

    public override void Update(GameTime gameTime)
    {
        _game.GumUi.Update(gameTime);
    }

    public override void Draw(GameTime gameTime)
    {
        if (_game.SpriteBatch is null || _game.ViewportAdapter is null) return;
        
        _game.SpriteBatch.Begin(SpriteSortMode.BackToFront, BlendState.AlphaBlend, SamplerState.LinearWrap, 
            DepthStencilState.None, RasterizerState.CullNone, null, _game.ViewportAdapter.GetScaleMatrix());
        background.Draw(gameTime);
        _game.SpriteBatch.End();
        _game.GumUi.Draw();
    }
}