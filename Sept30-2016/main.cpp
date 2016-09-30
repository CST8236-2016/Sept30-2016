#include <SFML/Graphics.hpp>

int main(int argc, char *argv)
{
  // Create my window with a size of 400x400, and a title bar that features minimize/maximize/close.
  sf::RenderWindow window(sf::VideoMode(600, 400), "Template", sf::Style::Titlebar | sf::Style::Close);

  sf::Event evt;
  sf::Clock appTimer;

  // Load my cloud texture.
  sf::Texture cloudsTexture;
  cloudsTexture.loadFromFile("res/tiling_clouds.jpg");
  cloudsTexture.setRepeated(true);

  sf::Sprite cloudsSprite;
  cloudsSprite.setTexture(cloudsTexture);

  int mouseX = 0, mouseY = 0;
  float offset = 100;
  bool growOffset = false, shrinkOffset = false;

  // Main loop.
  while (window.isOpen()) {
    float deltaTime = appTimer.restart().asSeconds();

    // Handling all incoming system/peripheral events.
    while (window.pollEvent(evt)) {
      switch (evt.type)
      {
      // Track mouse movements.
      case sf::Event::MouseMoved:
        mouseX = evt.mouseMove.x;
        mouseY = evt.mouseMove.y;
        break;

      case sf::Event::KeyPressed:
        // Change the offset size while the '[' key is held.
        if (evt.key.code == sf::Keyboard::Key::LBracket)
        {
          shrinkOffset = true;
        }
        else if (evt.key.code == sf::Keyboard::Key::RBracket)
        {
          growOffset = true;
        }
        break;

      case sf::Event::KeyReleased:
        // Change the offset size while the '[' key is held.
        if (evt.key.code == sf::Keyboard::Key::LBracket)
        {
          shrinkOffset = false;
        }
        else if (evt.key.code == sf::Keyboard::Key::RBracket)
        {
          growOffset = false;
        }
        break;

      case sf::Event::Closed:
        window.close();
        break;
      default:
        break;
      }
    }

    float offsetAdjustmentValue = 5.0f;

    // Change the size of our offset.
    if (shrinkOffset && !growOffset)
    {
      offset -= offsetAdjustmentValue * deltaTime;
      if (offset < offsetAdjustmentValue)
      {
        offset = offsetAdjustmentValue;
      }
    }
    else if (growOffset && !shrinkOffset)
    {
      offset += offsetAdjustmentValue * deltaTime;
    }

    // Reset the size of the texture rectangle.
    sf::IntRect cloudSpriteTextureRectangle = cloudsSprite.getTextureRect();
    cloudSpriteTextureRectangle.left = mouseX;
    cloudSpriteTextureRectangle.top = mouseY;

    cloudSpriteTextureRectangle.width = offset;
    cloudSpriteTextureRectangle.height = offset;
    cloudsSprite.setTextureRect(cloudSpriteTextureRectangle);

    // Overwrite the window's current contents with a background colour.
    window.clear();

    // Where to place the sprite relative to our mouse.
    sf::Transform spritePosition;
    spritePosition.translate(mouseX - (offset / 2), mouseY - (offset / 2));

    // Draw stuff.
    window.draw(cloudsSprite, spritePosition);

    // Push the offscreen buffer into the window's current contents.
    window.display();
  }

  return 0;
}