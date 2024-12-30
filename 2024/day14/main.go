package main

import (
	"aoc24/utils"
	_ "embed"
	"flag"
	"fmt"
	"image"
	_ "image"
	"image/color"
	"image/png"
	"io"
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

type Pos struct {
	x int
	y int
}

func main() {
	var part int
	flag.IntVar(&part, "part", 1, "part 1 or 2")
	flag.Parse()
	fmt.Println("Running part", part)

	if part == 1 {
		ans := part1(input, Pos{101, 103})
		fmt.Println("Output:", ans)
	} else {
		ans := part2(input, Pos{101, 103})
		fmt.Println("Output:", ans)
	}
}

func part1(input string, space Pos) int {
	endPos := []Pos{}
	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")

		fields := strings.Fields(line)
		px := utils.ToInt(fields[0])
		py := utils.ToInt(fields[1])
		vx := utils.ToInt(fields[2])
		vy := utils.ToInt(fields[3])
		end := elapseTime(100, Pos{px, py}, Pos{vx, vy}, space)
		fmt.Println(end.y, end.x)
		endPos = append(endPos, end)
	}

	for i := 0; i < space.y; i++ {
		for j := 0; j < space.x; j++ {
			if slices.Contains(endPos, Pos{j, i}) {
				fmt.Print("x")
			} else {
				fmt.Print(".")
			}
		}
		fmt.Println()
	}

	// [0,1]
	// [2,3]
	quadrants := []int{0, 0, 0, 0}

	for _, p := range endPos {
		mx := space.x / 2
		my := space.y / 2
		if p.x < mx && p.y < my {
			quadrants[0]++
		}
		if p.x > mx && p.y < my {
			quadrants[1]++
		}
		if p.x < mx && p.y > my {
			quadrants[2]++
		}
		if p.x > mx && p.y > my {
			quadrants[3]++
		}
	}

	fmt.Println(quadrants)
	q := quadrants
	safety := q[0] * q[1] * q[2] * q[3]

	return safety
}

func elapseTime(seconds int, start Pos, vel Pos, space Pos) Pos {

	end := Pos{
		x: (start.x + vel.x*seconds) % space.x,
		y: (start.y + vel.y*seconds) % space.y,
	}

	if end.x < 0 {
		end.x = end.x + space.x
	}
	if end.y < 0 {
		end.y = end.y + space.y
	}

	return end
}

func part2(input string, space Pos) int {

	pos := []Pos{}
	vel := []Pos{}

	for _, line := range strings.Split(input, "\n") {
		line = strings.TrimRight(line, "\r")

		fields := strings.Fields(line)
		px := utils.ToInt(fields[0])
		py := utils.ToInt(fields[1])
		vx := utils.ToInt(fields[2])
		vy := utils.ToInt(fields[3])
		pos = append(pos, Pos{px, py})
		vel = append(vel, Pos{vx, vy})

	}
	for i := 2000; i < 10000; i++ {
		endPos := []Pos{}
		for j := 0; j < len(pos); j++ {
			p := pos[j]
			v := vel[j]
			end := elapseTime(i, p, v, space)
			endPos = append(endPos, end)

		}
		r := image.Rect(0, 0, space.x, space.y)

		im := image.NewGray(r)

		for i := 0; i < space.y; i++ {
			for j := 0; j < space.x; j++ {
				if slices.Contains(endPos, Pos{j, i}) {
					im.SetGray(j, i, color.Gray{Y: 255})
				} else {
					im.SetGray(j, i, color.Gray{Y: 0})
				}
			}
		}
		fileName := fmt.Sprintf("frames/frame%d.png", i)
		file, err := os.Create(fileName)
		if err != nil {
			panic(err)
		}
		defer file.Close()

		var writer io.Writer = file
		err = png.Encode(writer, im)
		if err != nil {
			panic(err)
		}
		fmt.Println("Success on ", i)

	}

	return 0
}
