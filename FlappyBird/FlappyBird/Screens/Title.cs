using FlappyBird.Components;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using MonoGame.Extended.Screens;

namespace FlappyBird.Screens;

public class Title(Game game, Background background) : GameScreen(game)
{
    private readonly FlappyBird _game = (FlappyBird)game;

    public override void Initialize()
    {
        background.Initialize();
    }

    public override void UnloadContent()
    {
        background.Dispose();
    }

    public override void Update(GameTime gameTime)
    {
    }

    public override void Draw(GameTime gameTime)
    {
        if (_game.SpriteBatch is null) return;
        if (_game.ViewportAdapter is null) return;
        
        _game.SpriteBatch.Begin(SpriteSortMode.BackToFront, BlendState.AlphaBlend, SamplerState.LinearWrap, 
            DepthStencilState.None, RasterizerState.CullNone, null, _game.ViewportAdapter.GetScaleMatrix());
        background.Draw(gameTime);
        _game.SpriteBatch.End();
    }
}