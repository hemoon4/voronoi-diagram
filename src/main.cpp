#include <imgui_sfml/imgui.h>
#include <imgui_sfml/imgui-SFML.h> 

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "ImGuiWindow.hpp"

#include "Application.hpp"
int main() 
{
  const unsigned int WIDTH  = 1080, 
                     HEIGHT = 720;
  Application app(WIDTH, HEIGHT);
  app.run();
  return 0;
}
