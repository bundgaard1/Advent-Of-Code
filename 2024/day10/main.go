package main

import (
	"aoc24/utils"
	_ "embed"
	"flag"
	"fmt"
	"slices"
	"sort"
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

func part1(input string) int {
	var kort [][]int

	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		last := []int{}
		for _, c := range line {
			n := utils.ToInt(c)
			last = append(last, n)
		}
		kort = append(kort, last)
	}

	for _, l := range kort {
		fmt.Println(l)
	}

	sum := 0

	for i, row := range kort {
		for j, h := range row {
			if h == 0 {
				tops := trailhead(kort, 0, j, i)
				sort.Slice(tops, func(i, j int) bool {
					return tops[i].x < tops[j].x || tops[i].y < tops[j].y
				})
				tops = slices.Compact(tops)
				// fmt.Println(tops)
				sum += len(tops)
			}
		}
	}

	return sum
}

type pos struct {
	x int
	y int
}

var dirs []pos = []pos{
	{-1, 0},
	{0, 1},
	{1, 0},
	{0, -1},
}

func trailhead(kort [][]int, state, x, y int) []pos {
	// fmt.Printf("%d : (%d,%d)\n", state, x, y)
	out_of_bounds := func(x, y int) bool { return y < 0 || y >= len(kort) || x < 0 || x >= len(kort[y]) }

	if state == 9 {
		// fmt.Println("FOUND")
		return []pos{{x, y}}
	}

	head := []pos{}

	for _, dir := range dirs {
		nx, ny := x+dir.x, y+dir.y
		if out_of_bounds(nx, ny) {
			continue
		}
		next := kort[ny][nx]
		if next == state+1 {
			ahead := trailhead(kort, next, nx, ny)
			head = append(head, ahead...)
		}
	}

	return head

}

func part2(input string) int {
	var kort [][]int

	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		last := []int{}
		for _, c := range line {
			n := utils.ToInt(c)
			last = append(last, n)
		}
		kort = append(kort, last)
	}

	for _, l := range kort {
		fmt.Println(l)
	}

	sum := 0

	for i, row := range kort {
		for j, h := range row {
			if h == 0 {
				tops := trailhead2(kort, 0, j, i)
				// fmt.Println(tops)
				sum += tops
			}
		}
	}

	return sum
}

func trailhead2(kort [][]int, state, x, y int) int {
	// fmt.Printf("%d : (%d,%d)\n", state, x, y)
	out_of_bounds := func(x, y int) bool { return y < 0 || y >= len(kort) || x < 0 || x >= len(kort[y]) }

	if state == 9 {
		// fmt.Println("FOUND")
		return 1
	}

	count := 0

	for _, dir := range dirs {
		nx, ny := x+dir.x, y+dir.y
		if out_of_bounds(nx, ny) {
			continue
		}
		next := kort[ny][nx]
		if next == state+1 {
			count += trailhead2(kort, next, nx, ny)
		}
	}

	return count

}
