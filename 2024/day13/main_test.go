package main

import (
	"testing"
)

var example = `94 34
22 67
8400 5400

26 66
67 21
12748 12176

17 86
84 37
7870 6450

69 23
27 71
18641 10279`

func Test_part1(t *testing.T) {
	tests := []struct {
		name  string
		input string
		want  int
	}{{
		name:  "example",
		input: example,
		want:  480,
	}}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := part1(tt.input); got != tt.want {
				t.Errorf("part1() = %v want %v", got, tt.want)
			}
		})
	}
}

func Test_part2(t *testing.T) {
	tests := []struct {
		name  string
		input string
		want  int
	}{{
		name:  "example",
		input: example,
		want:  480,
	}}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := part2(tt.input); got != tt.want {
				t.Errorf("part2() = %v want %v", got, tt.want)
			}
		})
	}
}
