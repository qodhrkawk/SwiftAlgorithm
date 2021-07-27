import Foundation

var greeting = "Hello, playground"


func solution(_ s:String) -> Int{

    var stack:[Character] = []
    
    for c in s {
        if !stack.isEmpty{
            if stack[stack.count-1] == c {
                stack.popLast()
            }
        }
        
        else {
            stack.append(c)
        }
        
    }
    
    if stack.isEmpty {
        return 1
    }
    return 0

}

print(solution("cdcd"))
