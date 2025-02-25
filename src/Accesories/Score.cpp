#include "Score.hpp"
#include "configs.hpp"
#include <string>

using namespace std;

Score::Score(us requiredScore, us currentScore) : requiredScore(requiredScore), currentScore(currentScore)
{
    this->scoreTexture.loadFromFile(PROGRESS_BAR_TEXTURE_DIRECTORY + string("score_progress_bar.png"));
    this->scoreSprite.setTexture(scoreTexture);
    this->scoreSprite.setScale(sf::Vector2f(0.3f,0.3f));
    this->scoreTextFont.loadFromFile(FONT_DIRECTORY + string("Xerox Sans Serif Narrow Bold.ttf"));
    this->scoreText.setFont(scoreTextFont);
    this->scoreText.setCharacterSize(30);
    this->scoreText.setOutlineThickness(1.5);
    this->scoreText.setOutlineColor(sf::Color::Blue);
    this->scoreText.setFillColor(sf::Color::White);
}


void Score::setScoreProgressBarPosition(float x, float y)
{
    this->scoreSprite.setPosition(sf::Vector2f(x, y));
    this->scoreText.setPosition(x + 40, y + 13);
}


void Score::increaseScore(us score)
{
    this->currentScore += score;
}


void Score::decreaseScore(us score)
{
    this->currentScore -= score;
}


us Score::getCurrentScore() const
{
    return this->currentScore;
}


us Score::getRequiredScore() const
{
    return this->requiredScore;
}


void Score::render(sf::RenderWindow &window)
{
    string temp = to_string(currentScore) + "/" + to_string(requiredScore);
    this->scoreText.setString(temp);
    window.draw(this->scoreSprite);
    window.draw(this->scoreText);
}
void Score::setRequiredScore(int score)
{
    this->requiredScore = score;   
}

void Score::resetScore()
{
    this->currentScore = 0;
}
