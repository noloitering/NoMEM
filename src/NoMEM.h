#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "raylib.h"

namespace NoMEM
{
	struct Sprite
	{
		Texture2D texture;
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
	
	typedef std::tuple< FontMap, TextureMap, AnimMap, SpriteMap > Assets;

	class MEMManager
	{
	private:
		friend class GameEngine;
		Assets assets;
	public:
		MEMManager() {}
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
			get< Anim >(name) = newAnim;
			
			
			return newAnim;
		}
		
		std::shared_ptr< Font > addFont(const std::string& name, const std::string& path)
		{
			if ( FileExists(path.c_str()) )
			{
				std::shared_ptr< Font > newFont = std::make_shared< Font >(LoadFont(path.c_str()));
				get< Font >(name) = newFont;
				
				return newFont;
			}
			else
			{
				std::cerr << "could not load texture: " << path << std::endl;
			}
			
			return nullptr;
		}
		
		std::shared_ptr< Texture2D > addTexture(const std::string& name, const std::string& path)
		{
			if ( FileExists(path.c_str()) )
			{
				std::shared_ptr< Texture2D > newTexture = std::make_shared< Texture2D >(LoadTexture(path.c_str()));
				get< Texture >(name) = newTexture;
				
				return newTexture;
			}
			else
			{
				std::cerr << "could not load texture: " << path << std::endl;
			}
			
			return nullptr;
		}
		
		std::shared_ptr< Sprite > addSprite(const std::string& name, const std::string& path, int frames = 1)
		{
			if ( FileExists(path.c_str()) )
			{
				std::shared_ptr< Sprite > newSprite = std::make_shared< Sprite >((Sprite){LoadTexture(path.c_str()), frames});
				get< Sprite >(name) = newSprite;
				
				return newSprite;
			}
			else
			{
				std::cerr << "could not load texture: " << path << std::endl;
			}
			
			return nullptr;
		}
		
		// TODO: replace shared_ptrs with nullptr??
		void clear()
		{
			FontMap fontMap = std::get< FontMap >(assets);
			TextureMap textureMap = std::get< TextureMap >(assets);
			AnimMap animMap = std::get< AnimMap >(assets);
			SpriteMap spriteMap = std::get< SpriteMap >(assets);
			
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
				UnloadTexture(sprite.second->texture);
			}
		}
	};
}