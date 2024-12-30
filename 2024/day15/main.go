package main

import (
	_ "embed"
	"flag"
	"fmt"
	"slices"
	"strings"
)

//go:embed input.txt
var input string

func init() {
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

var (
	WALL     = 0
	BOX      = 1
	EMPTY    = 2
	BOXLEFT  = 4
	BOXRIGHT = 8
)

type Dir struct {
	dx int
	dy int
}

var dirTranslate map[rune]Dir = map[rune]Dir{
	'>': Dir{dx: 1, dy: 0},
	'^': Dir{dx: 0, dy: -1},
	'<': Dir{dx: -1, dy: 0},
	'v': Dir{dx: 0, dy: 1},
}

func part1(input string) int {

	var kort [][]int
	rx := 0
	ry := 0

	kortloading := true
	for i, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")

		if kortloading {

			if line == "" {
				kortloading = false
				continue
			}

			var row []int
			for j, a := range line {
				if a == '#' {
					row = append(row, WALL)
				} else if a == 'O' {
					row = append(row, BOX)
				} else if a == '.' {
					row = append(row, EMPTY)
				} else if a == '@' {
					rx = j
					ry = i
					row = append(row, EMPTY)
				} else {
					panic("Unknow symbol")
				}
			}
			kort = append(kort, row)
		} else {
			for _, c := range line {
				if c == '\n' {
					continue
				}
				dir := dirTranslate[c]
				if canMove(kort, rx, ry, dir) {
					rx, ry = rx+dir.dx, ry+dir.dy
				}
			}
		}
	}
	printKort(kort)

	sum := 0

	for i, row := range kort {
		for j, c := range row {
			if c == BOX {
				sum += i*100 + j
			}
		}
	}

	return sum
}

func canMove(kort [][]int, x, y int, dir Dir) bool {
	tx, ty := x+dir.dx, y+dir.dy
	switch kort[ty][tx] {
	case WALL:
		return false
	case BOX:
		if canMove(kort, tx, ty, dir) {
			kort[ty][tx] = kort[y][x]
			kort[y][x] = EMPTY
			return true
		}
		return false
	case EMPTY:
		kort[ty][tx] = kort[y][x]
		kort[y][x] = EMPTY
		return true

	default:
		panic("omg somthing is wroing")
	}
}

func printKort(kort [][]int) {
	for _, row := range kort {
		for _, c := range row {
			if c == WALL {
				fmt.Printf("#")
			} else if c == BOX {
				fmt.Printf("O")
			} else if c == EMPTY {
				fmt.Printf(".")
			}

		}
		fmt.Printf("\n")
	}
}

func part2(input string) int {

	var kort [][]int
	rx := 0
	ry := 0

	kortloading := true
	for i, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")

		if kortloading {
			if line == "" {
				kortloading = false
				fmt.Println("Initial state:")
				printKort2(kort, rx, ry)
				continue
			}

			var row []int
			for j, a := range line {
				if a == '#' {
					row = append(row, WALL)
					row = append(row, WALL)
				} else if a == 'O' {
					row = append(row, BOXLEFT)
					row = append(row, BOXRIGHT)
				} else if a == '.' {
					row = append(row, EMPTY)
					row = append(row, EMPTY)
				} else if a == '@' {
					rx = j * 2
					ry = i
					row = append(row, EMPTY)
					row = append(row, EMPTY)
				} else {
					panic("Unknow symbol")
				}
			}
			kort = append(kort, row)
		} else {
			for _, c := range line {
				if c == '\n' {
					continue
				}
				// fmt.Printf("%c", c)
				dir := dirTranslate[c]
				canMove, acc := canMove2(kort, rx+dir.dx, ry+dir.dy, dir)
				if canMove {

					rx, ry = rx+dir.dx, ry+dir.dy
					done := []Pos{}

					for _, p := range acc {
						if slices.Contains(done, p) {
							// panic("Same move twice")
							continue
						}

						tx, ty := p.x+dir.dx, p.y+dir.dy
						kort[ty][tx] = kort[p.y][p.x]
						kort[p.y][p.x] = EMPTY
						done = append(done, p)
					}
				}
			}
			// fmt.Println("")
			// fmt.Println(i)
			// printKort2(kort, rx, ry)
		}
	}

	sum := 0

	for i, row := range kort {
		for j, c := range row {
			if c == BOXLEFT {
				sum += i*100 + j
			}
		}
	}

	return sum
}

type Pos struct {
	x int
	y int
}

func canMove2(kort [][]int, x, y int, dir Dir) (bool, []Pos) {
	curr := kort[y][x]
	if curr == WALL {
		return false, []Pos{}
	} else if curr == EMPTY {
		return true, []Pos{}
	}

	tx, ty := x+dir.dx, y+dir.dy
	if dir.dx == 0 { // Vertical Move
		switch curr {
		case BOXRIGHT:
			canMoveRight, accRight := canMove2(kort, tx, ty, dir)
			canMoveLeft, accLeft := canMove2(kort, tx-1, ty, dir)
			if canMoveLeft && canMoveRight {
				acc := append(accRight, accLeft...)

				add := []Pos{{x, y}, {x - 1, y}}
				return true, append(acc, add...)
			}
			return false, []Pos{}
		case BOXLEFT:
			canMoveLeft, accLeft := canMove2(kort, tx, ty, dir)
			canMoveRight, accRight := canMove2(kort, tx+1, ty, dir)
			if canMoveLeft && canMoveRight {
				acc := append(accLeft, accRight...)

				add := []Pos{{x, y}, {x + 1, y}}
				return true, append(acc, add...)
			}
			return false, []Pos{}
		default:
			panic("omg somthing is wrong")
		}
	} else if dir.dy == 0 { // Horizontal Move
		switch curr {
		case BOXRIGHT:
			canMoveRight, acc := canMove2(kort, tx-1, ty, dir)
			if canMoveRight {
				return true, append(acc, Pos{x - 1, y}, Pos{x, y})
			}
			return false, []Pos{}
		case BOXLEFT:
			canMoveRight, acc := canMove2(kort, tx+1, ty, dir)
			if canMoveRight {
				return true, append(acc, Pos{x + 1, y}, Pos{x, y})
			}
			return false, []Pos{}
		default:
			panic("omg somthing is wrong")
		}
	}
	return false, []Pos{}
}

func printKort2(kort [][]int, rx, ry int) {
	for i, row := range kort {
		for j, c := range row {
			if i == ry && j == rx {
				fmt.Printf("@")
			} else if c == WALL {
				fmt.Printf("#")
			} else if c == BOXLEFT {
				fmt.Printf("[")
			} else if c == BOXRIGHT {
				fmt.Printf("]")
			} else if c == EMPTY {
				fmt.Printf(".")
			}

		}
		fmt.Printf("\n")
	}
}
