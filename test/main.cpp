#include "../src/NoMEM.h"

int main(int argc, char ** argv)
{
	NoMEM::MEMManager assets = NoMEM::MEMManager();
	InitWindow(1280, 1080, "Context");
	std::shared_ptr< Font > font = assets.addFont("jupiter_crash", "../fonts/jupiter_crash.png");
	std::shared_ptr< Font > font2 = assets.addFont("alagard", "../fonts/alagard.png");
	std::shared_ptr< Texture2D > mainImg = assets.addTexture("mainBack", "../imgs/space2.png");
	NoMEM::FontMap testMap = assets.getAll< Font >();
	if (testMap.size() != 2)
	{
		std::cerr << "fonts not adding to map"
		
		return 1;
	}
	std::cout << assets.has< Texture2D >("mainBack") << std::endl;
	while (!WindowShouldClose())
	{
		ClearBackground(RAYWHITE);
		BeginDrawing();
			DrawTexture(*(assets.get< Texture2D >("mainBack")), 0, 0, WHITE);
		EndDrawing();
	}
	assets.clear();
	
	return 0;
}