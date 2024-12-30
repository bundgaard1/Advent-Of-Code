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

const (
	EMPTY   = 0x0
	ROCK    = 0x1
	VISITED = 0x2
	UP      = 0x4
	DOWN    = 0x8
	LEFT    = 0x10
	RIGHT   = 0x20
)

var kort [][]int

func part1(input string) int {

	sx, sy := 0, 0

	for i, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		var row []int
		for j, c := range line {
			if c == rune('.') {
				row = append(row, EMPTY)
			} else if c == rune('#') {
				row = append(row, ROCK)
			} else if c == rune('^') {
				row = append(row, VISITED)
				sx, sy = j, i
			} else {
				panic("unknow character enconutered: ")
			}
		}
		kort = append(kort, row)
	}
	// for _, row := range kort {
	// 	fmt.Println(row)
	// }

	x, y := sx, sy
	dx, dy := 0, -1

	for {
		// fmt.Println(x, y, dx, dy)

		kort[y][x] = VISITED
		nx, ny := x+dx, y+dy
		if bounds(nx, ny) {
			break
		}

		next := kort[ny][nx]

		if next == ROCK {
			dx, dy = turn_right(dx, dy)
		} else {
			x, y = x+dx, y+dy
		}
	}
	for _, row := range kort {
		fmt.Println(row)
	}

	sum := 0

	for i := 0; i < len(kort); i++ {
		for j := 0; j < len(kort[i]); j++ {
			if kort[i][j] == VISITED {
				sum++
			}
		}
	}
	return sum
}

func bounds(x, y int) bool {
	return y < 0 ||
		y >= len(kort) ||
		x < 0 ||
		x >= len(kort[y])

}

func turn_right(dx, dy int) (int, int) {
	if dx == 1 {
		return 0, 1
	} else if dx == -1 {
		return 0, -1
	} else if dy == 1 {
		return -1, 0
	} else {
		return 1, 0
	}
}

func direction(dx, dy int) int {
	if dy == -1 {
		return UP
	} else if dy == 1 {
		return DOWN
	} else if dx == -1 {
		return LEFT
	} else {
		return RIGHT
	}
}

func part2(input string) int {
	kort = [][]int{}
	sx, sy := 0, 0

	for i, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		var row []int
		for j, c := range line {
			if c == rune('.') {
				row = append(row, EMPTY)
			} else if c == rune('#') {
				row = append(row, ROCK)
			} else if c == rune('^') {
				row = append(row, VISITED)
				sx, sy = j, i
			} else {
				panic("unknow character enconutered: ")
			}
		}
		kort = append(kort, row)
	}

	x, y := sx, sy
	dx, dy := 0, -1

	sum := 0

	for {
		// fmt.Println(x, y, dx, dy)
		kort[y][x] = VISITED
		nx, ny := x+dx, y+dy
		if bounds(nx, ny) {
			break
		}

		next := kort[ny][nx]

		if next == ROCK {
			dx, dy = turn_right(dx, dy)
		} else {
			x, y = x+dx, y+dy
		}
	}

	for i := 0; i < len(kort); i++ {
		for j := 0; j < len(kort[i]); j++ {
			if kort[i][j]&VISITED == VISITED {
				before := kort[i][j]
				kort[i][j] = ROCK
				if gets_stuck(sx, sy, 0, -1) {
					fmt.Println(i, j)
					sum++
				}
				kort[i][j] = before
			}
		}
	}

	return sum
}

func gets_stuck(x, y, dx, dy int) bool {

	hash := func(x, y, dir int) int {
		hash := ((dir >> 2) & 0xf) |
			((y << 4) & 0x3ff0) |
			((x << 14) & 0xffc000)
		// fmt.Printf("%b, %b, %b\n%b \n", x, y, dir, hash)
		return hash
	}

	visited := map[int]bool{}

	for {
		DIR := direction(dx, dy)
		// fmt.Println("  ", x, y, DIR)

		if visited[hash(x, y, DIR)] {
			return true
		}
		visited[hash(x, y, DIR)] = true

		nx, ny := x+dx, y+dy
		if bounds(nx, ny) {
			break
		}

		next := kort[ny][nx]

		if next == ROCK {
			dx, dy = turn_right(dx, dy)
		} else {
			x, y = x+dx, y+dy
		}

	}

	return false
}
