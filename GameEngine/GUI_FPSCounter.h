#pragma once

#ifndef ENGINE_GUI_FPS_COUNTER_H
#define ENGINE_GUI_FPS_COUNTER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace Engine_GUI {

	class FPSCounter {

	private:
		std::string m_font_file = "..\\Ressources\\Fonts\\arial.ttf";

		sf::Font m_font;
		
		sf::Text m_text;

	public:
		FPSCounter();

		void SetFPS(float fps);

		void SetFont(std::string font_path);

		void Draw(sf::RenderWindow * w);


		/*sf::Font font;
		if (!font.loadFromFile("arial.ttf"))
		{
			// erreur...
		}

		sf::Text text;

		// choix de la police � utiliser
		text.setFont(font); // font est un sf::Font

							// choix de la cha�ne de caract�res � afficher
		text.setString("Hello world");

		// choix de la taille des caract�res
		text.setCharacterSize(24); // exprim�e en pixels, pas en points !

								   // choix de la couleur du texte
		text.setColor(sf::Color::Red);

		// choix du style du texte
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);

		...

			// puis, dans la boucle de dessin, entre window.clear() et window.display()
			window.draw(text);*/

	};

}

#endif