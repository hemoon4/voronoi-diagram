#ifndef IMGUI_WINDOW
#define IMGUI_WINDOW

#include <SFML/Graphics/RenderWindow.hpp>

class ImGuiWindow
{
public:
  ImGuiWindow(sf::RenderWindow&);
  
  void processEvent(const sf::Event&) const;
  void update(const sf::Time);
  void render();
  float getStateX() const;
  float getStateY() const;
  bool getIsAddPointButtonClicked() const;
private:
    sf::RenderWindow& m_window;
    float m_stateX, m_stateY;
    bool m_isAddPointButtonClicked;
};

#endif
