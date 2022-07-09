/*
** EPITECH PROJECT, 2024
** B_OOP_400_BER_4_1_arcade_emile_hanau
** File description:
** Created by benedikt,
*/

#include "game.hpp"

Game::Game(IGraphics *lib) : centipede()
{
    this->lib = lib;
}

void Game::loadHighScore()
{
    std::ifstream highScoreFile("centipede_scores");
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
    highScore = std::stoi(scoreLine);
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
            centipede.sprites[i][j] = lib->createObject(&centipedeSpriteData[i][j]);
        }
    }
    std::srand(time(NULL));

    boxes = new Box(lib);
    boxes->centipedeReference = &centipede;
    boxes->spawn(20);
    object_creation_data data = {\
object_type::TEXT, "000000", "lib/centipede/resources/slkscr.ttf", "white"};
    scoreText = lib->createObject(&data);

    data.text = "score";
    scoreHeadlineText = lib->createObject(&data);
    data.text = "best";
    highScoreHeadlineText = lib->createObject(&data);
    loadHighScore();
    data.text = std::to_string(highScore + 1000000).substr(1, std::string::npos);
    highScoreText = lib->createObject(&data);
    data.text = "Level: 001";
    levelText = lib->createObject(&data);
    loadUserName();
    isRunning = true;
    ship = new Ship(lib);
}

std::string Game::game_tick()
{
    std::string check_input = lib->getPressedKey();
    if (!check_input.empty())
        last_key_pressed = check_input;
    std::chrono::steady_clock::time_point this_call_time = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::duration<double>>(
this_call_time - last_call_time).count() < min_frame_delay)
        return (check_input);
    last_call_time = this_call_time;
    if (last_key_pressed == "esc" || centipede.isCollisionWithPlayer(ship->getPosition())) {
        handleGameOver();
        isRunning = false;
        return ("exit");
    }
    spawnEnemies();
    computeProjectileCollisions();
    centipede.move();
    if (centipede.isOutOfBounds() && score >= 100) {
        score -= 100;
        object_creation_data new_score_data = {\
object_type::TEXT,(std::to_string(score + 1000000).substr(1, std::string::npos)), "lib/centipede/resources/slkscr.ttf", "white"};
        scoreText = lib->createObject(&new_score_data);
    }
    ship->moveProjectiles();
    boxes->updatePossibleSpawns(centipede.getAllSegmentPositions());

    lib->clear_screen();
    lib->draw(highScoreHeadlineText, 0, 70, 10, 90);
    lib->draw(highScoreText, 0, 70, 90, 170);
    lib->draw(scoreHeadlineText, 910, 1010, 10, 90);
    lib->draw(scoreText, 930, 1010, 90, 170);
    lib->draw(levelText, 0, 70, Centipedes::ScreenData::HEIGHT - 80, Centipedes::ScreenData::HEIGHT);
    centipede.draw(lib);
    boxes->drawAll();
    ship->draw();
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
object_type::TEXT, "Best", "lib/centipede/resources/slkscr.ttf", "white"};
    highScoreHeadlineText = lib->createObject(&textData);
    textData.text = "Score";
    scoreHeadlineText = lib->createObject(&textData);
    textData.text =  std::to_string(score + 1000000).substr(1, std::string::npos);
    scoreText = lib->createObject(&textData);
    textData.text =  std::to_string(highScore + 1000000).substr(1, std::string::npos);
    highScoreText = lib->createObject(&textData);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            centipede.sprites[i][j] = lib->createObject(&centipedeSpriteData[i][j]);
        }
    }
    boxes->useLib(lib);
    boxes->loadSprites();
    lib->init_screen(1200, 960);

    ship->setLib(lib);
    ship->loadSprites();

    textData.text = ("Level: " + std::to_string(level + 1000).substr(1, std::string::npos));
    levelText = lib->createObject(&textData);
}

void Game::handleGameOver()
{
    // save highScore
    if (highScore > oldHighScore) {
        std::ofstream scoreFile("centipede_scores", std::ios::app);
        if (scoreFile.is_open())
            scoreFile << "\n" + userName + " " + std::to_string(score + 1000000).substr(1, std::string::npos);
    }
    lib->destroy_screen();
}

void Game::computeProjectileCollisions()
{
    std::pair<int, int> collidedProjectilePosition;
    collidedProjectilePosition = boxes->handleProjectileCollision(ship->getProjectilePosition());
    if (collidedProjectilePosition.second != 0)
        ship->deleteProjectileAtPos(collidedProjectilePosition);
    centipede.updateSegmentDirections();
    centipede.setDirection(boxes->getPositions());
    if  (ship->handleInput(last_key_pressed))
        last_key_pressed = "";
    int prevKillCount = centipede.kilCount;
    int prevFullKills = centipede.fullKills;
    collidedProjectilePosition = centipede.handleProjectileColision(ship->getProjectilePosition());
    if (prevKillCount < centipede.kilCount) {
        score += 10;
        if (centipede.fullKills > prevFullKills)
            score += 100;
        object_creation_data new_score_data = {\
object_type::TEXT,(std::to_string(score + 1000000).substr(1, std::string::npos)), "lib/centipede/resources/slkscr.ttf", "white"};
        scoreText = lib->createObject(&new_score_data);
        if (score > highScore) {
            highScore = score;
            lib->deleteObject(highScoreText);
            highScoreText = lib->createObject(&new_score_data);
        }
    } else if (collidedProjectilePosition.second >= 0) {
        score += 1;
        object_creation_data new_score_data = {\
object_type::TEXT,(std::to_string(score + 1000000).substr(1, std::string::npos)), "lib/centipede/resources/slkscr.ttf", "white"};
        scoreText = lib->createObject(&new_score_data);
        if (score > highScore) {
            highScore = score;
            lib->deleteObject(highScoreText);
            highScoreText = lib->createObject(&new_score_data);
        }
        boxes->spawnAtFixedPos(collidedProjectilePosition);
    }
    ship->deleteProjectileAtPos(collidedProjectilePosition);
}

void Game::spawnEnemies()
{
   std::chrono::steady_clock::time_point this_call_time = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::duration<double>>(
        this_call_time - last_spawn_time).count() < enemySpawnDelay)
        return;

    if (_enemiesSpawned >= 20 && _enemiesSpawned % 20 == 0) {
        if (centipede.fullKills == _enemiesSpawned && centipede.allDead()) {
            increaseLevel();
        } else {
            return;
        }
    }
    last_spawn_time = this_call_time;
    centipede.spawn();
    _enemiesSpawned++;
}

void Game::increaseLevel()
{
    level++;
    object_creation_data new_level_data = {\
object_type::TEXT,("Level: " + std::to_string(level + 1000).substr(1, std::string::npos)), "lib/centipede/resources/slkscr.ttf", "white"};
    levelText = lib->createObject(&new_level_data);
    centipede.setSizes(7 + level * 5, 15 + level * 5);
    boxes->removeAllBoxes();
    boxes->spawn(20 + level * 3);
    enemySpawnDelay += 1.0;
    score += 1000;
    object_creation_data new_score_data = {\
object_type::TEXT,(std::to_string(score + 1000000).substr(1, std::string::npos)), "lib/centipede/resources/slkscr.ttf", "white"};
    scoreText = lib->createObject(&new_score_data);
    if (score > highScore) {
        highScore = score;
        lib->deleteObject(highScoreText);
        highScoreText = lib->createObject(&new_score_data);
    }
    ship->deleteAllProjectiles();
    ship->resetPosition();
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
