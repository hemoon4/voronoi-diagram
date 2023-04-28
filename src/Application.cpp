#include "Application.hpp"

#include <SFML/Window/Event.hpp>

Application::Application(unsigned int width, unsigned int height) 
  : m_window(sf::VideoMode(width, height), "Voronoi Diagrams"),    m_imguiWindow(m_window) 
{
  m_window.setFramerateLimit(60);
}

void Application::handleEvents()
{
  sf::Event event;

  while(m_window.pollEvent(event))
  {
    m_imguiWindow.processEvent(event);
    if (event.type == sf::Event::Closed)
    {
      m_window.close();
     }
    }
}

void Application::run()
{
  sf::Clock deltaClock;
  while (m_window.isOpen()) 
  {
    
    handleEvents();

    m_imguiWindow.update(deltaClock.restart());

    m_window.clear();
    m_imguiWindow.render();
    m_window.display();
  }
}
