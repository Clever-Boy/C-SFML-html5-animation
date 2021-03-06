#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <chrono>
#include "Ball.h"

const float BOUNCE = -0.7f;

typedef std::chrono::duration<int, std::ratio<1, 1000>> FrameTime;

FrameTime startTime;

FrameTime GetTimer() {
    return (std::chrono::duration_cast<FrameTime>(std::chrono::system_clock::now().time_since_epoch()) -
            startTime); //milliseconds
}

int main() {
    //You can turn off antialiasing if your graphics card doesn't support it
    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Time Based 1", sf::Style::Titlebar | sf::Style::Close, context);
    window.setFramerateLimit(60);

    std::mt19937 mt(time(NULL));
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    Ball ball = Ball(window.getSize().x / 2 * dist(mt), window.getSize().y / 2, 30, sf::Color::Red);
    float vx = 300;
    float vy = -300;

    float left = 0;
    float right = window.getSize().x;
    float top = 0;
    float bottom = window.getSize().y;

    startTime = std::chrono::duration_cast<FrameTime>(std::chrono::system_clock::now().time_since_epoch());

    FrameTime time = GetTimer();
    FrameTime elapsed = GetTimer() - time;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        elapsed = GetTimer() - time;
        time = GetTimer();
        ball.Translate(vx * elapsed.count() / 1000, vy * elapsed.count() / 1000);

        sf::Vector2f ballPos = ball.shape.getPosition();
        if (ballPos.x + ball.shape.getRadius() > right) {
            ball.SetX(right - ball.shape.getRadius());
            vx *= BOUNCE;
        } else if (ballPos.x - ball.shape.getRadius() < left) {
            ball.SetX(left + ball.shape.getRadius());
            vx *= BOUNCE;
        }

        if (ballPos.y + ball.shape.getRadius() > bottom) {
            ball.SetY(bottom - ball.shape.getRadius());
            vy *= BOUNCE;
        } else if (ballPos.y - ball.shape.getRadius() < top) {
            ball.SetY(top + ball.shape.getRadius());
            vy *= BOUNCE;
        }

        window.clear(sf::Color::White);
        window.draw(ball.shape);
        window.display();
    }

    return 0;
}