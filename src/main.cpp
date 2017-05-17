#include <SFML/Audio.hpp>

#include "headers/engine.h"

using namespace sf;

std::vector<DrawableObj*> toBeDrawn;
std::vector<ModeledObj*> toBeUpd;
std::vector<ModeledObj*> playerSide;
std::vector<ModeledObj*> oppoSide;

int main() {

	// Create the main world (random resolution for now)
	RenderWindow window(VideoMode(800, 600), "Duel Screen", Style::Fullscreen);
	window.setFramerateLimit(60);

	// create a view centered in 0,0, res 800*600
	View view(FloatRect(0, 0, 800, 600));

	// activate it
	window.setView(view);

	//landscape
	//char lanscapePath[] = "./img/ground.jpg";
	//make concrete type!
	//DrawableObj landscape(lanscapePath);
	//toBeDrawn.push_back(&landscape);

	// Load a music to play
	Music music;
	if (!music.openFromFile("./sng/song.ogg"))
		return EXIT_FAILURE;
	music.setLoop(true);

	// big mario
	char marioPath[] = "./img/Mario_Nintendo.png";
	ControlSet marioControls;
	marioControls.goRight = Keyboard::D;
	marioControls.goLeft = Keyboard::A;
	marioControls.goUp = Keyboard::W;
	marioControls.goDown = Keyboard::S;
	marioControls.teleport = Keyboard::Space;

	Player mario(marioPath, marioControls);
	toBeDrawn.push_back(&mario);
	toBeUpd.push_back(&mario);
	playerSide.push_back(&mario);

	// a bad guy to test collisions
	Persona badguy(marioPath, 500, 200);
	toBeDrawn.push_back(&badguy);
	toBeUpd.push_back(&badguy);
	oppoSide.push_back(&badguy);

	// Start the game loop
	while (window.isOpen()) {

		 // Process events
		Event event;
		while (window.pollEvent(event)) {

			mario.handleControls(event);

			// LEFT CLICK: Play the music
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) 
					music.play();
				if (event.mouseButton.button == Mouse::Right) 
					music.pause();
			}

			// ESC BUTTON: exit
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape)
					window.close();

			// ARROWS: adjust view
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					view.move(0, -2);
					window.setView(view);
				}
				if (Keyboard::isKeyPressed(Keyboard::Down)) {
					view.move(0, 2);
					window.setView(view);
				}
				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					view.move(-2, 0);
					window.setView(view);
				}
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					view.move(2, 0);
					window.setView(view);
				}
			}
		}

		window.clear();

		garbageCollection(toBeDrawn, toBeUpd, playerSide, oppoSide);

		//update and draw
		for (int i=0; i<toBeUpd.size(); i++)
			toBeUpd[i]->update();
		for (int i=0; i<toBeDrawn.size(); i++)
			toBeDrawn[i]->draw(window);

		detectCollisions(playerSide, oppoSide);

		window.display();
	}

	return EXIT_SUCCESS;
}

/*
class Mario {
public:
   void Jump();
   void Draw(RenderWindow &Window);
   void Update();
private:
   sf::Sprite Sprite;
   bool IsJumping;
};

void Mario::Jump() {
   IsJumping = true;
}

void Mario::Update() {
   if(IsJumping) {
      same jumping logic as above
   }
   
   some more updating logic
}
*/

/*
int main()
{
    vector<string> list;
    list.push_back("foo");
    list.push_back("bar");
    for( vector<string>::const_iterator it = list.begin(); it != list.end(); ++it )
        cout << *it << endl;

    return 0;
}
*/