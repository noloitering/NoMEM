#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

#include "raylib.h"

namespace NoMEM
{
	struct Sprite
	{
		std::shared_ptr< Texture2D > texture;
		int frames;
	};

	struct Anim
	{
		int start;
		int end;
		int speed;
		bool looping;
	};
	
	typedef std::unordered_map< std::string, std::shared_ptr< Font > > FontMap;
	typedef std::unordered_map< std::string, std::shared_ptr< Texture2D > > TextureMap;
	typedef std::unordered_map< std::string, std::shared_ptr< Anim > > AnimMap;
	typedef std::unordered_map< std::string, std::shared_ptr< Sprite > > SpriteMap;
	typedef std::unordered_map< std::string, std::shared_ptr< Sound > > SoundMap;
	typedef std::unordered_map< std::string, std::shared_ptr< Music > > MusicMap;
	typedef std::tuple< FontMap, TextureMap, AnimMap, SpriteMap, SoundMap, MusicMap > Assets;
	
	class Config // keeps track of files
	{
	private:
		friend class MEMManager;
		std::unordered_map< std::string, std::string > custom;
		std::string wd;
	public:
		Config() 
			: wd(std::string(GetWorkingDirectory())) {}
		
		Config(std::string basePath)
		{
			if ( basePath.back() != '/' )
			{
				basePath = basePath + "/";
			}
			if ( basePath.front() == '.' ) // ensure full path
			{
				std::cerr << "full path not given. Using current working directory instead" << std::endl;
				wd = std::string(GetWorkingDirectory()) + "/" + basePath;
			}
			else
			{
				wd = basePath;
			}
			textureDir = "textures/";
			spriteDir = "textures/sprites/";
			fontDir = "fonts/";
			soundDir = "audio/sounds/";
			musicDir = "audio/music/";
		}
		
		Config(std::string texturePath, std::string spritePath, std::string fontPath, std::string soundPath, std::string musicPath)
			: wd(std::string(GetWorkingDirectory()))
		{
			if ( texturePath.back() != '/' )
			{
				texturePath += "/";
			}
			if ( spritePath.back() != '/' )
			{
				spritePath += "/";
			}
			if ( fontPath.back() != '/' )
			{
				fontPath += "/";
			}
			if ( soundPath.back() != '/' )
			{
				soundPath += "/";
			}
			if ( musicPath.back() != '/' )
			{
				musicPath += "/";
			}
			textureDir = texturePath;
			spriteDir = spritePath;
			fontDir = fontPath;
			soundDir = soundPath;
			musicDir = musicPath;
		}
		
		Config(std::string basePath, std::string texturePath, std::string spritePath, std::string fontPath, std::string soundPath, std::string musicPath)
		{
			if ( basePath.back() != '/' )
			{
				basePath = basePath + "/";
			}
			if ( basePath.front() == '.' ) // ensure full path
			{
				std::cerr << "full path not given. Using current working directory instead" << std::endl;
				wd = std::string(GetWorkingDirectory()) + basePath;
			}
			else
			{
				wd = basePath;
			}
			if ( texturePath.back() != '/' )
			{
				texturePath += "/";
			}
			if ( spritePath.back() != '/' )
			{
				spritePath += "/";
			}
			if ( fontPath.back() != '/' )
			{
				fontPath += "/";
			}
			if ( soundPath.back() != '/' )
			{
				soundPath += "/";
			}
			if ( musicPath.back() != '/' )
			{
				musicPath += "/";
			}
			textureDir = texturePath;
			spriteDir = spritePath;
			fontDir = fontPath;
			soundDir = soundPath;
			musicDir = musicPath;
		}
		
		std::string textureDir = "../assets/textures/";
		std::string spriteDir = "../assets/textures/sprites/";
		std::string fontDir = "../assets/fonts/";
		std::string soundDir = "../assets/audio/sounds/";
		std::string musicDir = "../assets/audio/music/";
		
		bool has(const std::string& key)
		{
			auto found = custom.find(key);
			if ( found != custom.end() )
			{
				return true;
			}
			
			return false;
		}
		
		std::string get(const std::string& key)
		{
			
			return custom.at(key);
		}
		
		std::unordered_map< std::string, std::string > get()
		{
			
			return custom;
		}
		
		std::string cwd(const std::string& set="")
		{
			if ( !set.empty() )
			{
				wd = set;
			}
			
			return wd;
		}
		
		
		std::unordered_map< std::string, std::string >::iterator find(const std::string& key)
		{
			
			return custom.find(key);
		}
		
		std::unordered_map< std::string, std::string >::iterator customEnd()
		{
			
			return custom.end();
		}
	};
	
	class MEMManager // handles loading and unloading of assets
	{
	private:
		Assets assets;
	public:
		MEMManager() {}
		MEMManager(const Assets& a)
			: assets(a) {}
		MEMManager(const Assets& a, std::string texturePath, std::string spritePath, std::string fontPath, std::string soundPath, std::string musicPath)
			: assets(a), conf(Config(texturePath, spritePath, fontPath, soundPath, musicPath)) {}
		MEMManager(const Assets& a, const Config& config)
			: assets(a), conf(config) {}
		MEMManager(const Config& config)
			: conf(config) {}
		MEMManager(std::string confPath)
			: conf(Config(confPath)) {}
		MEMManager(std::string texturePath, std::string spritePath, std::string fontPath, std::string soundPath, std::string musicPath)
			: conf(Config(texturePath, spritePath, fontPath, soundPath, musicPath)) {}
		
		Config conf;
		
		Assets getAll()
		{
			
			return assets;
		}
		
		template< class C >
		std::unordered_map< std::string, std::shared_ptr< C > > getAll()
		{
			
			return std::get< std::unordered_map< std::string, std::shared_ptr< C > > >(assets);
		}
		
		template < class C >
		std::shared_ptr< C > get(const std::string& name)
		{
			auto assetMap = std::get< std::unordered_map< std::string, std::shared_ptr< C > > >(assets);
			
			return assetMap[name];
		}
		
		template < class C >
		bool has(const std::string& name)
		{
			auto assetMap = std::get< std::unordered_map< std::string, std::shared_ptr< C > > >(assets);
			auto search = assetMap.find(name);
	
			return (search != assetMap.end());
		}
		
		std::shared_ptr< Anim > addAnimation(const std::string& name, Anim anim) 
		{
			std::shared_ptr< Anim > newAnim = std::make_shared< Anim >(anim);
			AnimMap animMap = getAll< Anim >();
			animMap[name] = newAnim;
			assets = std::make_tuple(getAll< Font >(), getAll< Texture2D >(), animMap, getAll< Sprite >(), getAll< Sound >(), getAll< Music >());
			
			
			return newAnim;
		}
		
		std::shared_ptr< Font > addFont(const std::string& name, const std::string& path)
		{
			if ( FileExists(path.c_str()) )
			{
				std::shared_ptr< Font > newFont = std::make_shared< Font >(LoadFont(path.c_str()));
				FontMap fontMap = getAll< Font >();
				fontMap[name] = newFont;
				assets = std::make_tuple(fontMap, getAll< Texture2D >(), getAll< Anim >(), getAll< Sprite >(), getAll< Sound >(), getAll< Music >());
				conf.custom[name] = path;
				
				return newFont;
			}
			else
			{
				std::cerr << "could not load font: " << path << std::endl;
			}
			
			return nullptr;
		}
		
		std::shared_ptr< Font > addFont(const std::string& name)
		{
			std::string path = conf.cwd() + conf.fontDir + name;
			if ( FileExists(path.c_str()) )
			{
				
			}
			else if ( FileExists(((path + ".ttf").c_str())) )
			{
				path += ".ttf";
			}
			else if ( FileExists(((path + ".fnt").c_str())) )
			{
				path += ".fnt";
			}
			else if ( FileExists(((path + ".png").c_str())) )
			{
				path += ".png";
			}
			else
			{
				std::cerr << "could not load font: " << path << std::endl;
				
				return nullptr;
			}
			std::shared_ptr< Font > newFont = std::make_shared< Font >(LoadFont(path.c_str()));
			FontMap fontMap = getAll< Font >();
			fontMap[name] = newFont;
			assets = std::make_tuple(fontMap, getAll< Texture2D >(), getAll< Anim >(), getAll< Sprite >(), getAll< Sound >(), getAll< Music >());
				
			return newFont;
		}
		
		std::shared_ptr< Texture2D > addTexture(const std::string& name, const std::string& path)
		{
			if ( FileExists(path.c_str()) )
			{
				std::shared_ptr< Texture2D > newTexture = std::make_shared< Texture2D >(LoadTexture(path.c_str()));
				TextureMap textureMap = getAll< Texture2D >();
				textureMap[name] = newTexture;
				assets = std::make_tuple(getAll< Font >(), textureMap, getAll< Anim >(), getAll< Sprite >(), getAll< Sound >(), getAll< Music >());
				conf.custom[name] = path;
				
				return newTexture;
			}
			else
			{
				std::cerr << "could not load texture: " << path << std::endl;
			}
			
			return nullptr;
		}
		
		std::shared_ptr< Texture2D > addTexture(const std::string& name)
		{
			std::string path = conf.cwd() + conf.textureDir + name;
			if ( FileExists(path.c_str()) )
			{
				
			}
			else if ( FileExists(((path + ".png").c_str())) )
			{
				path += ".png";
			}
			else if ( FileExists(((path + ".gif").c_str())) )
			{
				path += ".gif";
			}
			else if ( FileExists(((path + ".hdr").c_str())) )
			{
				path += ".hdr";
			}
			else if ( FileExists(((path + ".dds").c_str())) )
			{
				path += ".dds";
			}
			else
			{
				std::cerr << "could not load texture: " << path << std::endl;
				
				return nullptr;
			}
			std::shared_ptr< Texture2D > newTexture = std::make_shared< Texture2D >(LoadTexture(path.c_str()));
			TextureMap textureMap = getAll< Texture2D >();
			textureMap[name] = newTexture;
			assets = std::make_tuple(getAll< Font >(), textureMap, getAll< Anim >(), getAll< Sprite >(), getAll< Sound >(), getAll< Music >());
				
			return newTexture;
		}
		
		std::shared_ptr< Sprite > addSprite(const std::string& name, const std::string& path, int frames = 1)
		{
			if ( FileExists(path.c_str()) )
			{
				std::shared_ptr< Texture2D > spriteTex = std::make_shared< Texture2D >(LoadTexture(path.c_str()));
				std::shared_ptr< Sprite > newSprite = std::make_shared< Sprite >((Sprite){spriteTex, frames});
				SpriteMap spriteMap = getAll< Sprite >();
				spriteMap[name] = newSprite;
				assets = std::make_tuple(getAll< Font >(), getAll< Texture2D >(), getAll< Anim >(), spriteMap, getAll< Sound >(), getAll< Music >());
				conf.custom[name] = path;
				
				return newSprite;
			}
			else
			{
				std::cerr << "could not load texture: " << path << std::endl;
			}
			
			return nullptr;
		}
		
		std::shared_ptr< Sprite > addSprite(const std::string& name, int frames = 1)
		{
			std::string path = conf.cwd() + conf.spriteDir + name;
			if ( FileExists(path.c_str()) )
			{
				
			}
			else if ( FileExists(((path + ".png").c_str())) )
			{
				path += ".png";
			}
			else if ( FileExists(((path + ".gif").c_str())) )
			{
				path += ".gif";
			}
			else if ( FileExists(((path + ".hdr").c_str())) )
			{
				path += ".hdr";
			}
			else if ( FileExists(((path + ".dds").c_str())) )
			{
				path += ".dds";
			}
			else
			{
				std::cerr << "could not load texture: " << path << std::endl;
				
				return nullptr;
			}
			std::shared_ptr< Texture2D > spriteTex = std::make_shared< Texture2D >(LoadTexture(path.c_str()));
			std::shared_ptr< Sprite > newSprite = std::make_shared< Sprite >((Sprite){spriteTex, frames});
			SpriteMap spriteMap = getAll< Sprite >();
			spriteMap[name] = newSprite;
			assets = std::make_tuple(getAll< Font >(), getAll< Texture2D >(), getAll< Anim >(), spriteMap, getAll< Sound >(), getAll< Music >());
				
			return newSprite;
		}
		
		std::shared_ptr< Sound > addSound(const std::string& name, const std::string& path)
		{
			if ( FileExists(path.c_str()) )
			{
				std::shared_ptr< Sound > newSound = std::make_shared< Sound >(LoadSound(path.c_str()));
				SoundMap soundMap = getAll< Sound >();
				soundMap[name] = newSound;
				assets = std::make_tuple(getAll< Font >(), getAll< Texture2D >(), getAll< Anim >(), getAll< Sprite >(), soundMap, getAll< Music >());
				conf.custom[name] = path;
				
				return newSound;
			}
			else
			{
				std::cerr << "could not load texture: " << path << std::endl;
			}
			
			return nullptr;
		}
		
		std::shared_ptr< Sound > addSound(const std::string& name)
		{
			std::string path = conf.cwd() + conf.soundDir + name;
			// TODO: figure out what files to support
			if ( FileExists(path.c_str()) )
			{
				
			}
			else if ( FileExists(((path + ".wav").c_str())) )
			{
				path += ".wav";
			}
			else if ( FileExists(((path + ".mp3").c_str())) )
			{
				path += ".mp3";
			}
			else if ( FileExists(((path + ".ogg").c_str())) )
			{
				path += ".ogg";
			}
			else
			{
				std::cerr << "could not load sound: " << path << std::endl;
				
				return nullptr;
			}
			std::shared_ptr< Sound > newSound = std::make_shared< Sound >(LoadSound(path.c_str()));
			SoundMap soundMap = getAll< Sound >();
			soundMap[name] = newSound;
			assets = std::make_tuple(getAll< Font >(), getAll< Texture2D >(), getAll< Anim >(), getAll< Sprite >(), soundMap, getAll< Music >());
				
			return newSound;
		}
		
		std::shared_ptr< Music > addMusic(const std::string& name, const std::string& path)
		{
			if ( FileExists(path.c_str()) )
			{
				std::shared_ptr< Music > newMusic = std::make_shared< Music >(LoadMusicStream(path.c_str()));
				MusicMap musicMap = getAll< Music >();
				musicMap[name] = newMusic;
				assets = std::make_tuple(getAll< Font >(), getAll< Texture2D >(), getAll< Anim >(), getAll< Sprite >(), getAll< Sound >(), musicMap);
				conf.custom[name] = path;
				
				return newMusic;
			}
			else
			{
				std::cerr << "could not load music: " << path << std::endl;
			}
			
			return nullptr;
		}
		
		std::shared_ptr< Music > addMusic(const std::string& name)
		{
			std::string path = conf.cwd() + conf.musicDir + name;
			// TODO: figure out what files to support
			if ( FileExists(path.c_str()) )
			{
				
			}
			else if ( FileExists(((path + ".wav").c_str())) )
			{
				path += ".wav";
			}
			else if ( FileExists(((path + ".mp3").c_str())) )
			{
				path += ".mp3";
			}
			else if ( FileExists(((path + ".ogg").c_str())) )
			{
				path += ".ogg";
			}
			else
			{
				std::cerr << "could not load sound: " << path << std::endl;
				
				return nullptr;
			}
			std::shared_ptr< Music > newMusic = std::make_shared< Music >(LoadMusicStream(path.c_str()));
			MusicMap musicMap = getAll< Music >();
			musicMap[name] = newMusic;
			assets = std::make_tuple(getAll< Font >(), getAll< Texture2D >(), getAll< Anim >(), getAll< Sprite >(), getAll< Sound >(), musicMap);
				
			return newMusic;
		}
		
		void clear()
		{
			FontMap& fontMap = std::get< FontMap >(assets);
			TextureMap& textureMap = std::get< TextureMap >(assets);
			AnimMap& animMap = std::get< AnimMap >(assets);
			SpriteMap& spriteMap = std::get< SpriteMap >(assets);
			SoundMap& soundMap = std::get< SoundMap >(assets);
			MusicMap& musicMap = std::get< MusicMap >(assets);
			
			for (auto font : fontMap)
			{
				UnloadFont(*(font.second));
			}
			for (auto texture : textureMap)
			{
				UnloadTexture(*(texture.second));
			}
			for (auto sprite : spriteMap)
			{
				UnloadTexture(*(sprite.second->texture));
			}
			for (auto sound : soundMap)
			{
				UnloadSound(*(sound.second));
			}
			for (auto music : musicMap)
			{
				UnloadMusicStream(*(music.second));
			}
			fontMap.clear();
			textureMap.clear();
			animMap.clear();
			spriteMap.clear();
			musicMap.clear();
		}
	};
}