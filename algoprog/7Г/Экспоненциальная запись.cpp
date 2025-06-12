package main

import (
	"fmt"
)

func main() {
	a := make([]byte, 1e6)
	fmt.Scanf("%s", &a)
	for i := 0; i < len(a); i++ {
		if a[i] != '0' {
			a = a[i:]
			break
		}
	}
	dotpos := len(a)
	for i := 0; i < len(a); i++ {
		if a[i] == '.' {
			dotpos = i
			break
		}
	}
	for i := len(a) - 1; i >= dotpos; i-- {
		if a[i] != '0' {
			a = a[:i+1]
			break
		}
	}
	dotpos = len(a)
	for i := 0; i < len(a); i++ {
		if a[i] == '.' {
			dotpos = i
			break
		}
	}
	e := -1
	for i := 0; i < dotpos; i++ {
		e++
	}
	if e == -1 {
		for i := dotpos + 1; i < len(a); i++ {
			if a[i] != '0' {
				break
			}
			e--
		}
	}
	if dotpos != len(a) {
		a = append(a[:dotpos], a[dotpos+1:]...)
	}
	for i := len(a) - 1; i >= 0; i-- {
		if a[i] != '0' {
			a = a[:i+1]
			break
		}
	}
	for i := 0; i < len(a); i++ {
		if a[i] != '0' && a[i] != '.' {
			a = a[i:]
			a = append(a[:2], a[1:]...)
			a[1] = '.'
			break
		}
	}
	fmt.Printf("%s", a)
	if e != 0 {
		fmt.Printf("E%d", e)
	}
}