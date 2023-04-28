#include <imgui_sfml/imgui.h>
#include <imgui_sfml/imgui-SFML.h> 

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "ImGuiWindow.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1080, 720), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGuiWindow imguiWindow(window);
    sf::VertexArray points(sf::Points, 0);
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        imguiWindow.update(deltaClock.restart());
       
        if(imguiWindow.getIsAddPointButtonClicked()){
          
          const sf::Vector2f pos{imguiWindow.getStateX(), imguiWindow.getStateY()};
          const sf::Vertex point{pos,sf::Color::Red};
          points.append(point);

        }

        window.clear();
        window.draw(points);
        imguiWindow.render();
        window.display();
    }
  
    ImGui::SFML::Shutdown();

    return 0;
}
