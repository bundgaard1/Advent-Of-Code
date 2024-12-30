package main

import (
	_ "embed"
	"flag"
	"fmt"
	"strings"

	"slices"
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

	graph := make(map[string][]string)

	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		fields := strings.Split(line, "-")
		fromV := graph[fields[0]]
		graph[fields[0]] = append(fromV, fields[1])
		toV := graph[fields[1]]
		graph[fields[1]] = append(toV, fields[0])
	}

	inter := make([][3]string, 0)
	for k, _ := range graph {
		// fmt.Println(k, v)
		ps := cycles(graph, k, k, 3)

		for _, p := range ps {
			// fmt.Println(p)
			p = p[1:]
			slices.Sort(p)
			p := [3]string{p[0], p[1], p[2]}
			if !slices.Contains(inter, p) {
				inter = append(inter, p)
			}
		}
	}
	containsT := 0
	for i, a := range inter {
		fmt.Println(i, a)
		for _, v := range a {
			if v[0] == 't' {
				containsT++
				break
			}
		}
	}

	return containsT
}

func cycles(g map[string][]string, curr, start string, rem int) [][]string {
	if rem == 0 {
		if curr == start {
			return [][]string{[]string{curr}}
		} else {
			return [][]string{}
		}
	}

	v := g[curr]

	paths := [][]string{}

	for _, n := range v {
		ps := cycles(g, n, start, rem-1)
		for _, p := range ps {
			paths = append(paths, append([]string{curr}, p...))
		}

	}

	return paths
}

type Graph map[string][]string

func part2(input string) int {

	graph := make(map[string][]string)

	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		fields := strings.Split(line, "-")
		fromV := graph[fields[0]]
		graph[fields[0]] = append(fromV, fields[1])
		toV := graph[fields[1]]
		graph[fields[1]] = append(toV, fields[0])
	}

	vertecies := []string{}

	for k, _ := range graph {
		vertecies = append(vertecies, k)
	}

	BronKerbosch(graph, []string{}, vertecies, []string{})

	return 0
}

var Max = 0

func BronKerbosch(G Graph, R, P, X []string) {
	if len(P) == 0 && len(X) == 0 {
		if len(R) > Max {
			fmt.Println(len(R), R)
			Max = len(R)
			slices.Sort(R)
			fmt.Println(strings.Join(R, ","))
		}
	}
	for len(P) > 0 {
		v := P[0]
		r := union(R, []string{v})
		p := intersect(P, G[v])
		x := intersect(P, G[v])
		BronKerbosch(G, r, p, x)
		P = P[1:]
		X = union(X, []string{v})
	}
}

func union(A, B []string) []string {
	for _, b := range B {
		if !slices.Contains(A, b) {
			A = append(A, b)
		}
	}

	return A
}

func intersect(A, B []string) []string {
	C := []string{}
	for _, a := range A {
		if slices.Contains(B, a) {
			C = append(C, a)
		}
	}
	return C
}
