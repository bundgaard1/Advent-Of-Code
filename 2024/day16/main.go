package main

import (
	_ "embed"
	"flag"
	"fmt"
	"math"
	"slices"
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

var INFTY = math.MaxInt

type Dir struct {
	dx int
	dy int
}

type Pos struct {
	x int
	y int
}

var (
	WALL    = 0
	EMPTY   = 1
	START   = 2
	END     = 3
	VISITED = 4
)

func part1(input string) int {
	var kort [][]int
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
				row = append(row, START)
			} else if a == 'E' {
				end = Pos{x: j, y: i}
				row = append(row, END)
			} else {
				panic("Unknow symbol")
			}
		}
		kort = append(kort, row)
	}

	printKort(kort)
	dp := make(map[Key]Value)

	dir := Dir{dx: 1, dy: 0}
	search(kort, start, dir, 0, dp)

	for i := 0; i < 4; i++ {
		key := Key{Pos: end, Dir: dir}
		score := dp[key]
		fmt.Println(key, " : ", score)
		dir = turnRight(dir)
	}

	return 0
}

func getKort(kort [][]int, p Pos) int {
	return kort[p.y][p.x]
}

func move(p Pos, d Dir) Pos {
	return Pos{p.x + d.dx, p.y + d.dy}
}

func turnRight(d Dir) Dir {
	return Dir{d.dy, -d.dx}
}

func turnLeft(d Dir) Dir {
	return Dir{-d.dy, d.dx}
}

type Key struct {
	Pos
	Dir
}

func search(kort [][]int, p Pos, d Dir, score int, dp map[Key]Value) int {
	// fmt.Println(p)
	if getKort(kort, p) == WALL {
		return INFTY
	}

	key := Key{Pos: p, Dir: d}
	if saved, ok := dp[key]; ok {
		if saved.soFar < score {
			return INFTY
		} else if saved.soFar == score {
			return saved.endCost
		}
	}

	dp[key] = Value{soFar: score, endCost: INFTY}

	if getKort(kort, p) == END {
		// printKort(kort)
		fmt.Println(score)
		return score
	}

	s1 := search(kort, move(p, d), d, score+1, dp)

	right := turnRight(d)
	s2 := search(kort, p, right, score+1000, dp)

	left := turnLeft(d)
	s3 := search(kort, p, left, score+1000, dp)

	minScore := min(s1, s2, s3)

	dp[key] = Value{soFar: score, endCost: minScore}

	return minScore

}

func printKort(kort [][]int) {
	for _, row := range kort {
		for _, c := range row {
			if c == WALL {
				fmt.Printf("#")
			} else if c == EMPTY {
				fmt.Printf(".")
			} else if c == START {
				fmt.Printf("S")
			} else if c == END {
				fmt.Printf("E")
			} else if c == VISITED {
				fmt.Printf("o")
			}

		}
		fmt.Printf("\n")
	}
}

func part2(input string) int {
	var kort [][]int
	var start Pos
	// var end Pos
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
				row = append(row, START)
			} else if a == 'E' {
				// end = Pos{x: j, y: i}
				row = append(row, END)
			} else {
				panic("Unknow symbol")
			}
		}
		kort = append(kort, row)
	}

	printKort(kort)
	dp := make(map[Key]Value)

	dir := Dir{dx: 1, dy: 0}
	score, trail := search2(kort, start, dir, 0, dp)
	fmt.Println(score)
	fmt.Println(trail)
	for _, t := range trail {
		kort[t.y][t.x] = VISITED
	}
	printKort(kort)

	count := 0
	done := []Pos{}
	for _, t := range trail {
		if slices.Contains(done, t) {
			continue
		} else {
			count++
			done = append(done, t)
		}
	}

	return count
}

type Value struct {
	soFar   int
	endCost int
}

func search2(kort [][]int, p Pos, d Dir, score int, dp map[Key]Value) (int, []Pos) {
	// fmt.Println(p)
	if getKort(kort, p) == WALL {
		return INFTY, []Pos{}
	}

	key := Key{Pos: p, Dir: d}
	if saved, ok := dp[key]; ok {
		if saved.soFar < score {
			return INFTY, []Pos{}
		}
		if saved.soFar == score {
			return saved.endCost, []Pos{p}
		}
	}

	dp[key] = Value{soFar: score, endCost: INFTY}

	if getKort(kort, p) == END {
		// printKort(kort)
		fmt.Println(score)

		dp[key] = Value{soFar: score, endCost: score}
		return score, []Pos{p}
	}

	s1, trail1 := search2(kort, move(p, d), d, score+1, dp)

	left := turnLeft(d)
	s2, trail2 := search2(kort, p, left, score+1000, dp)

	right := turnRight(d)
	s3, trail3 := search2(kort, p, right, score+1000, dp)

	minEndScore := min(s1, s2, s3)
	trail := []Pos{p}

	if s1 == minEndScore {
		trail = append(trail, trail1...)
	}
	if s2 == minEndScore {
		trail = append(trail, trail2...)
	}
	if s3 == minEndScore {
		trail = append(trail, trail3...)
	}

	dp[key] = Value{soFar: score, endCost: minEndScore}

	return minEndScore, trail
}
