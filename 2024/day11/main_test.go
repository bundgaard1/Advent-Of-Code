package main

import (
	"testing"
)

var example = `125 17`

func Test_part1(t *testing.T) {
	tests := []struct {
		name   string
		input  string
		blinks int
		want   int
	}{{
		name:   "jo",
		input:  example,
		blinks: 25,
		want:   55312,
	}}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := part1(tt.input, tt.blinks); got != tt.want {
				t.Errorf("part1() = %v, want %v", got, tt.want)
			}
		})
	}
}

func Test_part2(t *testing.T) {
	tests := []struct {
		name   string
		input  string
		blinks int
		want   int
	}{{
		name:   "jo",
		input:  example,
		blinks: 25,
		want:   55312,
	}}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := part2(tt.input, tt.blinks); got != tt.want {
				t.Errorf("part2() = %v, want %v", got, tt.want)
			}
		})
	}
}
