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
	sum := 0

	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		record := strings.Split(line, " ")
		if safeRecord(record) {
			sum++
		}
	}

	return sum
}

func part2(input string) int {

	sum := 0
	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		record := strings.Split(line, " ")

		if safeRecord(record) || safeByRemoval(record) {
			sum++
		}
	}

	return sum
}

func safeRecord(record []string) bool {
	fmt.Print(record, "  ")
	increasing := true
	if utils.ToInt(record[0]) > utils.ToInt(record[1]) {
		increasing = false
	}
	fmt.Print(" Increacing: ", increasing)
	safe := true
	for i := 0; i < len(record)-1; i++ {
		diff := utils.ToInt(record[i+1]) - utils.ToInt(record[i])

		if diff >= 1 && diff <= 3 && increasing || diff <= -1 && diff >= -3 && !increasing {
			continue
		} else {
			safe = false
		}
	}
	fmt.Print(" Safe: ", safe, "\n")
	return safe
}

func safeByRemoval(record []string) bool {

	for i := 0; i < len(record)-1; i++ {

		before := append([]string{}, record[0:i]...)
		after := append([]string{}, record[i+1:]...)
		fmt.Print(i, " ", before, after)
		oneRemoved := append(before, after...)
		if safeRecord(oneRemoved) {
			return true
		}
	}
	return false
}
