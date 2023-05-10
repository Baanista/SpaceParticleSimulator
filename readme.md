# OverView

This program is meant to simulate particle physics and evolutionary patterns.

# Runing the Program

1.) in terminal go into the projects directory

2.)then do ./go.sh

# Controls 

-press space to spawn a particle at the mouse evry tick

-press S to spawn grid of 5 by 5 particles at the mouse

-press TAB to bring up the my custimized consol

(message me for any questions)

here is my discord(https://discord.gg/xYbyAZScMG)

# How particles work?

Each particle has a position, velocity, and a id. The ID determines how the particle works and how it looks like. It's behavior is: how it interacts with other and its air resistance[double damp;]

# How Cells work?

Every cell inherits the properties of the particle ID 0. Each cell has a genome. Genome determines how the cell looks, and the max_size. Each cell produces energy every tick. The size of the cell is determined by the square root of the amount of energy. The bigger the size of the cell the more energy it takes up per tick. If a cell is 2 times larger than a cell that it collides with the larger cell gets all the energy of the other cell and kills that cell. Each tick the lifetime counter goes up. If the counter extends max_size * 1000 than the cell is dead.

## Preditor and Pray relationship
![Screen Shot 2023-05-09 at 10 16 18 PM](https://github.com/Baanista/SpaceParticleSimulator/assets/110647786/23422e2a-e7e0-42c8-a01e-0433ee5a1a63)
## Same simulation given more time. The Predatorstor and prey color changed.
![Screen Shot 2023-05-10 at 6 52 24 AM](https://github.com/Baanista/SpaceParticleSimulator/assets/110647786/a18849b3-c5e4-4f66-bee4-310d947a0972)
## Diffrent simulation. Prey and predator have a similar size.
![Screen Shot 2023-05-09 at 9 31 04 PM](https://github.com/Baanista/SpaceParticleSimulator/assets/110647786/d3b98d3a-6b12-4297-909f-52a8d021af63)

# New Features Comming Soon!

## -Pheromons

    -Cells can emmit pheromones using their cell response mechanism. They can control the spread, velocity, color, and duration of each pheromone.

    -Pheromon Map: each chunk in th map will be contain the avrage inside and outline color inside that chunk. The information in each chunk will be given to the cells "brain".

## -Cell Response Mechanism("Brain")

	-Input: The inputs are energy, lifetime, size, maxsize, and pheromone chunk details.
	
	-Output: The cell controls the details of the emitted pheromones. The cell can also control its direction. The cell can also control how much they go in that direction.







