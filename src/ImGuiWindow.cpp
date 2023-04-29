#include "ImGuiWindow.hpp"

#include <imgui_sfml/imgui.h>
#include <imgui_sfml/imgui-SFML.h>
#include <SFML/Graphics/RenderWindow.hpp>

ImGuiWindow::ImGuiWindow(sf::RenderWindow& window) 
  : m_window(window), 
    m_stateX(0.f), 
    m_stateY(0.f),
    m_isAddPointButtonClicked(false)
{
  ImGui::SFML::Init(m_window);
} 

void ImGuiWindow::processEvent(const sf::Event& e) const
{
  ImGui::SFML::ProcessEvent(e);
}

void ImGuiWindow::update(sf::Time dt)
{
  ImGui::SFML::Update(m_window, dt);

  ImGui::ShowDemoWindow();
  
  ImGui::Begin("ImGui");
  ImGui::InputFloat("X", &m_stateX);
  ImGui::InputFloat("Y", &m_stateY);

  if(ImGui::Button("Add point"))
  {

    m_isAddPointButtonClicked = true;
  }

  ImGui::End();
}

void ImGuiWindow::render() 
{
  m_isAddPointButtonClicked &= 0;
  ImGui::SFML::Render(m_window);
}

void ImGuiWindow::end(){
  ImGui::SFML::Shutdown();
}
bool ImGuiWindow::getIsAddPointButtonClicked() const
{
  return m_isAddPointButtonClicked;
}

float ImGuiWindow::getStateX() const 
{
  return m_stateX;
}

float ImGuiWindow::getStateY() const 
{
  return m_stateY;
}
