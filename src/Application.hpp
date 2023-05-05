#ifndef APPLICATION_H
#define APPLICATION_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "ImGuiWindow.hpp"

class Application
{
public:
  Application(unsigned int width, unsigned int height);
  void run();
  ~Application();
private:
  void handleEvents();
  void update(sf::Time dt);
  void draw();
  void calculateVoronoiDiagram();
  void addPoint();
private:
  sf::RenderWindow m_window;
  ImGuiWindow m_imguiWindow;
  sf::VertexArray* m_pixels, 
                 * m_points;
};

#endif
