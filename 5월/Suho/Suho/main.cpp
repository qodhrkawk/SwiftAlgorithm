#include <iostream>
#include <string>
using namespace std;

//가장 많이 예매된 좌석
int seatCountTotalArr[25];

//영화별 많이 예매된 좌석
int seatCountMovieArr[3][25];

//성별
int seatCountGenderArr[2][25];


enum Gender {
    MALE,
    FEMALE
};

class Seat {
public:
    Seat(){reserved = 0;}
    
//    0: 예약 안됨 1: 예약 됨 2: 거리두기
    int reserved = 0;

};


class SeatForCount {
public :
    SeatForCount(){ }
    
//    gender[0] : 남자 몇명이 예매?
    int gender[2];
//    movie[0] : 0번쨰 영화 몇명이 예매?
    int moives[3];
//    time[0] : 0번째 시간대에 몇명이 예매?
    int times[6];
    
};

class Theater {
public :
    
    Theater(){}
    Theater(string time1,string time2){
       
        for(int i = 0; i < 5; i++) {
            for(int j = 0 ;j < 5; j++) {
                seats[i][j][0] = Seat();
                seats[i][j][1] = Seat();
            }
        }
        
        times[0] = time1;
        times[1] = time2;
        
    }
    
    Seat seats[5][5][2];
    string times[2];
};

class Movie {
public :
    Movie(){}
    Movie(int theater1,int theater2,int time1,int time2,string i_movieName) {
        theaterNums[0] = theater1;
        theaterNums[1] = theater2;
        times[0] = time1;
        times[1] = time2;
        movieName = i_movieName;
    }
    string movieName;
    int theaterNums[2];
    int times[2];
};

class Reservation{
public:
    Reservation() {}
    Reservation(string i_movie, int i_seatNum,int i_theaterNum,int i_timeNum) {
        movie = i_movie;
        seatNum = i_seatNum;
        timeNum = i_timeNum;
        theaterNum = i_theaterNum;
        valid = true;
    }
    
    string movie;
    int theaterNum;
    int timeNum;
    int seatNum;
    bool valid;
};


class Client {
public:
    int point = 0;
    int gender = MALE;
    string name = "";
    
    Reservation reservation;
};

Client logIn(){
    cout<<"셩별 입력 : "<<endl;
    cout<<"1.남 2.여"<<endl;

    Client client;
    int gender = 0;
    cin>>gender;
    cout<<endl;
    gender == 1 ? client.gender = MALE : client.gender = FEMALE;

    cout<<"고객 이름 입력: "<<endl;
    cin>>client.name;
    cout<<endl;

    return client;

}

int selectSeat(Theater theater,int time){
    bool flag = false;
    
   
    for(int i = 0; i< 5; i++){
        for(int j = 0; j < 5; j++){
            if(theater.seats[i][j][time].reserved == 1){
                cout.width(15);
                cout<<i*5+j+1<<"번:X";
            }
            else if(theater.seats[i][j][time].reserved == 2) {
                cout.width(15);
                cout<<i*5+j+1<<"번:X";
            }
            
            else{
                cout.width(15);
                cout<<i*5+j+1<<"번:O";
            }
        }
        cout<<endl;
    }
    int result = 0;
    while(!flag) {
        cout<<"좌석을 골라주세요"<<endl;
        cin>>result;
        if(theater.seats[result/5][result%5-1][time].reserved != 0) {
            cout<<"사용 가능한 좌석을 골라주세요"<<endl;
        }
        else {
            flag = true;
        }
        
    }
    
    
   
    return result;

}

int selectAction(){
    cout<<"Select Action"<<endl;
    cout<<"1. 예매하기  2. 예매 취소하기  3. 통계 보기"<<endl;
    int result = 0;
    cin>>result;
    return result;

}

int selectMovie(Movie* movies){
    cout<<"영화 선택"<<endl;
    for(int i = 0; i < 3; i++ ) {
        cout<<movies[i].movieName<<"\t";
    }
    cout<<endl;
    int result;
    cin>>result;
    return result-1;
}

int selectTheater(Theater* theater,int* theaterCandidates){
    cout<<"상영관 선택"<<endl;
    
    for(int i = 0; i < 2; i++) {
        printf("%d관\t",theaterCandidates[i]+1);
    }
    int n;
    cin>>n;
    return n-1;
}

int selectTime(Theater theater) {
    cout<<"상영시간 선택"<<endl;
    for(int i = 0 ; i<2; i++) {
        cout<<theater.times[i]<<"\t"<<endl;
    }
    int n;
    cin>> n;
    return n-1;
    
}


Theater reserveSeat(int seatNum,Theater theater,int time) {
//    y : 행 x : 열
    int y = seatNum/5;
    int x = seatNum%5-1;
    
//    거리두기 설정(상하좌우)
    int direction[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
//    일단은 지금 자리 예약으로 설정
    theater.seats[y][x][time].reserved = 1;
    
//    거리두기 설정하기
    for(int i = 0; i < 4; i ++) {
//        행에 더하기
        int newY = y+direction[i][0];
//        열에 더하기
        int newX = x+direction[i][1];
        if(newY >= 0 && newY < 5 && newX >= 0 && newX < 5) {
            theater.seats[newY][newX][time].reserved = 2;
        }
    }
    
    return theater;
}


Theater cancelSeat(int seatNum,Theater theater,int time) {
    int y = seatNum/5;
    int x = seatNum%5-1;
    
//    거리두기 설정(상하좌우)
    int direction[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    theater.seats[y][x][time].reserved = 0;
    for(int i = 0; i < 4; i ++) {
        int newY = y+direction[i][0];
        int newX = x+direction[i][1];
        if(newY >= 0 && newY < 5 && newX >= 0 && newX < 5) {
            theater.seats[newY][newX][time].reserved = 0;
        }
    }
    return theater;
}

void showMost3(int* arr){

//    0: 1등 1: 2등 2: 3등 인데 얘는 그 좌석번호를 저장(나중에 1더해야함) (ex : rank가 4면 5번 자리 의미)
    int rank[3] = {-1,};
    
//    위랑 같은데 얘는 그 좌석번호의 값을 저장(ex : 10번 예약됨)
    int nums[3] = {0,};
//  [1,2,3,4,5,6,7,8,9,....]
    for(int i = 0; i < 25; i++) {
        
//        3등보다 값이 크냐?
        if(arr[i] > nums[2]) {
            
//            2등보다 값이 크냐?
            if(arr[i] > nums[1]) {
                
//                1등보다 값이 크냐?
                if (arr[i] > nums[0]) {
//                    2등을 3등으로
                    rank[2] = rank[1];
                    nums[2] = nums[1];
                    
//                   1등을 2등으로
                    rank[1] = rank[0];
                    nums[1] = nums[0];
                    
//                    지금 애를 1등으로
                    rank[0] = i;
                    nums[0] = arr[i];
                    
                }
                
//                그럼 얜 2등
                else {
                    rank[2] = rank[1];
                    nums[2] = nums[1];
                    rank[1] = i;
                    nums[1] = arr[i];
                }
            }
            
//            그럼 얜 3등
            else {
                rank[2] = i;
                nums[2] = arr[i];
            }
        }
    }
    
    if(nums[0] == 0) {
        cout<<"아직 예매 정보가 없습니다."<<endl;
    }
    else {
        for(int i = 0;i < 3; i++) {
            if(nums[i] != 0) {
                cout<<i+1<<"위 : "<<rank[i]+1<<"번 좌석("<<nums[i]<<"회)"<<endl;
            }
            
        }
    }
   
}




int main(){

    string movieNames[3] = {"1. 인셉션","2. 타이타닉","3. 국가대표"};
    string times[6] = {"11:00","14:00","13:00","17:00","15:00","19:00"};

    Movie movies[3];
    for(int i = 0; i<3; i++) {
        movies[i] = Movie(i%3, (i+1)%3, i%2, (i+1)%2,movieNames[i]);
    }
    
    Client *clients = new Client[100];
    int clientNum = 0;
    
    SeatForCount *seatForcounts = new SeatForCount[25];
    for(int i = 0; i<25;i++){
        SeatForCount seatForcount = SeatForCount();

        for(int j = 0; j< 2; j++){
            seatForcount.gender[j] = j+2;
        }
        for(int j = 0; j< 6; j++){
            seatForcount.times[j] = j+2;
        }
        for(int j = 0; j< 3; j++){
            seatForcount.moives[j] = j+2;
        }
        
        seatForcounts[i] = seatForcount;
    }

    Theater theaters[3];
    
    theaters[0] = Theater("11:00","14:00");
    theaters[1] = Theater("13:00","17:00");
    theaters[2] = Theater("15:00","19:00");
    
    for(int i = 0; i< 3; i++){
        for(int j = 0; j< 25; j++){
            seatCountMovieArr[i][j] = ((i+1)*j)%10;
            seatCountTotalArr[j] = ((i+1)*j)%20;
        }
    }
    for(int i = 0; i< 2; i++){
        for(int j = 0; j< 25; j++){
            seatCountGenderArr[i][j] = (((i+1)*j)%10)/2;
        }
    }
    


    while(true) {
        Client client;
        
//        과거에 로그인을 했던 유저인가
        bool past = false;

//        1. 예매하기 2. 취소 3. 통계
        int action = selectAction();
    
        switch(action) {
            case 1 : {
                client = logIn();
                
//                여기부터 원래 로그인 했었는지 확인. clientIdx : 현재 로그인한 사용자를 가리키는 인덱스(100개중에서)
                int clientIdx = -1;
                for(int i = 0; i < clientNum; i++){
                    if(clients[i].name == client.name && clients[i].gender == client.gender){
                        past = true;
//                        몇번째 인덱스에 있던 애인지 기록
                        clientIdx = i;
                    }
                }
//                신규 유저
                if(clientIdx == - 1) {
//                    5명 있었을 때 넣으면 5번 index에 넣어줌 (0~4번은 이미 있음)
                    clientIdx = clientNum;
                    clientNum += 1;
//                    등록
                   
                    clients[clientIdx] = client;
                }
                
               
     
                if(past) {

                    if(clients[clientIdx].reservation.valid == true) {
                        cout<<"이미 예약 정보가 존재합니다"<<endl;
                        break;
                    }
                }
                
//                여기까지 오는 경우는 1. 첫 로그인 2. 기존 유전데 예매 취소했어
                
                int movieNum = selectMovie(movies);

                int theaterCandidates[2] = {0,0};
                for(int i = 0; i < 2 ;i++){
                    theaterCandidates[i] = movies[movieNum].theaterNums[i];
                }
                
                
                int theaterNum = selectTheater(theaters,theaterCandidates);
                Theater nowTheater = theaters[theaterNum];
                
//                시간은 상영관당 두개니까 0,1 중에 하나
                int time = selectTime(nowTheater);
                int seatNum = selectSeat(nowTheater,time);
                
                cout<<"포인트를 사용하시겠습니까?. 현재 포인트 : "<<clients[clientIdx].point << endl;
                cout<<"1. 예 2. 아니오"<<endl;
                int pointUse;
                cin>>pointUse;
                int price = 8000;
                if(pointUse == 1) {
                    cout<<price-clients[clientIdx].point<<"원 결제되었습니다."<<endl;
                    clients[clientIdx].point = 0;
                    
                }
                else {
                    cout<<price<<"원 결제되었습니다."<<endl;
                }
                
                
                
                
//                통계
                seatCountTotalArr[seatNum-1] += 1;
                seatCountMovieArr[movieNum][seatNum-1] += 1;
                seatCountGenderArr[client.gender][seatNum-1] += 1;
                
                
                seatForcounts[seatNum].gender[client.gender] += 1;
                seatForcounts[seatNum].moives[movieNum] += 1;
                seatForcounts[seatNum].times[theaterNum*2+time] += 1;

                
//                예약 객체 생성해서 넣어주기
                Reservation reservation = Reservation(movies[movieNum].movieName,seatNum,theaterNum,time);
                clients[clientIdx].reservation = reservation;
                clients[clientIdx].point += 1000;
                cout<<"포인트 적립 완료. 현재 포인트 : "<<clients[clientIdx].point << endl;
                theaters[theaterNum] = reserveSeat(seatNum, nowTheater,time);
                
                
                break;
            }
            case 2 : {
                client = logIn();
                int clientIdx = -1;
                for(int i = 0; i < clientNum; i++){
                    if(clients[i].name == client.name && clients[i].gender == client.gender){
                        past = true;
                        clientIdx = i;
                    }
                }
              
                
                if(past) {

                    if(clients[clientIdx].reservation.valid == false) {
                        cout<<"예약 정보가 존재하지 않습니다"<<endl;
                        break;
                    }
                    
//                    진짜 취소하는 부분
                    else {
                        Reservation nowReservation = clients[clientIdx].reservation;
                        cout<<"예매 정보"<<endl;
                        cout<<nowReservation.movie<<" " <<nowReservation.theaterNum+1 << "관 "<< "예매 취소하시겠습니까?"<<endl;
                        cout<<"1. 예 2. 아니오"<<endl;
                        int cancel;
                        cin>>cancel;
                        if(cancel == 1){
                            theaters[nowReservation.theaterNum] = cancelSeat(nowReservation.seatNum, theaters[nowReservation.theaterNum], nowReservation.timeNum);
                            clients[clientIdx].reservation.valid = false;
                            clients[clientIdx].point -= 1000;
                        }
                        cout<<"포인트 적립 취소. 현재 포인트 : "<<clients[clientIdx].point << endl;
                    }
                }
//                신규유저
                else {
                    cout<<"예약 정보가 존재하지 않습니다"<<endl;
                }
                
                
                
                break;
            }
                
            case 3 : {
                
                
                cout<< "<<<<가장 많이 예매된 좌석>>>>"<<endl;
                showMost3(seatCountTotalArr);
                cout<<endl<<endl;
                
                cout<<"<<<<영화별 많이 예매된 좌석>>>>"<<endl;
                for(int i = 0; i < 3 ; i++) {
                    cout<<movies[i].movieName<<endl;
                    showMost3(seatCountMovieArr[i]);
                }
                cout<<endl<<endl;
                cout<<"<<<<남녀별 많이 예매된 좌석>>>>"<<endl;
                
                for(int i = 0; i < 2 ; i++) {
                    string s = i == 0 ? "남자" : "여자";
                    cout<<s<<endl;
                    showMost3(seatCountGenderArr[i]);
                }
                cout<<endl<<endl;
                
                cout<<"<<<<좌석 세부정보 확인>>>>"<<endl;
                cout<<"좌석 번호 입력 : "<<endl;
                int checkSeat;
                cin>>checkSeat;
                
                SeatForCount seatForShow = seatForcounts[checkSeat];
                
                cout<<"영화별 예매 횟수"<<endl;
                for(int i = 0; i < 3; i++){
                    cout<<movieNames[i]<<" : "<<seatForShow.moives[i]<< "회  ";
                }
                cout<<endl;
                cout<<"남녀 예매 비율"<<endl;
                
                cout<<seatForShow.gender[0]<< "회 : "<<seatForShow.gender[1]<<"회"<<endl;
                
                cout<<"상영대별 예매 횟수" <<endl;
                for(int i = 0; i < 6; i++){
                    cout<<times[i]<<" : "<<seatForShow.times[i]<< "회  "<<endl;
                }
                
                
            }
            default: {
                break;
            }

        }
    }

    return 0;
}
