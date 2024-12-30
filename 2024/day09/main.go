package main

import (
	"aoc24/utils"
	_ "embed"
	"flag"
	"fmt"
	"slices"
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
	file := true
	id := 0

	var memory []int

	for _, c := range input {
		if c == '\n' || c == '\r' {
			break
		}

		blockLength := utils.ToInt(c)
		fmt.Println(blockLength, file)
		if file {
			block := slices.Repeat([]int{id}, blockLength)
			memory = append(memory, block...)
			id++
		} else {
			block := slices.Repeat([]int{-1}, blockLength)
			memory = append(memory, block...)
		}

		file = !file
	}

	for i := 0; i < len(memory); i++ {
		if memory[i] == -1 {
			N := len(memory)
			memory[i] = memory[N-1]

			memory = memory[:N-1]
			// fmt.Println(memory)

			for memory[len(memory)-1] == -1 {
				memory = memory[:len(memory)-1]
			}
		}
	}

	checksum := 0

	for i, a := range memory {
		checksum += i * a
	}

	return checksum
}

func part2(input string) int {
	file := true
	id := 0

	var memory []int

	for _, c := range input {
		if c == '\n' || c == '\r' {
			break
		}

		blockLength := utils.ToInt(c)
		if file {
			block := slices.Repeat([]int{id}, blockLength)
			memory = append(memory, block...)
			id++
		} else {
			block := slices.Repeat([]int{-1}, blockLength)
			memory = append(memory, block...)
		}

		file = !file
	}
	fmt.Println(memory)

	for i := len(memory) - 1; i > 0; i-- {
		if memory[i] != -1 {
			// fmt.Print("i:", i)
			id := memory[i]
			a := i - 1
			for a >= 0 && memory[a] == id {
				a--
			}
			// fmt.Print(" a: ", a)
			M := i - a
			// fmt.Print(" M: ", M)

			for j := 0; j < i; j++ {
				if memory[j] == -1 {
					// fmt.Print(" j: ", j)
					K := 1
					for K < len(memory) && memory[j+K] == -1 {
						K++
					}
					// fmt.Print(" K: ", K)
					if K < M {
						j = j + K
					} else {
						for n := 0; n < M; n++ {
							memory[j+n] = id
							memory[i-n] = -1
						}
						break
					}
				}
			}

			i -= M - 1

		}
		// fmt.Println("\n\n", memory)

	}

	checksum := 0

	for i, a := range memory {
		if a == -1 {
			continue
		}
		checksum += i * a
	}

	return checksum
}
