package main

import (
	"testing"
)

var example = `0 4 3 -3
6 3 -1 -3
10 3 -1 2
2 0 2 -1
0 0 1 3
3 0 -2 -2
7 6 -1 -3
3 0 -1 -2
9 3 2 3
7 3 -1 2
2 4 2 -3
9 5 -3 -3`

func Test_part1(t *testing.T) {
	tests := []struct {
		name  string
		input string
		want  int
		space Pos
	}{{
		name:  "example",
		input: example,
		want:  12,
		space: Pos{x: 11, y: 7},
	}}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := part1(tt.input, tt.space); got != tt.want {
				t.Errorf("part1() = %v, want %v", got, tt.want)
			}
		})
	}
}

func Test_part2(t *testing.T) {
	tests := []struct {
		name  string
		input string
		want  int
		space Pos
	}{}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := part2(tt.input, tt.space); got != tt.want {
				t.Errorf("part2() = %v, want %v", got, tt.want)
			}
		})
	}
}
