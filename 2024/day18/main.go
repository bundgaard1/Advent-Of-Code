package main

import (
	"aoc24/utils"
	"container/heap"
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
		ans := part1(input, 70, 1024)
		fmt.Println("Output:", ans)
	} else {
		ans := part2(input, 70)
		fmt.Println("Output:", ans)
	}
}

var (
	EMPTY  = uint8(0)
	FALLEN = uint8(1)
	EXIT   = uint8(2)
)

type Pos struct {
	x, y int
}

type Dir struct {
	dx, dy int
}

var dirs []Dir = []Dir{
	{1, 0},
	{0, 1},
	{-1, 0},
	{0, -1},
}

type Item struct {
	value    Pos
	priority int // The priority of the item in the queue.
	// The index is needed by update and is maintained by the heap.Interface methods.
	index int // The index of the item in the heap.
}

type PriorityQueue []*Item

func (pq PriorityQueue) Len() int { return len(pq) }
func (pq PriorityQueue) Less(i, j int) bool {
	return pq[i].priority < pq[j].priority
}

func (pq PriorityQueue) Swap(i, j int) {
	pq[i], pq[j] = pq[j], pq[i]
	pq[i].index = i
	pq[j].index = j
}

func (pq *PriorityQueue) Push(x any) {
	n := len(*pq)
	item := x.(*Item)
	item.index = n
	*pq = append(*pq, item)
}

func (pq *PriorityQueue) Pop() any {
	old := *pq
	n := len(old)
	item := old[n-1]
	old[n-1] = nil  // don't stop the GC from reclaiming the item eventually
	item.index = -1 // for safety
	*pq = old[0 : n-1]
	return item
}

func part1(input string, r int, bytes int) int {

	space := make([][]uint8, r+1)

	for i := range space {
		space[i] = make([]uint8, r+1)
	}

	for i, line := range strings.Split(input, "\n") {
		if i >= bytes {
			break
		}
		line = strings.TrimRight(line, "\r")
		f := strings.Split(line, ",")
		x := utils.ToInt(f[0])
		y := utils.ToInt(f[1])
		space[y][x] = FALLEN
	}

	space[r][r] = EXIT

	for i := range space {
		fmt.Println(space[i])
	}

	// Heuristic
	h := func(p Pos) int {
		return r - p.x + r - p.y
	}
	//
	invalid := func(p Pos) bool {
		return (p.y < 0 || p.y >= len(space) || p.x < 0 || p.x >= len(space[p.y])) ||
			space[p.y][p.x] == FALLEN
	}

	pq := make(PriorityQueue, 0)
	heap.Init(&pq)

	startP := Pos{x: 0, y: 0}
	start := &Item{
		value:    startP,
		priority: 0,
	}
	heap.Push(&pq, start)

	cameFrom := make(map[Pos]Pos)
	gScore := make(map[Pos]int)
	gScore[startP] = 0

	fScore := make(map[Pos]int)
	fScore[startP] = h(startP)

	res := 0

	for pq.Len() > 0 {
		c := heap.Pop(&pq).(*Item)
		if space[c.value.x][c.value.y] == EXIT {
			fmt.Println("FOUND PATH")
			res = c.priority
			break
		}
		// fmt.Println(c.value, c.priority)

		for _, d := range dirs {
			tentG := gScore[c.value] + 1
			n := Pos{x: c.value.x + d.dx, y: c.value.y + d.dy}
			if invalid(n) {
				continue
			}
			if value, exists := gScore[n]; !exists || tentG < value {
				cameFrom[n] = c.value
				gScore[n] = tentG
				f := tentG + h(n)
				fScore[n] = f
				newN := &Item{
					value:    n,
					priority: f,
				}
				heap.Push(&pq, newN)
			}
		}
	}

	return res
}

func part2(input string, r int) int {

	space := make([][]uint8, r+1)

	for i := range space {
		space[i] = make([]uint8, r+1)
	}

	falls := []Pos{}

	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")
		f := strings.Split(line, ",")
		x := utils.ToInt(f[0])
		y := utils.ToInt(f[1])
		falls = append(falls, Pos{x, y})
	}

	space[r][r] = EXIT

	// for i := range space {
	// 	fmt.Println(space[i])
	// }

	// Heuristic
	h := func(p Pos) int {
		return r - p.x + r - p.y
	}
	//
	invalid := func(p Pos) bool {
		return (p.y < 0 || p.y >= len(space) || p.x < 0 || p.x >= len(space[p.y])) ||
			space[p.y][p.x] == FALLEN
	}

	res := Pos{0, 0}
	for i := range falls {
		f := falls[i]

		space[f.y][f.x] = FALLEN

		found := false

		pq := make(PriorityQueue, 0)
		heap.Init(&pq)

		startP := Pos{x: 0, y: 0}
		start := &Item{
			value:    startP,
			priority: 0,
		}
		heap.Push(&pq, start)

		cameFrom := make(map[Pos]Pos)
		gScore := make(map[Pos]int)
		gScore[startP] = 0

		fScore := make(map[Pos]int)
		fScore[startP] = h(startP)

		for pq.Len() > 0 {
			c := heap.Pop(&pq).(*Item)
			if space[c.value.x][c.value.y] == EXIT {
				fmt.Println("FOUND PATH: ", i)
				found = true
				break
			}
			// fmt.Println(c.value, c.priority)

			for _, d := range dirs {
				tentG := gScore[c.value] + 1
				n := Pos{x: c.value.x + d.dx, y: c.value.y + d.dy}
				if invalid(n) {
					continue
				}
				if value, exists := gScore[n]; !exists || tentG < value {
					cameFrom[n] = c.value
					gScore[n] = tentG
					f := tentG + h(n)
					fScore[n] = f
					newN := &Item{
						value:    n,
						priority: f,
					}
					heap.Push(&pq, newN)
				}
			}
		}

		if found {
			continue
		} else {
			res = f
			break
		}
	}

	fmt.Println("Final block: ", res)

	return 0
}
