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

var ws [][]byte

func part1(input string) int {

	for _, line := range strings.Split(input, "\n") {
		fmt.Println(line)
		ws_line := []byte{}
		for _, char := range line {
			ws_line = append(ws_line, byte(char))
		}
		ws = append(ws, ws_line)
	}

	sum := 0

	for i, line := range ws {
		for j, char := range line {
			if string(char) != "X" {
				continue
			}

			for dx := -1; dx <= 1; dx++ {
				for dy := -1; dy <= 1; dy++ {
					x, y := j+dx, i+dy

					if search("X", x, y, dx, dy) {
						sum++
					}

				}
			}
		}
	}

	return sum
}

func get_char(x, y int) string {
	return string(ws[y][x])
}

func search(state string, x, y int, dx, dy int) bool {
	// fmt.Println(state, x, y)

	if bounds_not_ok(x, y) {
		return false
	}

	if state == "X" {
		if get_char(x, y) == "M" {
			return search("M", x+dx, y+dy, dx, dy)
		}

	} else if state == "M" {
		if get_char(x, y) == "A" {
			return search("A", x+dx, y+dy, dx, dy)
		}

	} else if state == "A" {
		if get_char(x, y) == "S" {
			return true
		}
	}
	return false
}

func bounds_not_ok(x, y int) bool {
	return y < 0 || y >= len(ws) || x < 0 || x >= len(ws[y])

}

func part2(input string) int {
	for _, line := range strings.Split(input, "\n") {
		fmt.Println(line)
		ws_line := []byte{}
		for _, char := range line {
			ws_line = append(ws_line, byte(char))
		}
		ws = append(ws, ws_line)
	}

	sum := 0

	for i, line := range ws {
		for j, char := range line {
			if string(char) != "A" {
				continue
			}
			if search2(j, i) {
				sum++
			}

		}
	}

	return sum
}

func bounds_not_ok2(x, y int) bool {
	return y < 1 || y >= len(ws)-1 || x < 1 || x >= len(ws[y])-1

}

func search2(x, y int) bool {
	if bounds_not_ok2(x, y) {
		return false
	}

	corners := []string{
		get_char(x-1, y-1),
		get_char(x-1, y+1),
		get_char(x+1, y-1),
		get_char(x+1, y+1),
	}

	Ms, Ss := 0, 0

	for _, c := range corners {
		Ms, Ss = func(char string, M, S int) (int, int) {
			if char == "M" {
				return M + 1, S
			} else if char == "S" {
				return M, S + 1
			} else {
				return M, S
			}
		}(c, Ms, Ss)
	}

	if Ms == 2 && Ss == 2 {
		if corners[0] == corners[1] || corners[0] == corners[2] {
			return true
		}
	}

	return false
}
