package main

import (
	"aoc24/utils"
	_ "embed"
	"flag"
	"fmt"
	"os"
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

	wires := make(map[string]int)

	readingGates := false
	gates := make([]string, 0)

	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		if line == "" {
			readingGates = true
			continue
		}

		if readingGates {
			gates = append(gates, line)
		} else {
			f := strings.Split(line, ": ")
			wires[f[0]] = utils.ToInt(f[1])
		}
	}

	used := []int{}
	for len(used) < len(gates) {
		for i, s := range gates {
			if slices.Contains(used, i) {
				continue
			}

			f := strings.Fields(s)
			a, aExists := wires[f[0]]
			b, bExists := wires[f[2]]

			if !aExists || !bExists {
				continue
			}
			c := 0
			switch f[1] {
			case "AND":
				c = a & b
			case "OR":
				c = a | b
			case "XOR":
				c = a ^ b
			default:
				panic("Unexpected operations")
			}

			wires[f[4]] = c
			used = append(used, i)

		}
	}
	z := 0

	for k, v := range wires {
		if k[0] == 'z' {
			n := utils.ToInt(k[1:])
			z |= v << n
		}
	}

	return z
}

func part2(input string) int {
	wires := make(map[string]int)

	readingGates := false
	gates := make([]string, 0)

	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		if line == "" {
			readingGates = true
			continue
		}

		if readingGates {
			gates = append(gates, line)
		} else {
			f := strings.Split(line, ": ")
			wires[f[0]] = utils.ToInt(f[1])
		}
	}

	swaps := map[string]string{
		"kvn": "z18",
		"z18": "kvn",
		"z14": "hbk",
		"hbk": "z14",
		"z23": "dbb",
		"dbb": "z23",
		"cvh": "tfn",
		"tfn": "cvh",
	}

	dot := "digraph G {\n"

	counter := 0
	next := func() string {
		counter++
		return fmt.Sprintf("n%d", counter)
	}
	for _, s := range gates {
		f := strings.Fields(s)

		gate := next()

		if x, ok := swaps[f[4]]; ok {
			f[4] = x
		}

		dot += fmt.Sprintf("\t%s [label=\"%s\"];\n", gate, f[1])
		dot += fmt.Sprintf("\t%s -> %s;\n", f[0], gate)
		dot += fmt.Sprintf("\t%s -> %s;\n", f[2], gate)
		dot += fmt.Sprintf("\t%s -> %s;\n", gate, f[4])
	}
	dot += "}"

	file, err := os.Create("graph.dot")
	if err != nil {
		fmt.Println("Error creating file:", err)
	}
	defer file.Close()

	_, err = file.WriteString(dot)
	if err != nil {
		fmt.Println("Error writing to file:", err)
		return 0
	}

	used := []int{}
	for len(used) < len(gates) {
		for i, s := range gates {
			if slices.Contains(used, i) {
				continue
			}

			f := strings.Fields(s)
			a, aExists := wires[f[0]]
			b, bExists := wires[f[2]]

			if !aExists || !bExists {
				continue
			}
			c := 0
			switch f[1] {
			case "AND":
				c = a & b
			case "OR":
				c = a | b
			case "XOR":
				c = a ^ b
			default:
				panic("Unexpected operations")
			}

			if x, ok := swaps[f[4]]; ok {
				f[4] = x
			}

			wires[f[4]] = c
			used = append(used, i)

		}
	}
	x := 0
	y := 0
	z := 0
	for k, v := range wires {
		if k[0] == 'z' {
			n := utils.ToInt(k[1:])
			z |= v << n
		}
		if k[0] == 'y' {
			n := utils.ToInt(k[1:])
			y |= v << n
		}
		if k[0] == 'x' {
			n := utils.ToInt(k[1:])
			x |= v << n
		}
	}

	fmt.Printf("x: %d\ny: %d\nz: %d\n", x, y, z)
	fmt.Printf("x: %b\ny: %b\nz:   %b\n", x, y, z)
	fmt.Printf("x+y= %b\n", x+y)
	if x+y == z {
		fmt.Print("MATCH\n")
		answer := []string{}
		for k, _ := range swaps {
			answer = append(answer, k)
		}
		slices.Sort(answer)
		fmt.Println(strings.Join(answer, ","))
	} else {
		fmt.Print("NO MATCH\n")
	}

	return 0
}
