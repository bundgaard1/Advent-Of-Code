package main

import (
	"aoc24/utils"
	_ "embed"
	"flag"
	"fmt"
	"math"
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
	sum := 0
	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		fmt.Println(line)
		ws := ways(line, 'A')
		fmt.Println(ws)

		shortest := math.MaxInt64
		for _, w := range ws {
			for i := 0; i < 2; i++ {
				w = dirToDir(w)
				// fmt.Println(len(w), w)
			}
			if len(w) < shortest {
				shortest = len(w)

			}
		}

		num := utils.ToInt(line[:3])
		fmt.Println(shortest, "*", num)
		sum += shortest * num
	}
	return sum
}

func ways(nums string, from rune) []string {
	if nums == "" {
		return []string{""}
	}
	curr := numpad[from]
	to := rune(nums[0])
	target := numpad[to]
	diff := Pos{target.x - curr.x, target.y - curr.y}
	rest := ways(nums[1:], to)

	newIns := []string{}
	if curr.x == 0 && target.y == 3 {
		newIns = append(newIns, addHoriz(diff.x)+addVert(diff.y)+"A")
	} else if curr.y == 3 && target.x == 0 {
		newIns = append(newIns, addVert(diff.y)+addHoriz(diff.x)+"A")
	} else if diff.x == 0 || diff.y == 0 {
		newIns = append(newIns, addHoriz(diff.x)+addVert(diff.y)+"A")
	} else {
		newIns = append(newIns, addHoriz(diff.x)+addVert(diff.y)+"A")
		newIns = append(newIns, addVert(diff.y)+addHoriz(diff.x)+"A")
	}
	instructions := []string{}

	for _, new := range newIns {
		for _, r := range rest {
			instructions = append(instructions, new+r)
		}
	}

	return instructions
}

type Pos struct {
	x, y int
}

var numpad map[rune]Pos = map[rune]Pos{
	'7': Pos{0, 0},
	'8': Pos{1, 0},
	'9': Pos{2, 0},
	'4': Pos{0, 1},
	'5': Pos{1, 1},
	'6': Pos{2, 1},
	'1': Pos{0, 2},
	'2': Pos{1, 2},
	'3': Pos{2, 2},
	'0': Pos{1, 3},
	'A': Pos{2, 3},
}

var dirpad map[rune]Pos = map[rune]Pos{
	'^': Pos{1, 0},
	'A': Pos{2, 0},
	'<': Pos{0, 1},
	'v': Pos{1, 1},
	'>': Pos{2, 1},
}

type ButtonPair struct {
	from, to rune
}

var paths = map[ButtonPair]string{
	{'A', '>'}: "vA",
	{'A', '^'}: "<A",
	{'A', 'v'}: "<vA",
	{'A', '<'}: "v<<A",
	{'A', 'A'}: "A",
	{'>', '>'}: "A",
	{'>', '^'}: "<^A",
	{'>', 'v'}: "<A",
	{'>', '<'}: "<<A",
	{'>', 'A'}: "^A",
	{'<', '>'}: ">>A",
	{'<', '^'}: ">^A",
	{'<', 'v'}: ">A",
	{'<', '<'}: "A",
	{'<', 'A'}: ">>^A",
	{'^', '>'}: "v>A",
	{'^', '^'}: "A",
	{'^', 'v'}: "vA",
	{'^', '<'}: "v<A",
	{'^', 'A'}: ">A",
	{'v', '>'}: ">A",
	{'v', '^'}: "^A",
	{'v', 'v'}: "A",
	{'v', '<'}: "<A",
	{'v', 'A'}: "^>A",
}

func dirToDir(dirs string) string {
	from := 'A'
	ins := ""

	for _, a := range dirs {
		to := a
		ins += paths[ButtonPair{from, to}]
		from = to
	}

	return ins
}

func addHoriz(n int) string {
	if n > 0 {
		return strings.Repeat(">", n)
	} else {
		return strings.Repeat("<", -n)
	}
}

func addVert(n int) string {
	if n > 0 {
		return strings.Repeat("v", n)
	} else {
		return strings.Repeat("^", -n)
	}
}

func part2(input string) (sum int) {

	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		startWays := ways(line, 'A')
		fmt.Println("--", line, "--")
		shortest := math.MaxInt64

		for _, w := range startWays {

			sc := SeqToSeqCount(w)

			// fmt.Println(w, "\n", sc.length(), sc)
			for i := 0; i < 25; i++ {
				sc = nextSeq(sc)
				// fmt.Println(sc.length(), sc)
			}

			fmt.Println(sc.length())
			if sc.length() < shortest {
				shortest = sc.length()
			}
		}

		num := utils.ToInt(line[:3])
		fmt.Println(shortest, "*", num, "=", shortest*num)
		sum += shortest * num
	}
	return
}

type SeqCounter map[string]int

func nextSeq(in SeqCounter) (out SeqCounter) {
	out = make(SeqCounter)
	for key, val := range in {
		dirs := dirToDir(key)

		for _, seg := range strings.SplitAfter(dirs, "A") {
			if seg == "" {
				continue
			}
			out[seg] += val
		}

	}

	return
}

func SeqToSeqCount(in string) (out SeqCounter) {
	out = make(SeqCounter)
	for _, seg := range strings.SplitAfter(in, "A") {
		if seg == "" {
			continue
		}
		out[seg] += 1
	}

	return
}

func (sc *SeqCounter) length() (n int) {
	for key, val := range *sc {
		n += val * len(key)
	}
	return
}
