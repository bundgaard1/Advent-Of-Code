package main

import (
	_ "embed"
	"flag"
	"fmt"
	"strings"
)

//go:embed input.txt
var input string

func init() {
	// do this in init (not main) so test file has same input
	input = strings.TrimRight(input, "\n")
	if len(input) == 0 {
		panic("empty input.txt file")
	}
}

func main() {
	var part int
	flag.IntVar(&part, "part", 1, "part 1 or 2")
	flag.Parse()
	fmt.Println("Running part", part)

	if part == 1 {
		ans := part1(input)
		fmt.Println("Output:", ans)
	} else {
		ans := part2(input)
		fmt.Println("Output:", ans)
	}
}

type pos struct {
	x int
	y int
}

func part1(input string) int {

	var antinodes [][]bool
	antennas := make(map[rune][]pos)

	bounds := func(x, y int) bool {
		return y < 0 ||
			y >= len(antinodes) ||
			x < 0 ||
			x >= len(antinodes[y])
	}

	for y, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")

		var anLine []bool
		for x, a := range line {
			anLine = append(anLine, false)
			if a == '.' {
				continue
			}

			antennas[a] = append(antennas[a], pos{x, y})
		}

		antinodes = append(antinodes, anLine)
	}

	for key, aPos := range antennas {
		fmt.Printf("%c : %d\n", key, aPos)

		for i, a := range aPos {

			for j, o := range aPos {
				if i == j {
					continue
				}

				diff := pos{x: a.x - o.x, y: a.y - o.y}
				an := pos{x: a.x + diff.x, y: a.y + diff.y}
				if !bounds(an.x, an.y) {
					antinodes[an.y][an.x] = true
				}
				fmt.Println("new antinode: ", an.x, an.y)
			}
		}
	}

	count := 0

	for _, line := range antinodes {
		for _, an := range line {
			if an {
				fmt.Print("X")
				count++
			} else {
				fmt.Print(".")
			}
		}
		fmt.Printf("\n")
	}

	return count
}

func part2(input string) int {
	var antinodes [][]bool
	antennas := make(map[rune][]pos)

	bounds := func(x, y int) bool {
		return y < 0 ||
			y >= len(antinodes) ||
			x < 0 ||
			x >= len(antinodes[y])
	}

	for y, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")

		var anLine []bool
		for x, a := range line {
			anLine = append(anLine, false)
			if a == '.' {
				continue
			}

			antennas[a] = append(antennas[a], pos{x, y})
		}

		antinodes = append(antinodes, anLine)
	}

	for key, aPos := range antennas {
		fmt.Printf("%c : %d\n", key, aPos)

		for i, a := range aPos {

			for j, o := range aPos {
				if i == j {
					continue
				}

				diff := pos{x: o.x - a.x, y: o.y - a.y}
				an := pos{x: o.x, y: o.y}
				for !bounds(an.x, an.y) {
					antinodes[an.y][an.x] = true
					an = pos{x: an.x + diff.x, y: an.y + diff.y}
					fmt.Println("new antinode: ", an.x, an.y)
				}
			}
		}
	}

	count := 0

	for _, line := range antinodes {
		for _, an := range line {
			if an {
				fmt.Print("X")
				count++
			} else {
				fmt.Print(".")
			}
		}
		fmt.Printf("\n")
	}

	return count
}
