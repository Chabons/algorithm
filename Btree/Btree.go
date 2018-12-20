package Btree

import "fmt"

// NOTE:除根节点以外的每个内部节点至少有 t 个孩子，除根节点以外的每个结点至少有 t-1 个关键字。如果树非空，根结点至少有一个关键字。
//		每个内部结点最多有 2t 个孩子， 最多有 2t-1 个关键字。如果一个节点恰好有 2t-1 个关键字，则称该结点是满的。

type Key int
type Node struct {
	Leaf     bool
	Keys     []Key   // the number of keys, < 2 * degree - 1
	Children []*Node // the number of children must less than 2 * degree
}

type Btree struct {
	Root   *Node
	Degree int
	Desc   []*string
}

func NewNode(degree int, isLeaf bool) *Node {
	if degree < 2 {
		panic("B-tree's degree must greater than 2")
		return nil
	}

	return &Node{
		Leaf:     isLeaf,
		Keys:     make([]Key, 0, 2*degree-1),
		Children: make([]*Node, 0, 2*degree),
	}
}

func (this *Node) Search(k Key) (n *Node, idx int) {
	if this == nil {
		return nil, 0
	}

	var i int
	size := len(this.Keys)
	for i = 0; i < size && this.Keys[i] < k; i++ {
	}

	if i < size && this.Keys[i] == k {
		n, idx = this, i
	} else if this.Leaf {
		n, idx = nil, 0
	} else {
		if i < len(this.Children) && this.Children[i] != nil {
			n, idx = this.Children[i].Search(k)
		} else {
			panic("unknow error")
		}
	}

	return
}

func (this *Node) KeySize() int {
	return len(this.Keys)
}

func (this *Node) KeyFull(degree int) bool {
	return this.KeySize() >= (2*degree - 1)
}

func (this *Node) ChildSize() int {
	return len(this.Children)
}

func (this *Node) ChildFull(degree int) bool {
	return this.ChildSize() >= 2*degree
}

func (this *Node) InsertNoneFull(degree int, k Key) {
	if this.KeyFull(degree) {
		panic("call InsertNoneFull function, when this node's key is full")
	}

	var i int
	if this.Leaf {
		this.Keys = append(this.Keys, k)
		for i = this.KeySize() - 1; i > 0 && this.Keys[i-1] > k; i-- {
			this.Keys[i] = this.Keys[i-1]
		}
		this.Keys[i] = k
	} else {
		size := this.KeySize()
		for i = 0; i < size && k > this.Keys[i]; i++ {
		}

		if i >= this.ChildSize() || this.Children[i] == nil {
			panic("unexpected error")
			return
		}

		if this.Children[i].KeyFull(degree) {
			this.Split(degree, i)
			if k > this.Keys[i] {
				i += 1
			}
		}
		this.Children[i].InsertNoneFull(degree, k)
	}
}

func (this *Node) Split(degree int, idx int) {
	if this == nil || idx >= this.ChildSize() || !this.Children[idx].KeyFull(degree) || this.KeyFull(degree) {
		panic("parameters error")
	}

	c := this.Children[idx]
	n := NewNode(degree, c.Leaf)
	// copy keys
	n.Keys = append(n.Keys, c.Keys[degree:]...)
	if !c.Leaf {
		if !c.ChildFull(degree) {
			panic("unknown error, the size of children does not match our expectation")
		}

		// copy children
		n.Children = append(n.Children, c.Children[degree:]...)
		c.Children = append(c.Children[:degree])
	}

	// shift parent's key
	this.Keys = append(this.Keys[:idx+1], this.Keys[idx:]...)
	this.Keys[idx] = c.Keys[degree-1]
	c.Keys = append(c.Keys[:degree-1]) // [0, this.Degree - 1)

	// shift parent's child
	this.Children = append(this.Children[:idx+2], this.Children[idx+1:]...)
	this.Children[idx+1] = n
}

func NewBtree(degree int) (*Btree, error) {
	if degree < 2 {
		return nil, fmt.Errorf("B-tree's degree must greater than 2")
	}

	var tree *Btree = new(Btree)
	tree.Degree = degree
	tree.Root = NewNode(degree, true)
	tree.Desc = make([]*string, 0, 3)

	return tree, nil
}

func (this *Btree) Search(k Key) (n *Node, idx int) {
	return this.Root.Search(k)
}

func (this *Btree) Insert(k Key) {
	root := this.Root
	if node, _ := root.Search(k); node != nil {
		panic(fmt.Sprintf("key[%d] already exists", k))
	}

	if root.KeyFull(this.Degree) {
		n := NewNode(this.Degree, false)
		n.Children = append(n.Children, this.Root)
		this.Root = n
		this.Root.Split(this.Degree, 0)
	}

	this.Root.InsertNoneFull(this.Degree, k)
}

func addSpace(result *string, n int) {
	tmp := n - len(*result)/5
	if tmp <= 0 {
		return
	}
	for i := 0; i < tmp; i++ {
		*result += "     "
	}
}

func (this *Btree) toString(node *Node, depth int, idx int) (NewIdx int) {
	if len(this.Desc) <= depth {
		var result string
		this.Desc = append(this.Desc, &result)
	}

	size := node.KeySize()
	for i := 0; i < size; i++ {
		if !node.Leaf {
			idx = this.toString(node.Children[i], depth+1, idx)
		}
		addSpace(this.Desc[depth], idx)
		*this.Desc[depth] += fmt.Sprintf("%04d ", node.Keys[i])
	}
	idx += size
	if !node.Leaf && size > 0 {
		idx = this.toString(node.Children[size], depth+1, idx)
	}

	return idx
}

func (this *Btree) String() string {
	this.Desc = this.Desc[:0]
	this.toString(this.Root, 0, 0)
	var result string
	size := len(this.Desc)
	result += "----------------------------tree string begin------------------------\n"
	for i := 0; i < size; i++ {
		result += *this.Desc[i] + "\n"
	}
	result += "----------------------------tree string end  ------------------------\n"
	return result
}
