package main

import (
	"aoc24/utils"
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
		ans := part1(input, 25)
		fmt.Println("Output:", ans)
	} else {
		ans := part2(input, 75)
		fmt.Println("Output:", ans)
	}
}

func part1(input string, blinks int) int {

	stones := []int{}

	for _, stone := range strings.Split(input, " ") {
		stones = append(stones, utils.ToInt(stone))
	}

	for i := 0; i < blinks; i++ {
		stones = blink(stones)

	}

	return len(stones)
}

func blink(stones []int) []int {
	after := []int{}

	for _, stone := range stones {
		if stone == 0 {
			after = append(after, 1)
		} else if evenDigits(stone) {
			a, b := splitDigits(stone)
			after = append(after, a, b)
		} else {
			after = append(after, 2024*stone)
		}
	}
	return after
}

func part2(input string, blinks int) int {

	stones := []int{}

	dp = make(map[entryKey]int)

	for _, stone := range strings.Split(input, " ") {
		stones = append(stones, utils.ToInt(stone))
	}

	sum := 0
	for _, stone := range stones {
		sum += blink2(stone, blinks)
	}

	return sum
}

func evenDigits(a int) bool {
	for a > 99 {
		a /= 100
	}
	if a < 10 {
		return false
	}
	return true
}

func splitDigits(a int) (int, int) {
	a_str := fmt.Sprintf("%d", a)
	l := len(a_str)
	return utils.ToInt(a_str[0 : l/2]), utils.ToInt(a_str[l/2:])
}

type entryKey struct {
	stone            int
	blinks_remaining int
}

var dp map[entryKey]int

func blink2(stone, remaining int) int {
	if remaining == 0 {
		return 1
	}

	if dp[entryKey{stone, remaining}] != 0 {
		return dp[entryKey{stone, remaining}]
	}

	res := 0
	if stone == 0 {
		res = blink2(1, remaining-1)
	} else if evenDigits(stone) {
		a, b := splitDigits(stone)
		res = blink2(a, remaining-1) + blink2(b, remaining-1)
	} else {
		res = blink2(2024*stone, remaining-1)
	}

	dp[entryKey{stone, remaining}] = res
	return res
}
