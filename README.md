# Graph Visualization Program

## Introduction

This program is designed to visualize undirected graphs and create a BMP image representation of the graph.

## Features

- Visualizes undirected graphs with nodes and edges.
- Writes node IDs on the graph image.
- Supports BMP image format.

## Getting Started

### Prerequisites

- C++ compiler (supporting C++11 or later)

### Building the Program
Clone the repository:
```bash
git clone https://github.com/GigaKekes/GraphGenerator.git
```

Proceed to the folder
```bash
cd GraphGenerator
```

Create ```build``` folder
```bash
mkdir build && cd build
```

Use cmake to build the program
```bash
cmake .. && make
```
## Usage
To use this program run this comand
```
./GraphGenerator <Path/To/Your/File.txt>
```
### Input data
The input file should have the following structure 

V E - the first line specifies the number of vertices and edges 

u v - the next E lines specify the edges as pairs of vertex numbers


## Config file structure
| Name | Data Type | Recommended Value | Effect on Program |
|---|---|---|---|
| fruchtermanReingoldIterations | Integer | 3000 | Controls the number of iterations for the Fruchterman-Reingold layout algorithm. Higher values may improve layout balance but increase computation time. |
| offset | Integer | 54 | Specifies the byte offset within the BMP image file where pixel data starts. Modifying this value might cause the image to be unreadable. |
| width | Integer | 2000 | Sets the width of the output BMP image in pixels. |
| height | Integer | 2000 | Sets the height of the output BMP image in pixels. width and height may also affect edges length and readability of visualisation. |

## License

This project is licensed under the MIT License. Feel free to modify, distribute, and use the code for personal and educational purposes.

## Contact
If you have any questions, suggestions, or feedback, please feel free to contact me st119023@student.spbu.ru
