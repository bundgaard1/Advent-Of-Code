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

type Computer struct {
	A       int
	B       int
	C       int
	IP      int
	Program []int
	Output  string
}

func part1(input string) int {

	fields := strings.Split(input, "\n")
	aReg := utils.ToInt(strings.TrimRight(fields[0], "\r"))
	bReg := utils.ToInt(strings.TrimRight(fields[1], "\r"))
	cReg := utils.ToInt(strings.TrimRight(fields[2], "\r"))

	p := []int{}
	for _, op := range strings.Split(fields[3], ",") {
		p = append(p, utils.ToInt(op))
	}

	c := Computer{
		A:       aReg,
		B:       bReg,
		C:       cReg,
		IP:      0,
		Program: p,
		Output:  "",
	}

	combo := func(o int) int {
		switch o {
		case 0, 1, 2, 3:
			return o
		case 4:
			return c.A
		case 5:
			return c.B
		case 6:
			return c.C
		default:
			panic("Invalid combo operand: ")
		}
	}

	for {
		if c.IP >= len(c.Program) {
			break
		}

		opcode := c.Program[c.IP]
		op := c.Program[c.IP+1]

		switch opcode {
		case 0: //adv
			c.A = c.A >> combo(op)
		case 1: // bxl
			c.B = c.B ^ op
		case 2: // bst
			c.B = combo(op) % 8
		case 3: // jnz
			if c.A != 0 {
				c.IP = op
				continue
			}
		case 4: // bxc
			c.B = c.B ^ c.C
		case 5: // out
			c.Output = fmt.Sprintf("%s,%d", c.Output, combo(op)%8)
		case 6: // bdv
			c.B = c.A >> combo(op)
		case 7: // cdv
			c.C = c.A >> combo(op)
		default:
			panic("invalud opcode")
		}

		c.IP += 2
	}
	out := c.Output
	fmt.Println(out)
	return 0
}

func part2(input string) int {
	fields := strings.Split(input, "\n")
	p := []int{}
	pStr := fields[3]
	for _, op := range strings.Split(pStr, ",") {
		p = append(p, utils.ToInt(op))
	}

	out := 0

	third := len(pStr) / 3

	factor := len(p)

	for i := 0; i < (1 << factor); i++ {
		res := run2(i<<(factor*2), p)
		// fmt.Println(pStr)
		// fmt.Println(res)
		if len(res) != len(pStr) {
			continue
		}

		if strings.EqualFold(pStr[len(pStr)-third:], res[len(res)-third:]) {
			fmt.Print("First part done")

			for j := 0; j < (1 << factor); j++ {
				res := run2(i<<(factor*2)+j<<factor, p)
				// fmt.Println("  ", pStr)
				// fmt.Println("  ", res)

				if strings.EqualFold(pStr[len(pStr)-third*2:], res[len(res)-third*2:]) {
					fmt.Print("Second part done")
					for k := 0; k < (1 << factor); k++ {
						res := run2(i<<(factor*2)+j<<factor+k, p)
						// fmt.Println("    ", pStr)
						// fmt.Println("    ", res)

						if strings.EqualFold(pStr, res) {
							fmt.Println("FOUND COMPLETE MATCH")
							fmt.Println(i)
							out = i<<(factor*2) + j<<factor + k
							goto P
						}

					}
				}

			}
		}
	}
P:

	return out
}

func run2(a int, p []int) string {
	// fmt.Printf("A: %d \n", a)

	c := Computer{
		A:       a,
		B:       0,
		C:       0,
		IP:      0,
		Program: p,
		Output:  "",
	}

	combo := func(o int) int {
		switch o {
		case 0, 1, 2, 3:
			return o
		case 4:
			return c.A
		case 5:
			return c.B
		case 6:
			return c.C
		default:
			panic("Invalid combo operand: ")
		}
	}

	for {
		if c.IP >= len(c.Program) {
			break
		}

		opcode := c.Program[c.IP]
		op := c.Program[c.IP+1]

		switch opcode {
		case 0: //adv
			c.A = c.A >> combo(op)
		case 1: // bxl
			c.B = c.B ^ op
		case 2: // bst
			c.B = combo(op) % 8
		case 3: // jnz
			if c.A != 0 {
				c.IP = op
				continue
			}
		case 4: // bxc
			c.B = c.B ^ c.C
		case 5: // out
			a := combo(op) % 8
			c.Output = fmt.Sprintf("%s,%d", c.Output, a)

		case 6: // bdv
			c.B = c.A >> combo(op)
		case 7: // cdv
			c.C = c.A >> combo(op)
		default:
			panic("invalud opcode")
		}
		c.IP += 2
	}
	return strings.TrimLeft(c.Output, ",")
}
