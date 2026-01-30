
## Boids

Boids is a simple simulation of flocking behavior introduced by Craig Reynolds. Each “boid” is an autonomous agent that follows three local rules:

- **Separation**: avoid crowding nearby boids  
- **Alignment**: steer toward the average heading of neighbors  
- **Cohesion**: move toward the average position of neighbors  

Despite these simple rules, the system produces complex, realistic group motion similar to birds flocking or fish schooling. Boids is commonly used in computer graphics, games, and simulations to demonstrate emergent behavior.

This was written using pygame in python, and uses some messy vector calculus I learnt in MAT237. Most of the parameters are easily adjustable in the boid class or in the main function.
