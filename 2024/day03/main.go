package main

// The template is gotten from https://github.com/alexchao26

import (
	"aoc24/utils"
	_ "embed"
	"flag"
	"fmt"
	"slices"
	"strings"
	"unicode"
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
		parts := strings.Split(line, "mul")
		for i, part := range parts {
			fmt.Println(i, ": ", part)
			result, err := parse_mul(part)
			if err != nil {
				fmt.Println(err)
			}
			sum += result
			fmt.Println(result)
		}
	}
	return sum
}

func parse_mul(afterMul string) (int, error) {
	if !strings.HasPrefix(afterMul, "(") {
		return 0, fmt.Errorf("ERROR: no ( prefix")
	}
	afterMul = afterMul[1:]
	sorted := strings.SplitAfterN(afterMul, ")", 2)
	if len(sorted) != 2 {
		return 0, fmt.Errorf("ERROR: no ) in string")
	}
	numberWithComma := sorted[0]

	numberWithComma, _ = strings.CutSuffix(numberWithComma, ")")
	numbers := strings.Split(numberWithComma, ",")
	if len(numbers) != 2 {
		return 0, fmt.Errorf("ERROR: not 2 numbers given between")
	}
	a, _ := validNumber(numbers[0])
	b, _ := validNumber(numbers[1])

	result := a * b
	return result, nil
}

func validNumber(numStr string) (int, error) {
	if !slices.Contains([]int{1, 2, 3}, len(numStr)) {
		return 0, fmt.Errorf("number not the correct length")
	}
	if !isNumeric(numStr) {
		return 0, fmt.Errorf("string is not completly numeric")
	}
	num := utils.ToInt(numStr)

	return num, nil
}

func isNumeric(s string) bool {
	if s == "" { // Optional: handle empty string as not numeric
		return false
	}
	for _, r := range s {
		if !unicode.IsDigit(r) {
			return false
		}
	}
	return true
}

func part2(input string) int {

	sum := 0

	for _, line := range strings.Split(input, "\n") {
		dos := strings.Split(line, "do()")
		for _, do := range dos {
			only_do, dont, _ := strings.Cut(do, "don't()")
			fmt.Println("Do:", only_do)
			fmt.Println("Dont:", dont)
			sum += part1(only_do)
		}
	}

	return sum
}
