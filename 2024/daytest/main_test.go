package main

import (
	"testing"
)

// var example = "321"

func Test_part1(t *testing.T) {
	tests := []struct {
		name  string
		input string
		want  int
	}{
		{
			name:  "test1",
			input: "12",
			want:  2,
		},
		{
			name:  "test2",
			input: "14",
			want:  2,
		},
		{
			name:  "test3",
			input: "1969",
			want:  654,
		},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := part1(tt.input); got != tt.want {
				t.Errorf("part1() = %v, want %v", got, tt.want)
			}
		})
	}
}

// var example2 = "123"

func Test_part2(t *testing.T) {
	tests := []struct {
		name  string
		input string
		want  int
	}{
		{
			name:  "test1",
			input: "12",
			want:  2,
		},
		{
			name:  "test2",
			input: "14",
			want:  2,
		},
		{
			name:  "test3",
			input: "1969",
			want:  966,
		},
		{
			name:  "test4",
			input: "100756",
			want:  50346,
		},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := part2(tt.input); got != tt.want {
				t.Errorf("part2() = %v, want %v", got, tt.want)
			}
		})
	}
}
