package main

import (
	"fmt"
)

func main() {
	var n, t int
	fmt.Scanf("%d %d\n", &n, &t)
	s := make([]byte, n+1)
	fmt.Scanf("%s\n", &s)
	var minpos int
	dotpos := -1
	for ; minpos < len(s)-1; minpos++ {
		if s[minpos] == '.' {
			dotpos = minpos
			continue
		}
		if dotpos != -1 && s[minpos] >= '5' {
			break
		}
	}
	for i := minpos; i > dotpos; i-- {
		if t == 0 || s[i] < '5' {
			break
		}
		minpos--
		t--
		if i == dotpos-1 {
			s[i-2]++
		} else {
			s[i-1]++
		}
	}
	s = s[:minpos+1]
	if s[len(s)-1] == '.' {
		s = s[:minpos]
	}
	fmt.Print(string(s))
}