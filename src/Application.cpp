#include "Application.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <random>

Application::Application(unsigned int width, unsigned int height) 
  : m_window(sf::VideoMode{width, height}, "Voronoi Diagrams"),
    m_imguiWindow(m_window),
    m_pixels(new sf::VertexArray{sf::Points, width*height}),
    m_points(new sf::VertexArray{sf::Points, 0})
{
  m_window.setFramerateLimit(60);
  for(int x = 0; x < m_window.getSize().x; x++)
  {
    for(int y = 0; y < m_window.getSize().y; y++)
    {
      (*m_pixels)[y*m_window.getSize().x + x].position.x = x;
      (*m_pixels)[y*m_window.getSize().x + x].position.y = y;
      (*m_pixels)[y*m_window.getSize().x + x].color = sf::Color::Black; 
    }
  }
}

Application::~Application()
{
  delete m_pixels;
  delete m_points;
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
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(0,230);
  sf::Clock deltaClock;
  sf::CircleShape circle{9.f};
  while (m_window.isOpen()) 
  {
    handleEvents();

    m_imguiWindow.update(deltaClock.restart());

    
    if(m_imguiWindow.getIsAddPointButtonClicked())
    {
      sf::Vector2f pos{m_imguiWindow.getStateX(), m_imguiWindow.getStateY()};
      unsigned char red = distrib(gen);
      unsigned char green = distrib(gen);
      unsigned char blue = distrib(gen);
      sf::Color col{red, green, blue};
      m_points->append(sf::Vertex{pos, col});
      calculateVoronoiDiagram();
    }


    m_window.clear();
    m_window.draw(*m_pixels);
    m_window.draw(*m_points);
    for(int pointIndex = 0; pointIndex < m_points->getVertexCount(); pointIndex++)
    {
      circle.setPosition((*m_points)[pointIndex].position);
      m_window.draw(circle);
    }
    m_imguiWindow.render();
    m_window.display();
  }
  m_imguiWindow.end();
}

void Application::calculateVoronoiDiagram()
{
  for(int x = 0; x < m_window.getSize().x; x++)
  {
    for(int y = 0; y < m_window.getSize().y; y++)
    {
      int min_distance = (x-(*m_points)[0].position.x) * (x-(*m_points)[0].position.x) + (y - (*m_points)[0].position.y) * (y-(*m_points)[0].position.y);
      int min_point_index = 0;
      for(int pointIndex = 1; pointIndex < m_points->getVertexCount(); pointIndex++)
      {
        int distance = (x-(*m_points)[pointIndex].position.x) * (x-(*m_points)[pointIndex].position.x) + (y - (*m_points)[pointIndex].position.y) * (y-(*m_points)[pointIndex].position.y);
        if (distance < min_distance)
        {
          min_distance = distance;
          min_point_index = pointIndex;
        }
      }
      (*m_pixels)[y*m_window.getSize().x + x].color = (*m_points)[min_point_index].color; 
    }
  }
}


