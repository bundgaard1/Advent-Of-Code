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

type info struct {
	area      int
	perimeter int
}

func part1(input string) int {

	var garden [][]rune
	visited := make(map[pos]bool)

	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")

		gardenRow := []rune{}
		for _, plot := range line {
			gardenRow = append(gardenRow, plot)
		}

		garden = append(garden, gardenRow)
	}

	sum := 0

	for i, gardenRow := range garden {
		for j, c := range gardenRow {
			if visited[pos{j, i}] {
				continue
			}
			info := search(garden, visited, c, j, i)
			sum += info.area * info.perimeter

			fmt.Printf("%c : %d \n", c, info)
		}
	}

	return sum
}

type pos struct {
	x int
	y int
}

var dirs []pos = []pos{
	{1, 0},
	{0, -1},
	{-1, 0},
	{0, 1},
}

func out_of_bounds(garden [][]rune, x, y int) bool {
	return y < 0 || y >= len(garden) || x < 0 || x >= len(garden[y])
}

func search(garden [][]rune, visited map[pos]bool, state rune, x, y int) info {
	info := info{0, 0}

	if out_of_bounds(garden, x, y) || visited[pos{x, y}] || garden[y][x] != state {
		return info
	}

	visited[pos{x, y}] = true

	info.area += 1
	info.perimeter += perimeter(garden, x, y)

	for _, dir := range dirs {
		nx, ny := x+dir.x, y+dir.y

		ninfo := search(garden, visited, state, nx, ny)
		info.area += ninfo.area
		info.perimeter += ninfo.perimeter

	}

	return info
}

func perimeter(garden [][]rune, x, y int) int {

	c := garden[y][x]

	p := 4

	for _, dir := range dirs {
		nx, ny := x+dir.x, y+dir.y
		if out_of_bounds(garden, nx, ny) {
			continue
		}
		if garden[ny][nx] == c {
			p--
		}
	}
	return p
}

func part2(input string) int {
	var garden [][]rune
	visited := make(map[pos]bool)

	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")

		gardenRow := []rune{}
		for _, plot := range line {
			gardenRow = append(gardenRow, plot)
		}

		garden = append(garden, gardenRow)
	}

	sum := 0

	for i, gardenRow := range garden {
		for j, c := range gardenRow {
			if visited[pos{j, i}] {
				continue
			}
			info := search2(garden, visited, c, j, i)
			sum += info.area * info.perimeter

			fmt.Printf("%c : %d \n", c, info)
		}
	}
	for _, row := range garden {
		fmt.Printf("%c\n", row)

	}

	return sum
}
func search2(garden [][]rune, visited map[pos]bool, state rune, x, y int) info {
	info := info{0, 0}

	if out_of_bounds(garden, x, y) || visited[pos{x, y}] || garden[y][x] != state {
		return info
	}

	visited[pos{x, y}] = true

	info.area += 1
	info.perimeter += countSide(garden, x, y)

	for _, dir := range dirs {
		nx, ny := x+dir.x, y+dir.y

		ninfo := search2(garden, visited, state, nx, ny)
		info.area += ninfo.area
		info.perimeter += ninfo.perimeter

	}

	return info
}

func countSide(garden [][]rune, x, y int) int {

	c := garden[y][x]

	s := 0

	for i, dir := range dirs {
		ax, ay := x+dir.x, y+dir.y

		if out_of_bounds(garden, ax, ay) || garden[ay][ax] != c {
			nextdir := dirs[(i+1)%4]
			bx, by := x+nextdir.x, y+nextdir.y
			cx, cy := x+dir.x+nextdir.x, y+dir.y+nextdir.y

			// fmt.Println("countside:", "(", ax, ay, "), (", bx, by, "), (", cx, cy, ")")

			if !(!out_of_bounds(garden, bx, by) && garden[by][bx] == c && (out_of_bounds(garden, cx, cy) || garden[cy][cx] != c)) {
				s++
				// fmt.Println("Side counter", x, y, dir.x, dir.y)

			}

		}
	}
	return s
}
