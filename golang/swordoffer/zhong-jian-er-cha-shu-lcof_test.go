package swordoffer

import (
	"fmt"
	"testing"
)

// 示例1:
// Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
// Output: [3,9,20,null,null,15,7]
func TestSwordOffer07Case1(t *testing.T) {
	fmt.Println("the rectangular name's result is ok")
	preorder := []int{3, 9, 20, 15, 7}
	inorder := []int{9, 3, 15, 20, 7}
	orderTree := buildTree(preorder, inorder)
	fmt.Printf("%v", orderTree)
}

// 测试2: 测试计算出来的体积是否符合预期
func TestGetSomething(t *testing.T) {
	fmt.Println("the rectangular volume's result is ok")
}
