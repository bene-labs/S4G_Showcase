/*
** EPITECH PROJECT, 2024
** B_OOP_400_BER_4_1_arcade_emile_hanau
** File description:
** Created by benedikt,
*/

#include "../include/game.hpp"

Game::Game(IGraphics *lib)
{
    this->lib = lib;
}

void Game::loadHighScore()
{
    std::ifstream highScoreFile("nibbler_scores");
    std::string fileContent;
    std::string scoreLine;

    if (highScoreFile.fail())
        return;
    fileContent.assign((std::istreambuf_iterator<char>(highScoreFile) ),
        (std::istreambuf_iterator<char>()));
    if (fileContent.find_last_of('\n') != std::string::npos)
        scoreLine = fileContent.substr(fileContent.find_last_of('\n'), std::string::npos);
    else
        scoreLine = fileContent;
    if (scoreLine.empty())
        return;
    scoreLine = scoreLine.substr(scoreLine.find_last_of(' ') + 1, std::string::npos);
    try {
        highScore = std::stoi(scoreLine);
    } catch (std::exception e) {
        highScore = 0;
    }
    oldHighScore = highScore;
}

void Game::loadUserName()
{
    std::ifstream highScoreFile("users");
    std::string fileContent;
    std::string nameLine;

    if (highScoreFile.fail())
        return;
    fileContent.assign((std::istreambuf_iterator<char>(highScoreFile) ),
        (std::istreambuf_iterator<char>()));
    nameLine = fileContent.substr(fileContent.find_last_of('\n') + 1, std::string::npos);
    if (nameLine.empty())
        return;
    userName = nameLine;
}

void Game::start_game()
{
    lib->init_screen(1200, 960);
    isRunning = true;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            snake.sprites[i][j] = lib->createObject(&snakeSpriteData[i][j]);
        }
    }
    std::srand(time(NULL));

    apples = new Apple(lib->createObject(&appleCreationData));
    apples->snakeReference = &snake;
    apples->spawn();
    object_creation_data data = {\
object_type::TEXT, "0000", "lib/nibbler/resources/slkscr.ttf", "white"};
    scoreText = lib->createObject(&data);

    data.text = "score";
    scoreHeadlineText = lib->createObject(&data);
    data.text = "best";
    highScoreHeadlineText = lib->createObject(&data);
    loadHighScore();
    data.text = std::to_string(highScore + 10000).substr(1, std::string::npos);
    highScoreText = lib->createObject(&data);

    loadUserName();
    isRunning = true;
}

std::string Game::game_tick()
{
    std::string check_input = lib->getPressedKey();
    if (!check_input.empty())
        last_key_pressed = check_input;
    std::chrono::steady_clock::time_point this_call_time = std::chrono::steady_clock::now();

    float frame_delay_reduction = 0.0f;
    if (last_key_pressed == "space") {
        frame_delay_reduction = 0.75f;
        last_key_pressed = lib->getPressedKey();
    }
    if (std::chrono::duration_cast<std::chrono::duration<double>>(
this_call_time - last_call_time).count() < min_frame_delay - (min_frame_delay * frame_delay_reduction))
        return (check_input);
    last_call_time = this_call_time;
    snake.updateSegmentDirections();
    if (last_key_pressed == "esc" || snake.isOutOfBounds() || snake.isCollisionWithSelf()) {
        handleGameOver();
        isRunning = false;
        return ("exit");
    }
    lib->clear_screen();
    snake.setDirection(last_key_pressed);
    snake.move();
    apples->updatePossibleSpawns(snake.getAllSegmentPositions());
    if (snake.isCollisionWithObject(apples->getPosition(), true)) {
        for (int i = 0; i < (std::rand() % 3) + 1; i++) {
            snake.increaseSize();
            score++;
        }
        apples->spawn();

        if (min_frame_delay > 0.16)
            min_frame_delay -= 0.02;
        lib->deleteObject(scoreText);
        object_creation_data new_score_data = {\
object_type::TEXT,(std::to_string(score + 10000).substr(1, std::string::npos)), "lib/nibbler/resources/slkscr.ttf", "white"};
        scoreText = lib->createObject(&new_score_data);
        if (score > highScore) {
            highScore = score;
            lib->deleteObject(highScoreText);
            highScoreText = lib->createObject(&new_score_data);
        }
    }
    lib->draw(highScoreHeadlineText, 0, 70, 10, 90);
    lib->draw(highScoreText, 0, 70, 90, 170);
    lib->draw(scoreHeadlineText, 910, 1010, 10, 90);
    lib->draw(scoreText, 930, 1010, 90, 170);
    snake.draw(lib);
    apples->drawAll(lib);
    lib->display_screen();
    return check_input;
}

bool Game::is_running()
{
    return isRunning;
}

void Game::use_graphics_lib(IGraphics *lib)
{
    /*if (this->lib != nullptr)
        delete this->lib;*/
    this->lib = lib;
}

void Game::reload_all_objects()
{
    object_creation_data textData = {\
object_type::TEXT, "Best", "lib/nibbler/resources/slkscr.ttf", "white"};
    highScoreHeadlineText = lib->createObject(&textData);
    textData.text = "Score";
    scoreHeadlineText = lib->createObject(&textData);
    textData.text =  std::to_string(score + 10000).substr(1, std::string::npos);
    scoreText = lib->createObject(&textData);
    textData.text =  std::to_string(highScore + 10000).substr(1, std::string::npos);
    highScoreText = lib->createObject(&textData);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            snake.sprites[i][j] = lib->createObject(&snakeSpriteData[i][j]);
        }
    }

    apples->_regularSprite = lib->createObject(&appleCreationData);
    lib->init_screen(1200, 960);
}

void Game::handleGameOver()
{
    // save highScore
    if (highScore > oldHighScore) {
        std::ofstream scoreFile("nibbler_scores", std::ios::app);
        if (scoreFile.is_open())
            scoreFile << "\n" + userName + " " + std::to_string(score + 10000).substr(1, std::string::npos);
    }
    lib->destroy_screen();
}

extern "C" {
    __attribute__((constructor))
    void init(){
    }

    IGame *create_game(IGraphics *lib) {
        return new Game(lib);
    }

    __attribute__((destructor))
    void destroy() {
    }
}
