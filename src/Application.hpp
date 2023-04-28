#ifndef APPLICATION_H
#define APPLICATION_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "ImGuiWindow.hpp"

class Application
{
public:
  Application(unsigned int width, unsigned int height);
  void run();
private:
  void handleEvents();
private:
  sf::RenderWindow m_window;
  ImGuiWindow m_imguiWindow;
};

#endif
