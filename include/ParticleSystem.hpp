#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>

struct Particle
{
    sf::Vector2f position = {0.0f, 0.0f};  
    float lifetime;
    int seed;
    int seed2;
    sf::Color color = sf::Color::Red;
};

typedef std::function<void(float, Particle&)> VecFunction;

class ParticleSource
{
    const float MAX_TIME = 1e+10;
    float currTime = 0.0f;

    bool stopShowing;
    

    std::vector<Particle> particles;
    std::vector<sf::CircleShape> shapes;

    VecFunction pathFunction;

    sf::Vector2f sourcePosition = {0.0f, 0.0f}; 
    bool interpolation = false; 
    float particleSize = 20.0f; 
    

public:
    ParticleSource(unsigned int numParticles, float avgLifetime, VecFunction _pathFunction)
        : pathFunction{_pathFunction}
    {
        srand(static_cast<unsigned>(time(NULL)));
        for (int i = 0; i < numParticles; ++i)
        {
            Particle p;
            p.seed = rand();
            p.seed2 = rand();
            p.lifetime = avgLifetime /* rand() / RAND_MAX*/;
            p.position = sourcePosition; 

            particles.push_back(p);

            sf::CircleShape shape(particleSize);
            shape.setFillColor(p.color);
            shape.setOrigin(particleSize, particleSize); 
            shapes.push_back(shape);
        }
    }

    void updateParticles(float dt)
{
    
    std::vector<Particle> newParticles;
    std::vector<sf::CircleShape> newShapes;

    for (int i = 0; i < particles.size(); ++i)
    {
        float newTime = fmodf(currTime + dt, particles[i].lifetime);

        
        if (newTime  < particles[i].lifetime)
        {
            pathFunction(newTime, particles[i]);

            
            shapes[i].setPosition(particles[i].position);

            
            sf::Color fillColor = particles[i].color;
            fillColor.a = static_cast<uint8_t>(255 * (1.0f - newTime / particles[i].lifetime)); 
            shapes[i].setFillColor(fillColor);

            
            sf::Color outlineColor = sf::Color(255, 255, 255, 200); 
            shapes[i].setOutlineColor(outlineColor);
            shapes[i].setOutlineThickness(2.0f); 

            
            newParticles.push_back(particles[i]);
            newShapes.push_back(shapes[i]);
        }
        else
        {
            
        }

    }

    
    particles = std::move(newParticles);
    shapes = std::move(newShapes);

    currTime += dt;
    if (currTime > MAX_TIME)
        currTime = 0.0f;
    
}








    void draw(sf::RenderWindow& window)
    {
        for (const auto& shape : shapes)
        {
            window.draw(shape);
        }
    }

    
    void setPosition(sf::Vector2f position)
    {
        sourcePosition = position;

        
        for (auto& particle : particles)
        {
            particle.position = sourcePosition;
        }
    }

    void setParticleSize(float size)
    {
        particleSize = size;
        for (auto& shape : shapes)
        {
            shape.setRadius(particleSize);
            shape.setOrigin(particleSize, particleSize); 
        }
    }

    int getParticleCount() { return particles.size(); }

    Particle const& getParticle(unsigned int index)
    {
        return particles[index];
    }

    void setInterpolation(bool value) { interpolation = value; }
    bool PositionSet = false;

    sf::Vector2f getPosition()
    {
        return (this->sourcePosition);
    }
};

#endif 
