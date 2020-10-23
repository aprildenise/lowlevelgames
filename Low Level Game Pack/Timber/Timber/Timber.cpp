#include <iostream>
#include <sstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;


void SetSpeed(float& speed, int randMinBound, int randMaxBound);
void SetSpeed(float& speed, int randMinBound, int randMaxBound) {
    srand((int)time(0) * 10);
    speed = (rand() % randMinBound) + randMaxBound; // Speed.
}

void SetSpriteHeight(Sprite& sprite, int randMinBound, int randMaxBound, float xPosition);
void SetSpriteHeight(Sprite& sprite, int randMinBound, int randMaxBound, float xPosition) {
    srand((int)time(0) * 10);
    float height = (rand() % randMinBound) + randMaxBound; // Height
    sprite.setPosition(xPosition, height);
}

void MoveSprite(Sprite& sprite, float& speed, Time& deltaTime, bool isMovingLeft);
void MoveSprite(Sprite& sprite, float& speed,  Time& deltaTime, bool isMovingLeft) {
    float x;
    if (isMovingLeft) x = sprite.getPosition().x - (speed * deltaTime.asSeconds());
    else x = sprite.getPosition().x + (speed * deltaTime.asSeconds());
    float y = sprite.getPosition().y;
    sprite.setPosition(x, y);
}

void UpdateTextCenter(sf::Text& text);
void UpdateTextCenter(sf::Text& text) {
    FloatRect rect = text.getLocalBounds();
    text.setOrigin(
        rect.left + rect.width / 2.0f,
        rect.top + rect.height / 2.0f
    );
}




const int NUMBRANCHES = 6;
Sprite branches[NUMBRANCHES];

enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUMBRANCHES];


/// <summary>
/// Change the position of the branches.
/// </summary>
/// <param name="seed">Seed for the random number generator.</param>
void UpdateBranches(int seed) {

    // Move all the branches down one place.
    for (int j = NUMBRANCHES - 1; j > 0; j--) {
        branchPositions[j] = branchPositions[j - 1];
    }

    // Spawn a new branch at branchPosition[0] and randomly decide what side it will be on
    srand((int)time(0) + seed);
    int r = rand() % 5;
	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
	}
}


int main()
{
    std::cout << "Hello World!\n";

    // Create a video mode object and open a new window for the game.
    auto modes = sf::VideoMode::getFullscreenModes();
    VideoMode vm(modes[0].width, modes[0].height);
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

    // Important variables.
    int const MINBOUNDX = -100;
    int const MAXBOUNDX = modes[0].width;
    int const MINBOUNDY = -100;
    int const MAXBOUNDY = modes[0].height;
    bool isPaused = true;
    int score = 0;
    bool acceptInput = false;

    // Setup the texts.
    sf::Text messageText;
    sf::Text scoreText;
    Font font;
    font.loadFromFile("assets/fonts/KOMIKAP_.ttf");
    messageText.setFont(font);
    scoreText.setFont(font);
    messageText.setString("Press ENTER to start!");
    scoreText.setString("Score: " + score);
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    // Positioning the text
    UpdateTextCenter(messageText);
    messageText.setPosition(MAXBOUNDX / 4, MAXBOUNDY / 4);
    scoreText.setPosition(20, 20);

    // Create the background.
    Texture textureBackground;
    textureBackground.loadFromFile("assets/graphics/background.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    // Place a tree.
    Texture textureTree;
    textureTree.loadFromFile("assets/graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(800, 0);

    // Place some clouds.
    Texture textureCloud;
    textureCloud.loadFromFile("assets/graphics/cloud.png");
    Sprite cloud1, cloud2, cloud3;
    cloud1.setTexture(textureCloud);
    cloud2.setTexture(textureCloud);
    cloud3.setTexture(textureCloud);
    cloud1.setPosition(0, 0);
    cloud2.setPosition(0, 250);
    cloud3.setPosition(0, 500);
    bool isCloudActive[3] = { false };
    float  cloudSpeeds[3] = {0.0f};

    // Prepare the bee.
    Texture textureBee;
    textureBee.loadFromFile("assets/graphics/bee.png");
    Sprite spriteBee; 
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);
    bool isBeeActive = false;
    float beeSpeed = 0.0f;

    // Prepare a clock.
    Clock clock;

    // Time bar.
    RectangleShape timeBarBG;
    RectangleShape timeBar;
    float const timeBarWidth = 400;
    float const timeBarHeight = 80;
    auto timeBarSize = Vector2f(timeBarWidth, timeBarHeight);
    timeBar.setSize(timeBarSize);
    timeBarBG.setSize(timeBarSize);
    timeBar.setFillColor(Color::Green);
    timeBarBG.setFillColor(Color::Black);
    timeBar.setPosition(MAXBOUNDX / 2 - timeBarWidth / 2, 980);
    timeBarBG.setPosition(MAXBOUNDX / 2 - timeBarWidth / 2, 980);

    float const TOTALTIME = 6.0f;
    float timeRemaining = TOTALTIME;
    float barWidthPerSecond = timeBarWidth / timeRemaining;

    // Create the branches.
    Texture textureBranch;
    textureBranch.loadFromFile("assets/graphics/branch.png");
    for (int i = 0; i < NUMBRANCHES; i++) {
        Sprite& branch = branches[i];
        branch.setTexture(textureBranch);
        branch.setPosition(0, 0);
        branch.setOrigin(220, 20); // Center of the branch
    }

    // Create the player.
    Texture texturePlayer;
    texturePlayer.loadFromFile("assets/graphics/player.png");
    Sprite player;
    player.setTexture(texturePlayer);
    player.setPosition(580, 720);
    side playerSide = side::LEFT;
    
    // Create the gravestone.
    Texture textureGrave;
    textureGrave.loadFromFile("assets/graphics/rip.png");
    Sprite grave;
    grave.setTexture(textureGrave);
    grave.setPosition(600, 860);

    // Create the axe.
    Texture textureAxe;
    textureAxe.loadFromFile("assets/graphics/axe.png");
    Sprite axe;
    axe.setTexture(textureAxe);
    axe.setPosition(700, 830);
    const float AXEPOSITIONLEFT = 700;
    const float AXEPOSITIONRIGHT = 1075;

    // Create the log.
    Texture textureLog;
    textureLog.loadFromFile("assets/graphics/log.png");
    Sprite log;
    log.setTexture(textureLog);
    log.setPosition(810, 720);
    bool isLogActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    // Create buffers for sound FXs
    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("assets/sound/chop.wav");
    Sound chop;
    chop.setBuffer(chopBuffer);

    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("assets/sound/death.wav");
    Sound death;
    death.setBuffer(deathBuffer);

    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("assets/sound/out_of_time.wav");
    Sound outOfTime;
    outOfTime.setBuffer(ootBuffer);

    // Main gameloop.
    while (window.isOpen()) {
        
        // Debouce input.
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased && !isPaused) {
                acceptInput = true;

                // Hide the axe.
                axe.setPosition(2000, axe.getPosition().y);
            }
        }

        // Check if the player wants to quit. 
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Return)) {

            // Player is resetting the game.
            isPaused = false;

            // Reset the time and the score.
            score = 0;
            timeRemaining = TOTALTIME;

            // Make all the branches disappear.
            for (int i = 0; i < NUMBRANCHES; i++) {
                branchPositions[i] = side::NONE;
            }

            // Hide the gravestone.
            grave.setPosition(675, 2000);

            // Move the player into position.
            player.setPosition(580, 720);
            acceptInput = true;
        }

        if (acceptInput) {
            // If the player uses the right arrow, move the player right.
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                playerSide = side::RIGHT;
                score++;

                // Update time remaining.
                timeRemaining += (2 / score) + .15;

                // Update the axe and the player.
                axe.setPosition(AXEPOSITIONRIGHT, axe.getPosition().y);
                player.setPosition(1200, 720);

                // Update the branches.
                UpdateBranches(score);

                // Make the log fly!!
                log.setPosition(810, 720);
                logSpeedX = -5000;
                isLogActive = true;

                acceptInput = false;

                chop.play();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left)) {
                playerSide = side::LEFT;
                score++;

                // Update time remaining.
                timeRemaining += (2 / score) + .15;

                // Update the axe and the player.
                axe.setPosition(AXEPOSITIONRIGHT, axe.getPosition().y);
                player.setPosition(580, 720);

                // Update the branches.
                UpdateBranches(score);

                // Make the log fly!!
                log.setPosition(810, 720);
                logSpeedX = 5000;
                isLogActive = true;

                acceptInput = false;

                chop.play();
            }
        }

        if (!isPaused) {
            // Control the update rate.
            Time deltaTime = clock.restart();

            // Update the time bar.
            timeRemaining -= deltaTime.asSeconds();
            timeBar.setSize(Vector2f(barWidthPerSecond * timeRemaining, timeBarHeight));

            // Calculate the movement of the bee.
            if (!isBeeActive) {
                SetSpeed(beeSpeed, 200, 200);
                SetSpriteHeight(spriteBee, 500, 500, MAXBOUNDX);
                isBeeActive = true;
            }
            else {
                MoveSprite(spriteBee, beeSpeed, deltaTime, true);
                if (spriteBee.getPosition().x < MINBOUNDX) isBeeActive = false;
            }

            // Calculate the movements of the clouds.
            if (!isCloudActive[0]) {
                SetSpeed(cloudSpeeds[0], 200, 100);
                SetSpriteHeight(cloud1, 200, 0, -100);
                isCloudActive[0] = true;
            }
            else {
                MoveSprite(cloud1, cloudSpeeds[0], deltaTime, false);
                if (cloud1.getPosition().x > MAXBOUNDX) isCloudActive[0] = false;
            }
            if (!isCloudActive[1]) {
                SetSpeed(cloudSpeeds[1], 250, 100);
                SetSpriteHeight(cloud2, 200, 0, -100);
                isCloudActive[1] = true;
            }
            else {
                MoveSprite(cloud2, cloudSpeeds[1], deltaTime, false);
                if (cloud2.getPosition().x > MAXBOUNDX) isCloudActive[1] = false;
            }
            if (!isCloudActive[2]) {
                SetSpeed(cloudSpeeds[2], 300, 100);
                SetSpriteHeight(cloud3, 200, 100, -100);
                isCloudActive[2] = true;
            }
            else {
                MoveSprite(cloud3, cloudSpeeds[2], deltaTime, false);
                if (cloud3.getPosition().x > MAXBOUNDX) isCloudActive[2] = false;
            }

            // Update the score.
            std::stringstream s;
            s << "Score : " << score;
            scoreText.setString(s.str());

            // Update the branches.
            for (int i = 0; i < NUMBRANCHES; i++) {
                float height = i * 150;
                Sprite& branch = branches[i];
                side& position = branchPositions[i];
                if (position == side::LEFT) {
                    branch.setPosition(610, height);
                    branch.setRotation(180);
                }
                else if (position == side::RIGHT) {
                    branch.setPosition(1330, height);
                    branch.setRotation(0);
                }
                else {
                    // Hide the branch.
                    branch.setPosition(3000, height);
                }
            }

            // Update the log.
            if (isLogActive) {
                float x = log.getPosition().x + logSpeedX * deltaTime.asSeconds();
                float y = log.getPosition().y + logSpeedY * deltaTime.asSeconds();

                log.setPosition(x, y);

                // Make sure the log does not fly out of the scene.
                if (log.getPosition().x < MINBOUNDX || log.getPosition().x > MAXBOUNDX) {
                    isLogActive = false;
                    log.setPosition(810, 720);
                }
            }
        }

        // Clear everything from the last frame.
        window.clear();

        // Draw our scene.
        window.draw(spriteBackground);
        window.draw(cloud1);
        window.draw(cloud2);
        window.draw(cloud3);
        window.draw(spriteTree);
        for (int i = 0; i < NUMBRANCHES; i++) {
            window.draw(branches[i]);
        }
        window.draw(spriteBee);
        window.draw(player);
        window.draw(axe);
        window.draw(log);
        window.draw(grave);
        window.draw(scoreText);
        window.draw(timeBarBG);
        window.draw(timeBar);



        if (isPaused) {
            // Show the prompt.
            window.draw(messageText);
        }

        // Check the time remaining.
        if (timeRemaining <= 0) {
            isPaused = true;
            messageText.setString("Out of time!!");
            UpdateTextCenter(messageText);

            outOfTime.play();
        }

        // Check if the player collides with a branch.
        if (branchPositions[5] == playerSide) {

            // The player has died. Gameover!
            isPaused = true;
            acceptInput = false;

            grave.setPosition(525, 760);
            player.setPosition(2000, 660);
            messageText.setString("SQUISHED!");
            UpdateTextCenter(messageText);

            death.play();
        }

        // Show everything we just drew.
        window.display();
    }


    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
