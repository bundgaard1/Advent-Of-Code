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
		test_str := strings.SplitN(line, ":", 2)
		test := utils.ToInt(test_str[0])

		nums := []int{}
		nums_str := strings.Split(test_str[1], " ")
		for _, n := range nums_str {
			if n == "" {
				continue
			}
			nums = append(nums, utils.ToInt(n))
		}
		fmt.Printf("%d : %d\n", test, nums)
		if backtracking(test, nums) {
			fmt.Printf("yes\n")
			sum += test
		} else {
			fmt.Printf("no\n")
		}
	}
	return sum
}

func backtracking(target int, nums []int) bool {
	if len(nums) == 1 {
		return target == nums[0]
	}
	a := nums[0]
	b := nums[1]
	return backtracking(target, append([]int{a + b}, nums[2:]...)) ||
		backtracking(target, append([]int{a * b}, nums[2:]...))
}

func part2(input string) int {
	sum := 0
	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		test_str := strings.SplitN(line, ":", 2)
		test := utils.ToInt(test_str[0])

		nums := []int{}
		nums_str := strings.Split(test_str[1], " ")
		for _, n := range nums_str {
			if n == "" {
				continue
			}
			nums = append(nums, utils.ToInt(n))
		}
		fmt.Printf("%d : %d\n", test, nums)
		if backtracking2(test, nums) {
			fmt.Printf("yes\n")
			sum += test
		} else {
			fmt.Printf("no\n")
		}
	}
	return sum
}

func concat(a, b int) int {

	str := fmt.Sprintf("%d%d", a, b)

	// fmt.Printf("%d %d = %s \n", a, b, str)
	return utils.ToInt(str)
}

func backtracking2(target int, nums []int) bool {
	// fmt.Printf("%d: %d \n", target, nums)
	if len(nums) == 1 {
		return target == nums[0]
	}
	a := nums[0]
	b := nums[1]
	return backtracking2(target, append([]int{a + b}, nums[2:]...)) ||
		backtracking2(target, append([]int{a * b}, nums[2:]...)) ||
		backtracking2(target, append([]int{concat(a, b)}, nums[2:]...))
}
