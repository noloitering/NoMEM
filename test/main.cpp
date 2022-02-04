#include "../src/NoMEM.h"

int main(int argc, char ** argv)
{
	NoMEM::MEMManager assets = NoMEM::MEMManager("../");
	InitWindow(1280, 1080, "Context");
	InitAudioDevice();
	std::shared_ptr< Font > font = assets.addFont("jupiter_crash", "../fonts/jupiter_crash.png");
	std::shared_ptr< Font > font2 = assets.addFont("alagard");
	std::shared_ptr< Texture2D > mainImg = assets.addTexture("mainBack", "../imgs/space2.png");
	std::shared_ptr< Sound > sound = assets.addSound("dontknow", "../audio/sound.mp3");
	std::shared_ptr< Music > song = assets.addMusic("sunshine", "../audio/music.wav");
	NoMEM::FontMap testMap = assets.getAll< Font >();
	if ( testMap.size() != 2 )
	{
		std::cerr << "fonts not adding to map" << std::endl;
		std::cout << assets.conf.cwd() << std::endl;
		std::cout << assets.conf.fontDir << std::endl;
		
		return 1;
	}
	std::cout << assets.has< Texture2D >("mainBack") << std::endl;
	if ( assets.conf.find("jupiter_crash") == assets.conf.customEnd() )
	{
		std::cerr << "custom texture not adding to map";
		
		return 1;
	}
	if ( !assets.conf.has("mainBack") )
	{
		std::cerr << "custom texture not adding to map";
		
		return 1;
	}
	SetSoundVolume(*(sound), 0.1f);
	PlayMusicStream(*(song));
	
	while ( !WindowShouldClose() )
	{
		UpdateMusicStream(*(song));
		if ( IsMouseButtonDown(MOUSE_BUTTON_LEFT) )
		{
			PlaySoundMulti(*(sound));
		}
		else
		{
			StopSoundMulti();
		}
		ClearBackground(RAYWHITE);
		BeginDrawing();
			DrawTexture(*(assets.get< Texture2D >("mainBack")), 0, 0, WHITE);
		EndDrawing();
	}
	std::cout << assets.conf.cwd() << std::endl;
	assets.clear();
	
	return 0;
}