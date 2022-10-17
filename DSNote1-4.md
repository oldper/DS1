# Recursion

### Definition

Define a base case and any other situation can back to base case.

### How to use

Split a question in small pieces and every pieces are in same way to solve.

### Warning

Although recursion is a powerful way, it still has some problems. For instance, sometimes recursion spends more memory or time to solve a problem. So if you want to use. And there is an interesting thing that some problems are perfect fit with recursion. We will talk about it later.

### Example ( use go ) 

##### Factorial

``` go
func fac( n int ) int {
    if n > 1 {
        return 1
    } else {
        return n * fac(n-1)
    }
}
```

### GCD

``` go 
func GCD ( a int, b int ) int {
    if b == 0 {
        return a
    } else if b > a {
        return GCD( a, b%a )
    } else {
        return GCD( b, a%b )
    }
}
```



##### Fibonacci Series

```go
func fib( n int ) int {
    if n == 1 || n == 2 {
        return 1
    } else {
        return fib(n-1)+fib(n-2)
    }
}
```

 

##### Tower of Hanoi

``` go
func towers( disk int, source, dest, auxliary string ) {
    if disk == 1 {
        fmt.Print( "Move form ", source, " to ", dest )
    } else {
        towers( disk - 1, source, auxliary, dest )
        fmt.Print( "Move from ", source, " to ", dest )
        towers( disk - 1, auxliary, dest, source )
    }
}
```

And there are some other like kth Small, combination number etc....

# ADT

### Background Knowledge OOP( object oriental programming )

Just like nature, we can see our problem as some object. Each object has its data and method.

##### Principle

1. Encapsulation
2. Inheritance
3. Polymorphism

### C++ Class ( easy part and useful )

``` C++
class object {
    public : // can be used everywhere
    
    private: // only can be used in class
}

int main() {
    object obj;
}
```

### Example ( list )

##### Data

I don't think this need to explain.

##### Method

1. Insert
2. isEmpty
3. Delete
4. search

etc..... You can add what you want the list to do.

# Linked List

### Background Knowledge Pointer

Pointer is a data type that store address. You can use pointer to link with normal data.

### Practice in code ( go ) 

```go
type Node struct {
    Val interface{} // data
	next *Node // to next
}

type linkedList struct {
    head *Node
    tail *Node
}
```

### Theory

Every node of a linked list has data and a pointer that link to next node. Because of the pointer named next, the list can be linked together.

### Some Method

``` go
func (list *linkedList) isEmpty() bool {
    return list.head == nil
}

func (list *linkedList) append(node *Node) {
    if list.isEmpty() {
        list.head = node
        list.tail = node
        return
    }
    
    list.tail.next = n
    list.tail = n
}

func (list *linkedList) prepend( node *Node) {
    if list.isEmpty() {
        list.head = node
        list.tail = node
        return
    }
    
    node.next = list.head
    list.head = node
}

func (list *linkedLIst) pop() (*Node, error ) {
    if list.isEmpty() {
        return nil, fmt.Print( "empty" );
    }
    
    var previous *Node
    if list.tail == list.head {
        previous = list.head
        list.head = nil
        list.tail = nil
    }
    
    for cur := list.head ; cur != list.tail ; cur = cur.next {
        previous = cur
    }
    
    tmp := previous.Next
    previous.Next = nil
    list.tail = previous
    return tmp, nil
}
```

There are still a lot of method. I just program some important method.

# Recursive solution technique

### Define Languages

this part is just talking about the grammars of C++.

### Algebraic Expressions

1. Infix -> normal
2. Prefix -> put the operator before operands
3. Postfix -> opposite to Prefix

### Backtracking

Go to the start point when it can't run in that situation.

##### Eight Queen Solution

1. Base Case: No more columns to consider.
2. Other cases: If success, consider next column.

``` go
// code in Go
type Point struce {
    x, y int
}

var results = make([][]Point, 0 )
func canPLace( target Point, board []Point ) bool {
    for _, point:= range board {
        if canAttack( point, target) {
            return false
        }
    }
    return true
}

func canAttack( a, b Point ) bool {
    return a.x == b.x || a.y == b.y || nath.Abs(float64(a.x-b.x)) == math.Abs(float64(a.y-b.y))
}

func eightQueens(point Point, current []Point, n int) {
    if CanPlace( point, current ) {
        current = append(current, point)
        if len(current) == n {
            cur := make([]Point, n )
            for i, point := range current {
                cur[i] = point
            }
            results = append(results, c)
        } else {
            for col:=0; col < n ; col++ {
                for row := point.y ; row < n ; row++ {
                    eightQueens(Point{x:col, y:row}, current, n )
                }
			}
        }
    }
}
```

