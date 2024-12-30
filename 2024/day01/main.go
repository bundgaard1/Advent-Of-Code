package main

// The template is gotten from https://github.com/alexchao26

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

func part1(input string) int {
	var A, B []int

	for _, line := range strings.Split(input, "\r\n") {
		nums := strings.Split(line, "   ")
		A = append(A, utils.ToInt(nums[0]))
		B = append(B, utils.ToInt(nums[1]))
	}

	sort.Slice(A, func(i, j int) bool {
		return A[i] < A[j]
	})

	sort.Slice(B, func(i, j int) bool {
		return B[i] < B[j]
	})

	sum := 0

	for i := 0; i < len(A); i++ {
		a := A[i] - B[i]
		a = max(a, -a)
		sum += a
	}

	return sum
}

func part2(input string) int {
	var A, B []int

	for _, line := range strings.Split(input, "\r\n") {
		nums := strings.Split(line, "   ")
		A = append(A, utils.ToInt(nums[0]))
		B = append(B, utils.ToInt(nums[1]))
	}

	sort.Slice(A, func(i, j int) bool {
		return A[i] < A[j]
	})

	sort.Slice(B, func(i, j int) bool {
		return B[i] < B[j]
	})

	sum := 0

	for i := 0; i < len(A); i++ {
		a := A[i]
		count := 0
		for j := 0; j < len(B); j++ {
			if a == B[j] {
				count++
			}
		}
		sum += count * a
	}

	return sum

}
