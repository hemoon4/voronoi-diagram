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
  for(auto x = 0u; x < m_window.getSize().x; x++)
  {
    for(auto y = 0u; y < m_window.getSize().y; y++)
    {
      auto& pixel =  (*m_pixels)[y*m_window.getSize().x + x];
      pixel.position.x = x;
      pixel.position.y = y;
      pixel.color = sf::Color::Black; 
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

void Application::update(sf::Time dt)
{

    m_imguiWindow.update(dt);

    if(m_imguiWindow.getIsAddPointButtonClicked())
    {
      addPoint();
      calculateVoronoiDiagram();
    }

}

void Application::draw()
{

    sf::CircleShape circle{9.f};
    m_window.clear();
    m_window.draw(*m_pixels);
    m_window.draw(*m_points);
    for(std::size_t  pointIndex = 0; pointIndex < m_points->getVertexCount(); pointIndex++)
    {
      circle.setPosition((*m_points)[pointIndex].position);
      m_window.draw(circle);
    }
    m_imguiWindow.render();
    m_window.display();
}
void Application::run()
{

  sf::Clock deltaClock;
  while (m_window.isOpen()) 
  {
    handleEvents();

    update(deltaClock.restart());

    draw();
  }
  m_imguiWindow.end();
}

void Application::calculateVoronoiDiagram()
{
  for(auto pixel_x = 0u; pixel_x < m_window.getSize().x; pixel_x++)
  {
    for(auto pixel_y = 0u; pixel_y < m_window.getSize().y; pixel_y++)
    {
      int point_x = (*m_points)[0].position.x,
          point_y = (*m_points)[0].position.y;
      int min_distance = (pixel_x-point_x) * (pixel_x-point_x) + (pixel_y - point_y) * (pixel_y-point_y);
      int min_point_index = 0;
      for(std::size_t  pointIndex = 1; pointIndex < m_points->getVertexCount(); pointIndex++)
      {
        point_x = (*m_points)[pointIndex].position.x;
        point_y = (*m_points)[pointIndex].position.y;
        int distance = (pixel_x-point_x) * (pixel_x-point_x) + (pixel_y - point_y) * (pixel_y-point_y);
        if (distance < min_distance)
        {
          min_distance = distance;
          min_point_index = pointIndex;
        }
      }
      (*m_pixels)[pixel_y*m_window.getSize().x + pixel_x].color = (*m_points)[min_point_index].color; 
    }
  }
}

void Application::addPoint()
{
  
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(0,230);
  sf::Vector2f pos{m_imguiWindow.getStateX(), m_imguiWindow.getStateY()};
  unsigned char red = distrib(gen);
  unsigned char green = distrib(gen);
  unsigned char blue = distrib(gen);
  sf::Color col{red, green, blue};
  m_points->append(sf::Vertex{pos, col});
      calculateVoronoiDiagram();
}
