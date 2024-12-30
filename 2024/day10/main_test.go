package main

import (
	"testing"
)

var example = `89010123
78121874
87430965
96549874
45678903
32019012
01329801
10456732`

var sample1 = `...0...
...1...
...2...
6543456
7.....7
8.....8
9.....9`

func Test_part1(t *testing.T) {
	tests := []struct {
		name  string
		input string
		want  int
	}{{
		name:  "bro",
		input: example,
		want:  36,
	}, {
		name:  "ex1",
		input: sample1,
		want:  2,
	}}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := part1(tt.input); got != tt.want {
				t.Errorf("part1() = %v, want %v", got, tt.want)
			}
		})
	}
}

var sample2 = `.....0.
..4321.
..5..2.
..6543.
..7..4.
..8765.
..9....`

func Test_part2(t *testing.T) {
	tests := []struct {
		name  string
		input string
		want  int
	}{{
		name:  "bro",
		input: example,
		want:  81,
	}, {
		name:  "ex1",
		input: sample2,
		want:  3,
	}}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := part2(tt.input); got != tt.want {
				t.Errorf("part2() = %v, want %v", got, tt.want)
			}
		})
	}
}
