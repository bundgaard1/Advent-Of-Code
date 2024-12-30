package main

import (
	"aoc24/utils"
	_ "embed"
	"flag"
	"fmt"
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

var rules map[int][]int

func is_rule(x, y int) bool {
	after := rules[x]
	for _, a := range after {
		if y == a {
			return true
		}
	}
	return false
}

func part1(input string) int {
	rules = make(map[int][]int)
	updates := false
	sum := 0

	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		if line == "" {
			updates = true
			continue
		}
		if updates {
			fmt.Println(line)
			updatesStr := strings.Split(line, ",")
			updates := utils.StringsToInt(updatesStr)
			valid := true
			for i := 0; i < len(updates); i++ {
				actual := updates[i]
				before := updates[:i]
				after := updates[i+1:]
				for _, b := range before {
					if !is_rule(b, actual) {
						valid = false
					}
				}
				for _, a := range after {
					if !is_rule(actual, a) {
						valid = false
					}
				}
				fmt.Println(actual, before, after, valid)
			}
			if valid {
				middle := len(updates) / 2
				fmt.Println(middle, updates[middle])
				sum += updates[middle]
			}

		} else {
			parts := strings.Split(line, "|")
			a, b := utils.ToInt(parts[0]), utils.ToInt(parts[1])
			temp := append(rules[a], b)
			rules[a] = temp
		}
	}

	return sum
}

func part2(input string) int {
	rules = make(map[int][]int)
	updates := false
	sum := 0

	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		if line == "" {
			updates = true
			continue
		}
		if updates {
			fmt.Println(line)
			updatesStr := strings.Split(line, ",")
			updates := utils.StringsToInt(updatesStr)
			valid := true
			for i := 0; i < len(updates); i++ {
				actual := updates[i]
				before := updates[:i]
				after := updates[i+1:]
				for _, b := range before {
					if !is_rule(b, actual) {
						valid = false
					}
				}
				for _, a := range after {
					if !is_rule(actual, a) {
						valid = false
					}
				}
				// fmt.Println(actual, before, after, valid)
			}
			if !valid {
				fmt.Println(updates)
				sort_updates(updates)
				fmt.Println(updates)

				middle := len(updates) / 2
				fmt.Println(middle, updates[middle])
				sum += updates[middle]
			}

		} else {
			parts := strings.Split(line, "|")
			a, b := utils.ToInt(parts[0]), utils.ToInt(parts[1])
			temp := append(rules[a], b)
			rules[a] = temp
		}
	}

	return sum
}

func sort_updates(updates []int) []int {
	sort.Slice(updates, func(i, j int) bool {
		return is_rule(updates[i], updates[j])
	})

	return updates
}
