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

type Dir struct {
	dx int
	dy int
}

type Pos struct {
	x int
	y int
}

var (
	WALL  = -1
	EMPTY = 0
)

func part1(input string) int {

	var course [][]int
	var start Pos
	var end Pos
	for i, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")

		var row []int
		for j, a := range line {
			if a == '#' {
				row = append(row, WALL)
			} else if a == '.' {
				row = append(row, EMPTY)
			} else if a == 'S' {
				start = Pos{x: j, y: i}
				row = append(row, EMPTY)
			} else if a == 'E' {
				end = Pos{x: j, y: i}
				row = append(row, EMPTY)
			} else {
				panic("Unknow symbol")
			}
		}
		course = append(course, row)
	}

	printCourse(course)
	// fmt.Println(start, end)
	race(course, start, end)
	// for _, a := range course {
	// 	fmt.Println(a)
	// }

	cheats := cheat(course)
	count := 0

	for key, val := range cheats {
		fmt.Println(key, ": ", val)
		if key >= 100 {
			count += val
		}
	}

	return count
}

var dirs []Pos = []Pos{
	{1, 0},
	{0, -1},
	{-1, 0},
	{0, 1},
}

func race(course [][]int, start, end Pos) {

	curr := start
	count := 1

	c := func(p Pos) int {
		return course[p.y][p.x]
	}

	for curr != end {
		course[curr.y][curr.x] = count
		count++

		for _, d := range dirs {
			next := Pos{curr.x + d.x, curr.y + d.y}
			if c(next) == EMPTY {
				curr = next
				break
			}
		}
	}

	course[curr.y][curr.x] = count

}

func cheat(course [][]int) map[int]int {
	cheats := make(map[int]int)

	c := func(p Pos) int {
		return course[p.y][p.x]
	}

	out_of_bounds := func(p Pos) bool { return p.y < 0 || p.y >= len(course) || p.x < 0 || p.x >= len(course[p.y]) }

	for y, row := range course {
		for x, a := range row {
			if a > EMPTY {
				for _, d := range dirs {
					next := Pos{x + 2*d.x, y + 2*d.y}
					if out_of_bounds(next) {
						continue
					}
					if c(next) > EMPTY {
						saved := c(next) - a - 2
						if saved > 0 {
							cheats[saved]++
						}
					}
				}
			}
		}
	}

	return cheats
}

func printCourse(cource [][]int) {
	for _, row := range cource {
		for _, c := range row {
			if c == WALL {
				fmt.Printf("#")
			} else if c == EMPTY {
				fmt.Printf(".")
			}
		}
		fmt.Printf("\n")
	}
}

func part2(input string) int {

	var course [][]int
	var start Pos
	var end Pos
	for i, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")

		var row []int
		for j, a := range line {
			if a == '#' {
				row = append(row, WALL)
			} else if a == '.' {
				row = append(row, EMPTY)
			} else if a == 'S' {
				start = Pos{x: j, y: i}
				row = append(row, EMPTY)
			} else if a == 'E' {
				end = Pos{x: j, y: i}
				row = append(row, EMPTY)
			} else {
				panic("Unknown symbol")
			}
		}
		course = append(course, row)
	}

	printCourse(course)
	// fmt.Println(start, end)
	race(course, start, end)
	// for _, a := range course {
	// 	fmt.Println(a)
	// }

	cheats := cheat2(course)
	count := 0

	for key, val := range cheats {
		// fmt.Println(key, ": ", val)
		if key >= 100 {
			count += val
		}
	}

	return count

}

func cheat2(course [][]int) map[int]int {
	cheats := make(map[int]int)

	for y, row := range course {
		for x, a := range row {
			if a > EMPTY {
				// fmt.Println(a)
				dp := make(map[Pos]int)
				searchCheats(course, Pos{x, y}, Pos{x, y}, dp)
				// fmt.Println(dp)
				for _, saved := range dp {
					if saved > 0 {
						cheats[saved]++
					}
				}
			}
		}
	}

	return cheats
}

func searchCheats(course [][]int, start, curr Pos, dp map[Pos]int) {
	c := func(p Pos) int {
		return course[p.y][p.x]
	}
	abs := func(x int) int {
		if x < 0 {
			return -x
		}
		return x
	}

	dist := abs(start.x-curr.x) + abs(start.y-curr.y)
	out_of_bounds := func(p Pos) bool { return p.y < 0 || p.y >= len(course) || p.x < 0 || p.x >= len(course[p.y]) }
	if dist > 20 || out_of_bounds(curr) {
		return
	}

	if _, exists := dp[curr]; exists {
		return
	}

	if c(curr) > EMPTY {
		saved := c(curr) - c(start) - dist
		// fmt.Println(start, curr, saved)
		dp[curr] = saved
	} else {
		dp[curr] = 0
	}
	for _, d := range dirs {
		next := Pos{curr.x + d.x, curr.y + d.y}
		searchCheats(course, start, next, dp)
	}
}
