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
    sf::Vector2f position = {0.0f, 0.0f};  // Removed initialPosition
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

    sf::Vector2f sourcePosition = {0.0f, 0.0f}; // Default position for particles
    bool interpolation = false; // Interpolation is not necessary now
    float particleSize = 20.0f; // Radius of particles
    

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
            p.position = sourcePosition; // Set all particles' positions to sourcePosition initially

            particles.push_back(p);

            sf::CircleShape shape(particleSize);
            shape.setFillColor(p.color);
            shape.setOrigin(particleSize, particleSize); // Center the shape
            shapes.push_back(shape);
        }
    }

    void updateParticles(float dt)
{
    // We'll use two vectors to store the updated particles and shapes
    std::vector<Particle> newParticles;
    std::vector<sf::CircleShape> newShapes;

    for (int i = 0; i < particles.size(); ++i)
    {
        float newTime = fmodf(currTime + dt, particles[i].lifetime);

        // Only update the particle if its lifetime has not exceeded
        if (newTime  < particles[i].lifetime)
        {
            pathFunction(newTime, particles[i]);

            // Update particle visual properties
            shapes[i].setPosition(particles[i].position);

            // Transparent fill color: fading effect based on the remaining lifetime
            sf::Color fillColor = particles[i].color;
            fillColor.a = static_cast<uint8_t>(255 * (1.0f - newTime / particles[i].lifetime)); // Fade out
            shapes[i].setFillColor(fillColor);

            // Outline for bubble effect
            sf::Color outlineColor = sf::Color(255, 255, 255, 200); // Light reflective outline
            shapes[i].setOutlineColor(outlineColor);
            shapes[i].setOutlineThickness(2.0f); // Adjust thickness as needed

            // Keep the particle and shape for the next frame
            newParticles.push_back(particles[i]);
            newShapes.push_back(shapes[i]);
        }
        else
        {
            
        }

    }

    // Update the particles and shapes with the new ones
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

    // Set position of the particle system, particles will then start moving from here
    void setPosition(sf::Vector2f position)
    {
        sourcePosition = position;

        // Update all particles' positions when the system's position is updated
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
            shape.setOrigin(particleSize, particleSize); // Center the shape
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

#endif // PARTICLE_SYSTEM_H
