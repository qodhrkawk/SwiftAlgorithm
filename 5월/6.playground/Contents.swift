import UIKit

//
//let n = readLine()!.components(separatedBy: [" "]).map { Int($0)! }
//let (a, b) = (n[0], n[1])
//
//for _ in 0..<b {
//    for _ in 0..<a {
//        print("*", separator: "", terminator: "")
//    }
//    print("")
//}


func solution1(_ arr1:[[Int]], _ arr2:[[Int]]) -> [[Int]] {
    
    var answer:[[Int]] = []
    
    for i in 0..<arr1.count {
        var tmp:[Int] = []
        for j in 0..<arr1[0].count {
            tmp.append(arr1[i][j]+arr2[i][j])
        }
        answer.append(tmp)
    }
    
    
    return answer
}


func solution2(_ n:Int, _ t:Int, _ m:Int, _ p:Int) -> String {
    
    var arr = ""
    var answer = ""

    
    var num = 0
    var count = m-1
    while answer.count < t {
        var tmp = String(num,radix: n)
        
        if tmp.count > count {
            answer += tmp[tmp.index(tmp.startIndex, offsetBy: count)..<tmp.index(tmp.startIndex, offsetBy: count+1)]
        }
        
        
        
        num += 1
    }
    
    
    while true {
        if arr.count/m >= t {
            break
        }
        arr += String(num,radix: n)
        num += 1
    }
    
    arr = arr.uppercased()
    
    var i = p-1
    
    while i < arr.count {
        answer += arr[arr.index(arr.startIndex, offsetBy: i)..<arr.index(arr.startIndex, offsetBy: i+1)]
        i += m
    }
    
    
    
    
    return answer
}


func pow (_ base:Int, _ power:Int) -> Int {
  var answer : Int = 1
  for _ in 0..<power { answer *= base }
  return answer
}

func solution(_ n:Int, _ A:Int, _ B:Int) -> Int
{
    var a = A
    var b = B
    var answer = 0
    
    if a > b {
        swap(&a,&b)
    }
    
    for round in 1..<21 {
        var mid = 1
        while true {
            if mid > a {
                mid -= pow(2,round)
            }
            else if mid <= a && a < mid+pow(2,round) {
                if b < mid+pow(2,round) {
                    print(a,mid)
                    return round
                }
                break
            }
            else {
                mid += pow(2,round)
            }
            
        }
        
        
    }

    
    

    return answer
}

print(solution(8, 6, 7))
