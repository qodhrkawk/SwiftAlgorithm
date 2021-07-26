import Foundation


var answer = 0

func solution(_ numbers:[Int], _ target:Int) -> Int {
    
    
    
    dfs(numbers,target,0,0)
    
    return answer
}

func dfs(_ numbers:[Int], _ target:Int, _ depth: Int, _ curVal: Int)  {
    if depth == numbers.count {
        if curVal == target {
            answer += 1
        }
    }
    else {
        dfs(numbers,target,depth+1,curVal+numbers[depth])
        dfs(numbers,target,depth+1,curVal-numbers[depth])
    }
    
    
    
}
print(solution([1,1,1,1,1], 3))
