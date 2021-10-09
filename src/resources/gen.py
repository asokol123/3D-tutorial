#!/usr/bin/env python3

import json
import sys

def gen_cube(filename: str):
    colors = [
        "white",
        "red",
        "green",
        "blue",
        "yellow",
        "magenta",
        "cyan",
    ]

    x = [{
        'type': 'cube',
        'colors': colors,
        'points': [
                {'x': 0, 'y': 0, 'z': 10},
                {'x': 1, 'y': 0, 'z': 10},
                {'x': 0, 'y': 1, 'z': 10},
                {'x': 0, 'y': 0, 'z': 11},
        ]
    }]

    with open(filename, 'w') as fout:
        json.dump(x, fout, indent=4, sort_keys=True)

if __name__ == '__main__':
    gen_cube('./resources/cube.json')
