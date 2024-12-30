package main

import (
	_ "embed"
	"flag"
	"fmt"
	"regexp"
	"strings"
	"time"
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

	a := strings.SplitN(input, "\n", 2)
	patterns := strings.Split(a[0], ", ")
	pattern := "^("
	for _, p := range patterns {
		p = strings.TrimRight(p, "\r")

		fmt.Println("\"" + p + "\"")
		pattern += p + "|"
	}
	pattern = strings.TrimRight(pattern, "|")
	pattern += ")+$"

	fmt.Println(pattern)

	rg, err := regexp.Compile(pattern)
	if err != nil {
		panic(err)
	}

	total := 0

	for _, d := range strings.Split(a[1], "\n") {
		d = strings.TrimRight(d, "\r")
		res := rg.MatchString(d)
		if res {
			total++
		}
		fmt.Println(d, rg.MatchString(d))
	}

	return total
}

func part2(input string) int {

	start := time.Now()

	a := strings.SplitN(input, "\n", 2)
	patterns := strings.Split(a[0], ", ")
	patterns[len(patterns)-1] = strings.TrimRight(patterns[len(patterns)-1], "\r")

	total := 0

	for _, d := range strings.Split(a[1], "\n") {
		d = strings.TrimRight(d, "\r")
		dp := make(map[string]int)
		res := CountMatches(d, patterns, dp)
		// fmt.Println(d, res)
		total += res
	}

	fmt.Println("total runtime:", time.Now().Sub(start))

	return total

}

func CountMatches(input string, patterns []string, dp map[string]int) int {
	if len(input) == 0 {
		return 1
	}
	if value, exists := dp[input]; exists {
		return value
	}

	count := 0

	for _, pattern := range patterns {
		if len(input) >= len(pattern) && input[:len(pattern)] == pattern {
			count += CountMatches(input[len(pattern):], patterns, dp)
		}
	}

	dp[input] = count

	return count
}
