import pygame
import random
from typing import List

pygame.init()
screen_width = 1000
screen_height = 1000
screen = pygame.display.set_mode((screen_width, screen_height))
clock = pygame.time.Clock()
running = True

middle_screen = pygame.Vector2(screen.get_width() / 2, screen.get_height() / 2)


class boid:
    def __init__(self, spawn_x, spawn_y) -> None:
        # positional info
        self.x = spawn_x
        self.y = spawn_y

        # pygame rect to display
        self.rect = pygame.Rect(self.x, self.y, 10, 10)

        # movement info
        self.v = 1
        self.d = [10, 10]  # initial direction, gets changed later

        self.vt = 1
        self.dt = 2

        self.nearby = []

        # boid sight distance
        self.sight = 50

        # boids attributes
        self.alignment = 1
        self.cohesion = 1
        self.seperation = 20

    def fla(self) -> None:
        """
        move dt mag in d direction
        """
        alignment = self.align()
        cohesey = self.cohese()
        sep = self.separate()

        total_x = (
            cohesey[0] * self.cohesion
            + alignment[0] * self.alignment
            + sep[0] * self.seperation
        )
        total_y = (
            cohesey[1] * self.cohesion
            + alignment[1] * self.alignment
            + sep[1] * self.seperation
        )
        mag = (total_x**2 + total_y**2) ** 0.5

        self.d = [total_x / mag, total_y / mag]

        # update dt
        self.velocity_change()

        # update, multiply by dt
        self.x += self.dt * self.d[0]
        self.y += self.dt * self.d[1]

        # boundary logic, make them bounce around if at edge of screen
        if self.x >= screen_width - 10:
            self.d[0] = -self.d[0]
            self.x = screen_width - 10
        if self.x <= 10:
            self.d[0] = -self.d[0]
            self.x = 10
        if self.y >= screen_height - 10:
            self.d[1] = -self.d[1]
            self.y = screen_height - 10
        if self.y <= 10:
            self.d[1] = -self.d[1]
            self.y = 10

        self.rect.update(self.x, self.y, 10, 10)

    def nearby_boids(self, all_boids: List) -> None:
        """
        get all the boids within distance of sight
        flock needs to pass boids in here

        return: List[tuple(boid, x direction, y direction)]
        """
        nearby = []
        for b in all_boids:
            x_d = b.x - self.x
            y_d = b.y - self.y

            mag_d = (x_d**2 + y_d**2) ** 0.5

            if mag_d <= self.sight:
                nearby.append(b)

        self.nearby = nearby

    def align(self) -> tuple:
        """
        return avg direction of nearby boids
        tuple(x, y)
        """
        total_d = [0, 0]
        for b in self.nearby:
            total_d[0] += b.d[0]
            total_d[1] += b.d[1]

        avg = (total_d[0] / len(self.nearby), total_d[1] / len(self.nearby))
        return avg

    def cohese(self) -> tuple:
        """
        return average position of nearby_boids
        as a direction vector from self
        """
        total_p = [0, 0]
        for b in self.nearby:
            total_p[0] += b.x
            total_p[1] += b.y

        avg = (total_p[0] / len(self.nearby), total_p[1] / len(self.nearby))
        direction = (avg[0] - self.x, avg[1] - self.y)
        return direction

    def separate(self) -> tuple:
        """
        steer away from nearby boids that are too close
        returns a direction vector pointing away from crowded neighbors
        """
        if len(self.nearby) == 0:
            return (0, 0)

        steer_x = 0
        steer_y = 0

        for b in self.nearby:
            if b != self:
                dx = self.x - b.x
                dy = self.y - b.y
                distance = (dx**2 + dy**2) ** 0.5

                if distance > 0 and distance < 50:
                    steer_x += dx / distance
                    steer_y += dy / distance

        mag = (steer_x**2 + steer_y**2) ** 0.5
        if mag > 0:
            return (steer_x / mag, steer_y / mag)
        return (0, 0)

    def velocity_change(self) -> None:
        """
        boids are faster with more friends!
        """
        self.dt = 1 + len(self.nearby) * 0.5


class flock:
    """
    all the boids on da frame
    """

    def __init__(self, n) -> None:
        # 390 360
        self.boids = []
        for _ in range(n):
            self.boids.append(
                boid(random.randrange(100, 900), random.randrange(100, 900))
            )

        self.rects = []
        for b in self.boids:
            self.rects.append(b.rect)

    def flyem(self) -> None:
        for b in self.boids:
            b.nearby_boids(self.boids)
            b.fla()

    def _view_radius(self) -> None:
        """
        helper for debugging to see _view_radius
        """
        for boi in self.boids:
            pygame.draw.circle(screen, "red", (boi.x, boi.y), boi.sight, width=1)

    def _view_direction(self) -> None:
        """
        helper to view direction of boid
        """
        for b in self.boids:
            center = (b.x + 5, b.y + 5)
            end = (center[0] + b.d[0] * 15, center[1] + b.d[1] * 15)
            pygame.draw.line(screen, "black", center, end, width=2)

    def add_boid(self) -> None:
        """
        add boid on click
        """
        pass


if __name__ == "__main__":
    flocky = flock(100)
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        screen.fill("white")

        background = pygame.image.load("Toronto_map.png")

        flocky.flyem()
        flocky._view_direction()
        for recty in flocky.boids:
            pygame.draw.rect(screen, "blue", recty.rect, 40)

        pygame.display.flip()
        clock.tick(144)

    pygame.quit()
