package main

import (
	"C"
	"fmt"
	"sync"
)

func main() {
	// 3个协程，分别打印A、B、C，要求按顺序打印10次ABCABC...
	ch1 := make(chan struct{}, 1)
	ch2 := make(chan struct{}, 1)
	ch3 := make(chan struct{}, 1)
	wg := sync.WaitGroup{}
	wg.Add(3)
	go func() {
		for i := 0; i < 10; i++ {
			<-ch1
			fmt.Print("A")
			ch2 <- struct{}{}
		}
		wg.Done()
	}()

	go func() {
		for i := 0; i < 10; i++ {
			<-ch2
			fmt.Print("B")
			ch3 <- struct{}{}
		}
		wg.Done()
	}()

	go func() {
		for i := 0; i < 10; i++ {
			<-ch3
			fmt.Print("C")
			ch1 <- struct{}{}
		}
		wg.Done()
	}()

	ch1 <- struct{}{}
	wg.Wait()
	fmt.Println()
}
