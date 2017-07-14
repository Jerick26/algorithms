/******************************************************************************
 *  Compilation:  go build popcount.go
 *  Execution:    ./popcount 123456
 *
 *  PopCount returns the population count (number of set bits) of x.
 *
 *  % ./popcount 123456
 *  result is 6 for 123456 from PopCount
 *  result is 6 for 123456 from PopCountByClear
 *  a benchmark for measuring two PopCount method’s performance
 *  49.86ms elapsed for PopCount
 *  4557.68ms elapsed for PopCountByClear
 *
 ******************************************************************************/
package main

import (
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"time"
)

var pc [256]byte
var data [100000000]uint64

func init() {
	for i := range pc {
		pc[i] = pc[i/2] + byte(i&1)
	}
}

func init() {
	for i := range data {
		data[i] = rand.Uint64()
	}
}

// PopCount return the population count (number of set bits) of x
func PopCount(x uint64) int {
	return int(pc[byte(x>>(0*8))] +
		pc[byte(x>>(1*8))] +
		pc[byte(x>>(2*8))] +
		pc[byte(x>>(3*8))] +
		pc[byte(x>>(4*8))] +
		pc[byte(x>>(5*8))] +
		pc[byte(x>>(6*8))] +
		pc[byte(x>>(7*8))])
}

// PopCountByClear using clear rightmost bit
func PopCountByClear(x uint64) int {
	n := 0
	for x != 0 {
		x = x & (x - 1) // clear rightmost non-zero bit
		n++
	}
	return n
}

func main() {
	if v, err := strconv.ParseUint(os.Args[1], 10, 64); err == nil {
		fmt.Printf("result is %d for %d from PopCount\n", PopCount(v), v)
		fmt.Printf("result is %d for %d from PopCountByClear\n",
			PopCountByClear(v), v)
	} else {
		fmt.Fprintf(os.Stderr, "PopCount: %v\n", err)
		os.Exit(1)
	}
	fmt.Println("a benchmark for measuring two PopCount method’s performance")
	start := time.Now()
	for i := range data {
		PopCount(data[i])
	}
	fmt.Printf("%.2fms elapsed for PopCount\n", time.Since(start).Seconds()*1000)
	start = time.Now()
	for i := range data {
		PopCountByClear(data[i])
	}
	fmt.Printf("%.2fms elapsed for PopCountByClear\n",
		time.Since(start).Seconds()*1000)
}
