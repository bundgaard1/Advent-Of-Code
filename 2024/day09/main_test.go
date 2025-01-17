package main

import (
	"testing"
)

var example = `2333133121414131402`

func Test_part1(t *testing.T) {
	tests := []struct {
		name  string
		input string
		want  int
	}{{
		name:  "a",
		input: example,
		want:  1928,
	}}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := part1(tt.input); got != tt.want {
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
	}{{
		name:  "part 2",
		input: example,
		want:  2858,
	}}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := part2(tt.input); got != tt.want {
				t.Errorf("part2() = %v, want %v", got, tt.want)
			}
		})
	}
}
