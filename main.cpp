#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>

class WindowWrapper : public sf::RenderWindow {
	
	bool busy;
	std::map<std::string, sf::Cursor*> cursors;
	std::string active_cursor;

	public:

		bool setActiveCursor( std::string internal_name ) {
			if( this->cursors.find(internal_name) == this->cursors.end()) { // Cursor with that name does not exist
				return false;
			}
			if( this->cursors[internal_name] == nullptr ) { // That cursor is invalid
				return false; // TODO: Cleanup the bad cursor
			}
			this->active_cursor = internal_name;
			this->setMouseCursor( *(this->cursors[active_cursor]) );

			return true;
		}

		bool registerCursor( std::string internal_name, sf::Cursor* n_cursor ) {
			if( this->cursors.find( internal_name ) != this->cursors.end() ) { // Cursor with that name is already registered
				return false;
			}

			this->cursors[internal_name] = n_cursor;

			return true;
		}
		bool registerCursor( std::string internal_name, sf::Cursor::Type sys_name ) {
			if( this->cursors.find( internal_name ) != this->cursors.end() ) { // Cursor with that name is already registered
				return false;
			}

			sf::Cursor* n_cursor = new sf::Cursor();
			n_cursor->loadFromSystem( sys_name );

			this->cursors[internal_name] = n_cursor;

			return true;
		}
		bool registerCursor( std::string internal_name, const sf::Image img, sf::Vector2u hotspot ) {
			if( this->cursors.find( internal_name ) != this->cursors.end() ) { // Cursor with that name is already registered
				return false;
			}

			sf::Cursor* n_cursor = new sf::Cursor();
			n_cursor->loadFromPixels( img.getPixelsPtr(), img.getSize(), hotspot );

			this->cursors[internal_name] = n_cursor;

			return true;
		}
		bool registerCursor( std::string internal_name, const std::string file_path, sf::Vector2u hotspot ) {
			if( this->cursors.find( internal_name ) != this->cursors.end() ) { return false; }

			sf::Image img;
			if(!img.loadFromFile(file_path)) { return false; } // Crashes Here

			return true;

			sf::Cursor* n_cursor = new sf::Cursor();
			n_cursor->loadFromPixels( img.getPixelsPtr(), img.getSize(), hotspot );

			this->cursors[internal_name] = n_cursor;

			return true;
		}

		void handleEvents( sf::Event event ) {
			while(this->pollEvent( event )) {
				if( event.type == sf::Event::Closed && !this->busy ) {
					this->close();
				}
			}
		}

		WindowWrapper( sf::VideoMode size, std::string title ) : sf::RenderWindow( size, title ), busy(false) {
			// Register system cursors:
			this->registerCursor( "sys_arrow", sf::Cursor::Type::Arrow );
			this->registerCursor( "sys_pointer", sf::Cursor::Type::Hand );
			this->registerCursor( "sys_help", sf::Cursor::Type::Help );
			this->registerCursor( "sys_wait", sf::Cursor::Type::Wait );
			this->registerCursor( "sys_deny", sf::Cursor::Type::NotAllowed );
		}
};

int main( int argc, char* argv[] ) {
	WindowWrapper win( sf::VideoMode(800, 600), "Test Window" );
	win.setFramerateLimit(60);

	sf::Sprite spr;
	sf::Texture text;
	text.loadFromFile("../resource/ui/pointer.png"); // Crash Happens here
	spr.setTexture(text);

	win.registerCursor("default", "../resource/ui/pointer.png", sf::Vector2u(3,3) ); // This also causes a crash when it tries to use sf::Image::loadFromFile()

	while( win.isOpen() ) {
		sf::Event event;
		win.handleEvents( event );

		win.clear();
		// Draw

		win.draw( spr );

		win.display();
	}
}