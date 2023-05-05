#include "Application.hpp"

int main() 
{
  const unsigned int WIDTH  = 1080, 
                     HEIGHT = 720;
  Application app{WIDTH, HEIGHT};
  app.run();
  return 0;
}
