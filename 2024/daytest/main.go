package main

// The template is gotten from https://github.com/alexchao26

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
		ans := part1(input)
		fmt.Println("Output:", ans)
	} else {
		ans := part2(input)
		fmt.Println("Output:", ans)
	}
}

func part1(input string) int {
	var sum int

	for _, line := range strings.Split(input, "\r\n") {
		mass := utils.ToInt(line)
		fuel := (mass / 3) - 2
		sum += fuel
	}

	return sum
}

func part2(input string) int {
	var sum int

	for _, line := range strings.Split(input, "\r\n") {
		mass := utils.ToInt(line)
		for mass > 0 {
			fuel := (mass / 3) - 2
			fuel = max(fuel, 0)
			mass = fuel
			sum += fuel
		}
	}

	return sum
}
