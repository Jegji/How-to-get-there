# How to get there

The goal of this project is to find the shortest path between given cities using various algorithms and data structures.

# Input Pattern

First the dimension of the map (two int). \
Then load the map. \
'.' represent empty space,\
'#' represent road with take 1 unit of time to travel, \
'*' represents city. Letters represent the name of city.\
Then put the numbers of flights\
In next lines put flights in format:\
[source] [destination] [time]\
Then put the numbers of questions\
In next lines put questions in format:\
[source] [destination] [type]
types:\
0: fastest time from source to destination and all the visited cites\
1: only fastes time from source to destination
# Example of input
## INPUT:
```
20 20
.........GDANSK.....
........*...........
........#...........
........#...........
*##################.
#SZCZECIN.........#.
#.................#.
##................#.
.############*#####.
.#...WARSZAWA.......
.#..................
.#############......
.#...........#......
.#..WROCLAW.##......
.#..*.......*.......
.####.......#KIELCE.
......*##.#########.
.OPOLE..#.*.......#.
........#.KRAKOW..#.
........###########.


2
KRAKOW GDANSK 10
WARSZAWA WROCLAW 3
3
KRAKOW GDANSK 1
WARSZAWA WROCLAW 1
SZCZECIN KRAKOW 1
```
## OUTPUT:
```
10
3
29 KIELCE
```
