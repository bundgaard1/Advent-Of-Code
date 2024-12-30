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
	a := 123
	for i := 0; i < 10; i++ {
		a = SecretSteps(a, 1)
		fmt.Println(a)
	}
	sum := 0
	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")

		s := utils.ToInt(line)

		t := SecretSteps(s, 2000)
		fmt.Println(s, ":", t)
		sum += t
	}

	return sum
}

func SecretSteps(s int, n int) int {
	if n == 0 {
		return s
	}
	m := s * 64
	s = s ^ m
	s = s % 16777216
	d := s / 32
	s = s ^ d
	s = s % 16777216
	h := s * 2048
	s = s ^ h
	s = s % 16777216
	return SecretSteps(s, n-1)
}

type ChangeSequence [4]int

func part2(input string) int {

	seqCounter := make(map[ChangeSequence]int)

	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		s := utils.ToInt(line)

		cng := [4]int{-10, -10, -10, -10}
		alreadyReached := make(map[ChangeSequence]bool)

		for i := 0; i < 2000; i++ {

			n := nextSecret(s)
			p := n % 10
			d := p - (s % 10)

			cng[0] = cng[1]
			cng[1] = cng[2]
			cng[2] = cng[3]
			cng[3] = d
			// fmt.Println(s, p, d, cng)

			if _, exists := alreadyReached[cng]; !exists {
				seqCounter[cng] += p
				alreadyReached[cng] = true
			}

			s = n
		}
	}
	res := 0
	for _, val := range seqCounter {

		if val > res {
			res = val
			// fmt.Println(key, val)
		}

	}

	return res
}

func nextSecret(s int) int {
	m := s * 64
	s = s ^ m
	s = s % 16777216
	d := s / 32
	s = s ^ d
	s = s % 16777216
	h := s * 2048
	s = s ^ h
	s = s % 16777216
	return s
}
