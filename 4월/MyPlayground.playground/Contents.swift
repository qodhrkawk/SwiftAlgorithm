import Foundation

// 프로그래머스 문자열 내맘대로 정리하기

func solution(_ strings:[String], _ n:Int) -> [String] {
    
    let index = strings[0].index(strings[0].startIndex,offsetBy: n)
    
    return strings.sorted(by: { (left: String, right:String)-> Bool in
        if left[index] == right[index] {
            return left < right
        }
        else {
            return left[index]<right[index]
        }

    })
    
}



// 프로그래머스 내적


func solution(_ a:[Int], _ b:[Int]) -> Int {
    
    var answer = 0
    for i in 0..<a.count {
        answer += a[i]*b[i]
    }
    
    
    
    return answer
}


// 프로그래머스 음양 더하기

func solution(_ absolutes:[Int], _ signs:[Bool]) -> Int {
    var abs = absolutes
    
    for (idx,sign) in signs.enumerated() {
        if !sign {
            abs[idx] = -abs[idx]
        }
        
    }
    
    
    
    return abs.reduce(0,+)
}
