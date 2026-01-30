
## Boids

Boids is a simple simulation of flocking behavior introduced by Craig Reynolds. Each “boid” is an autonomous agent that follows three local rules:

- **Separation**: avoid crowding nearby boids  
- **Alignment**: steer toward the average heading of neighbors  
- **Cohesion**: move toward the average position of neighbors  

Despite these simple rules, the system produces complex, realistic group motion similar to birds flocking or fish schooling. Boids is commonly used in computer graphics, games, and simulations to demonstrate emergent behavior.

This was written using pygame because I only wanted to worry about the math (I should have used numpy). This was a nice application of the vector calculus I learnt in 237 despite everything else. Maybe in the future I will make the boids look less ugly.
