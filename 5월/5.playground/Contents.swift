import UIKit


func solution(_ s:String) -> String {
    
    var arr = Array(s)
    
    arr = arr.sorted()
    
    var answer = ""
    
    for i in 0..<arr.count {
        answer += String(arr[arr.count-1-i])
    }
    
    return s
}


