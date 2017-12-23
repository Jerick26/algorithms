package main

import "log"

func strcmp(a, b string) int {
	var min = len(b)
	if len(a) < len(b) {
		min = len(a)
	}
	var diff int
	for i := 0; i < min && diff == 0; i++ {
		diff = int(a[i]) - int(b[i])
	}
	if diff == 0 {
		diff = len(a) - len(b)
	}
	return diff
}

func main() {
	a := "abcedf"
	b := "abc1dfgh"
	if strcmp(a, b) < 0 {
		log.Fatal("compare error for ", a, ", and ", b)
	}
}
