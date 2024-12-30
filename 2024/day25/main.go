package main

import (
	"bufio"
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

	scan := bufio.NewScanner(strings.NewReader(input))

	locks := make([][5]int, 0)
	keys := make([][5]int, 0)

	for scan.Scan() {
		lock := true
		if scan.Text()[0] == '.' {
			lock = false
		}
		p := [5]int{}
		for i := 0; scan.Scan(); i++ {
			t := scan.Text()
			fmt.Println(t)
			t = strings.TrimRight(t, "\r\n")
			if t == "" {
				break
			}
			for j, a := range t {
				if lock {
					if a == '.' {
						p[j] = max(5-i, p[j])
					}
				} else {
					if a == '#' {
						p[j] = max(5-i, p[j])
					}
				}

			}
		}
		if lock {
			locks = append(locks, p)
		} else {
			keys = append(keys, p)
		}

	}
	for i, l := range locks {
		for j := range l {
			locks[i][j] = 5 - l[j]
		}
	}
	fmt.Println(locks)
	fmt.Println(keys)

	count := 0

	for _, l := range locks {
		for _, k := range keys {
			overlaps := false
			fmt.Print(l, k)
			for n := 0; n < 5; n++ {
				if l[n]+k[n] > 5 {
					overlaps = true
					fmt.Printf("Overlap at: %d\n", n)
					break
				}
			}
			if !overlaps {
				count++
				fmt.Printf("fits\n")
			}

		}
	}

	return count
}

func part2(input string) int {
	return 0
}
