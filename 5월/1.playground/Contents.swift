import Foundation


//프로그래머스 p,y찾기

func solution(_ s:String) -> Bool
{

    var ps = 0
    var ys = 0
    
    for (idx,c) in s.enumerated() {
        if c == "p" || c == "P" {
            ps += 1
        }
        else if c == "Y" || c == "y" {
            ys += 1
        }
        
    }
    
    

    return ps == ys
}



//프로그래머스 직사각형 별찍기

let n = readLine()!.components(separatedBy: [" "]).map { Int($0)! }
let (a, b) = (n[0], n[1])

for _ in 0..<a {
    for _ in 0..<b {
        print("*",separator:"")
    }
    print("")
}

print(a + b)
