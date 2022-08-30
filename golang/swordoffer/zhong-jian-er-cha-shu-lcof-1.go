package swordoffer

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

// 思路
// 关键是要理解，前序与中序之间的数列的关系
// 1. “前序”的一个节点必定是根节点
// 2. 那么基于此根节点，就能把“中序”分为左右两部分
// 3. 基于上面"中序"中得到的左边一部分，又能把前面"前序"中除根节点之外的序列分为左右两部分
// 4. 这样就得到了，除根节点之外的，"前序"左右两部分和"中序"左右连部分
// 5. 这样就能递归处理了
/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func buildTree(preorder []int, inorder []int) *TreeNode {
	if len(preorder) == 0 || len(inorder) == 0 {
		return nil
	}
	var node TreeNode
	var leftPreorder []int
	var leftInorder []int
	var rightPreorder []int
	var rightInorder []int

	node.Val = preorder[0]
	if len(preorder) > 1 {
		leftInorder, rightInorder = getInorderLeftRigh(preorder[0], inorder)
		leftPreorder, rightPreorder = getPreorderLeftRigh(preorder[1:], leftInorder)
	} else {
		leftInorder, rightInorder = nil, nil
		leftPreorder, rightPreorder = nil, nil
		node.Left = nil
		node.Right = nil
		return &node
	}

	node.Left = buildTree(leftPreorder, leftInorder)
	node.Right = buildTree(rightPreorder, rightInorder)
	return &node
}

func getInorderLeftRigh(root int, inorder []int) (left []int, right []int) {
	for idx, val := range inorder {
		if val == root {
			if idx > 0 {
				left = inorder[0:idx]
			} else {
				left = nil
			}
			if idx < (len(inorder) - 1) {
				right = inorder[idx+1:]
			} else {
				right = nil
			}
			return
		}
	}
	return nil, nil
}

func getPreorderLeftRigh(preorder []int, leftPart []int) (left []int, right []int) {
	left = preorder[0:len(leftPart)]
	right = preorder[len(leftPart):]
	return
}
