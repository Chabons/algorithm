package main

import (
	"../Btree"
	"fmt"
)

func main() {
	tree, err := Btree.NewBtree(2)
	if err != nil {
		panic(err)
	}

	tree.Insert(5)
	tree.Insert(8)
	tree.Insert(9)
	tree.Insert(1)
	fmt.Println(tree)
	tree.Insert(3)
	tree.Insert(4)
	tree.Insert(10)
	tree.Insert(11)
	tree.Insert(12)
	tree.Insert(13)
	fmt.Println(tree)
}
