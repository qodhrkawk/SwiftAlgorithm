import UIKit

var str = "Hello, playground"


//프로그래머스 비밀지도
var completionHandlers: [()->Void] = []

func getPerson(completion: @escaping () -> Void) {
    
    print("a")
}


func solution1(_ n:Int, _ arr1:[Int], _ arr2:[Int]) -> [String] {
    var answer: [String] = []
    
    var binary1: [String] = []
    var binary2: [String] = []
    
    for i in 0..<n {
        var bin1 = String(arr1[i],radix: 2)
        var bin2 = String(arr2[i],radix: 2)
        for _ in 0..<(n-bin1.count) {
            bin1.insert("0", at: bin1.startIndex)
        }
        for _ in 0..<(n-bin2.count) {
            bin2.insert("0", at: bin1.startIndex)
        }
        
        binary1.append(bin1)
        binary2.append(bin2)
    }
    for i in 0..<n {
        var tmp = ""
        for j in 0..<n {
            if binary1[i][binary1[i].index(binary1[i].startIndex, offsetBy: j)] == "1" || binary2[i][binary2[i].index(binary2[i].startIndex, offsetBy: j)] == "1" {
                tmp+="#"
            }
            else {
                tmp += " "
            }
        }
        
        answer.append(tmp)
    }
    
    
    return answer
}

print(solution1(5, [9, 20, 28, 18, 11], [30, 1, 21, 17, 28]))


func solution2(_ s:String, _ n:Int) -> String {
    
    var answer = ""
    for c in s {
        if c != " "{
            if c.asciiValue! >= 65 && c.asciiValue! <= 90 {
                print(String((c.asciiValue!+UInt8(n)-65)%26+65))
                answer += String(UnicodeScalar((c.asciiValue!+UInt8(n))%26+65))
            }
            else if c.asciiValue! >= 97 && c.asciiValue! <= 122 {
                print(String((c.asciiValue!+UInt8(n)-97)%26+97))
                answer += String(UnicodeScalar((c.asciiValue!+UInt8(n))%26+97))
            }
        }
        else {
            answer += " "
        }
        
    }
    
   
    return ""
}


func solution3(_ numbers:[Int], _ hand:String) -> String {
    let lefts = [1,4,7]
    let rights = [3,6,9]

    
    let arr = [[],[0,0,1,0,0,2,0,0,3,0,0,4,0],[0,0,0,0,0,1,0,0,2,0,0,3,0],[0,0,1,0,0,2,0,0,3,0,0,4,0],[0,0,2,0,0,1,0,0,2,0,0,3,0],[0,0,1,0,0,0,0,0,1,0,0,2,0],[0,0,2,0,0,1,0,0,2,0,0,3,0],[0,0,3,0,0,2,0,0,1,0,0,2,0],[0,0,2,0,0,1,0,0,0,0,0,1,0],[0,0,3,0,0,2,0,0,1,0,0,2,0],[0,0,4,0,0,3,0,0,2,0,0,1,0],[0,0,3,0,0,2,0,0,1,0,0,0,0],[0,0,4,0,0,3,0,0,2,0,0,1,0]]
    
    var answer = ""
    
    var leftFinger = 10
    var rightFinger = 12
    
    for num in numbers {
        if lefts.contains(num) {
            leftFinger = num
            answer += "L"
        }
        else if rights.contains(num) {
            rightFinger = num
            answer += "R"
        }
        else {
            var nowNum = num
            if num == 0 {
               nowNum = 11
            }

            if arr[leftFinger][nowNum] < arr[rightFinger][nowNum] {
                leftFinger = nowNum
                answer += "L"
            }
            else if arr[leftFinger][nowNum] > arr[rightFinger][nowNum]{
                rightFinger = nowNum
                answer += "R"
            }
            else {
                if hand == "left" {
                    leftFinger = nowNum
                    answer += "L"
                }
                else {
                    rightFinger = nowNum
                    answer += "R"
                }
            }
            
        }
        
    }
    
    
    return answer
}

print(solution3([1, 3, 4, 5, 8, 2, 1, 4, 5, 9, 5], "right"))
print(solution3([7, 0, 8, 2, 8, 3, 1, 5, 7, 6, 2], "left"))



// 프로그래머스 로또의 최고 순위와 최저 순위

func solution(_ lottos:[Int], _ win_nums:[Int]) -> [Int] {
    
    var correct = 0
    var zeros = 0
    var answer: [Int] = []
    for lotto in lottos {
        if win_nums.contains(lotto) {
            correct += 1
        }
        else if lotto == 0 {
            zeros += 1
        }
        
    }
    var best = correct+zeros
    if best < 2 {
        answer.append(6)
    } else {
        answer.append(7-best)
    }
    if correct < 2 {
        answer.append(6)
    }
    else{
        answer.append(7-correct)
    }
    
    
    return answer
}

// 프로그래머스 가운데 글자 가져오기


func solution(_ s:String) -> String {
    
    if s.count%2 == 0{
        let range = s.index(s.startIndex, offsetBy: s.count/2-1)..<s.index(s.startIndex, offsetBy: s.count/2+1)
        return String(s[range])
    }
    else {
        return String(s[s.index(s.startIndex, offsetBy: s.count/2)])
    }
}
