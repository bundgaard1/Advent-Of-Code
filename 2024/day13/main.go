package main

import (
	"aoc24/utils"
	"bufio"
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

type Pos struct {
	x int
	y int
}

func subPos(a Pos, b Pos) Pos {
	return Pos{a.x - b.x, a.y - b.y}
}

type Machine struct {
	A     Pos
	B     Pos
	Prize Pos
}

func part1(input string) int {
	scanner := bufio.NewScanner(strings.NewReader(input))

	parsePair := func(line string) Pos {
		fields := strings.Fields(line)
		a := utils.ToInt(fields[0])
		b := utils.ToInt(fields[1])
		return Pos{a, b}
	}

	sum := 0

	for scanner.Scan() {
		line1 := strings.TrimSpace(scanner.Text())
		if line1 == "" {
			continue // Skip empty lines
		}
		pair1 := parsePair(line1)

		// Read next pair
		scanner.Scan()
		line2 := strings.TrimSpace(scanner.Text())
		pair2 := parsePair(line2)

		// Read final pair
		scanner.Scan()
		line3 := strings.TrimSpace(scanner.Text())
		final := parsePair(line3)

		// Add to result
		machine := Machine{
			A:     pair1,
			B:     pair2,
			Prize: final,
		}

		tokens := tokensNeeded(machine)
		fmt.Println(tokens)

		sum += tokensNeeded(machine)

	}

	return sum
}

func tokensNeeded(m Machine) int {

	visited := make(map[Pos]bool)

	a, b := dfs(m.A, m.B, 0, 0, m.Prize, visited)

	if a >= 0 {
		return a*3 + b
	}

	return 0
}

func dfs(A Pos, B Pos, nA, nB int, target Pos, visited map[Pos]bool) (int, int) {
	// fmt.Println(target, nA, nB)
	if target.x == 0 && target.y == 0 {
		return 0, 0
	}
	if target.x < 0 || target.y < 0 {
		return -1000, -1000
	}
	if visited[Pos{nA, nB}] {
		return -1000, -1000
	}

	a, b := dfs(A, B, nA, nB+1, subPos(target, B), visited)
	if a >= 0 {
		return a, b + 1 // The B branch has found the target
	}
	a, b = dfs(A, B, nA+1, nB, subPos(target, A), visited)
	if b >= 0 {
		return a + 1, b // The A branch has found the target
	}

	visited[Pos{nA, nB}] = true

	return -1000, -1000

}
func part2(input string) int {
	extra := 10000000000000
	scanner := bufio.NewScanner(strings.NewReader(input))

	parsePair := func(line string) Pos {
		fields := strings.Fields(line)
		a := utils.ToInt(fields[0])
		b := utils.ToInt(fields[1])
		return Pos{a, b}
	}

	var sum int = 0

	for scanner.Scan() {
		line1 := strings.TrimSpace(scanner.Text())
		if line1 == "" {
			continue // Skip empty lines
		}
		pair1 := parsePair(line1)

		// Read next pair
		scanner.Scan()
		line2 := strings.TrimSpace(scanner.Text())
		pair2 := parsePair(line2)

		// Read final pair
		scanner.Scan()
		line3 := strings.TrimSpace(scanner.Text())
		final := parsePair(line3)
		final.x += extra
		final.y += extra

		// Add to result
		machine := Machine{
			A:     pair1,
			B:     pair2,
			Prize: final,
		}

		tokens := tokensNeeded2(machine)
		fmt.Println(tokens)

		sum += tokens

	}

	return sum
}

func tokensNeeded2(m Machine) int {

	right := m.Prize.x*m.B.y - m.Prize.y*m.B.x
	left := m.A.x*m.B.y - m.B.x*m.A.y

	if right%left == 0 {
		a := right / left
		if (m.Prize.x-m.A.x*a)%m.B.x == 0 {
			b := (m.Prize.x - m.A.x*a) / m.B.x
			return a*3 + b
		}
	}

	return 0
}

// let [x1, y1, x2, y2, mut n1, mut n2] = [nums[0], nums[1], nums[2], nums[3], nums[4], nums[5]];
// if p2 {
//     n1 += 10_000_000_000_000;
//     n2 += 10_000_000_000_000;
// }
// // x1*a + x2*b == n1
// // y1*a + y2*b == n2
// // x1*y2*a + x2*y2*b == n1*y2
// // x2*y1*a + x2*y2*b == n2*x2
// // (x1*y2 - x2*y1) *a == n1*y2 - n2*x2
// let right = n1 * y2 - n2 * x2;
// let left = x1 * y2 - x2 * y1;
// if right % left == 0 {
//     let a = right / left;
//     if (n1 - x1 * a) % x2 == 0 {
//         let b = (n1 - x1 * a) / x2;
//         if p2 || (0..=100).contains(&a) && (0..=100).contains(&b) {
//             return Some([a, b]);
//         }
//     }
// }
// None
