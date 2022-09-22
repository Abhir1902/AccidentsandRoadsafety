#include<iostream>
#include<windows.h>
#include<mysql.h>
#include<sstream>
#include<string>
#include<cmath>
#include<conio.h>
#include <thread>
#include <chrono>
using namespace std;
#define N 7 // Number of vertices
#define INF 99999
deletedb(MYSQL* conn,string User_id)
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    stringstream ss;
    ss<<"DELETE FROM driver WHERE User_id = '"+User_id+"' ";
    string query = ss.str();
    const char* q = query.c_str();
    mysql_query(conn,q);
}
selection(MYSQL*conn){
    MYSQL_ROW row;
    MYSQL_RES* res;
    string s;
    string pass ="";
    char ch;
    cout<<"Enter your user_id"<<endl;
    cin>>s;
    cout<<"Enter your password"<<endl;
    m:
    int c;
    ch = _getch();
    while(ch != 13){//You can enter max 13 characters
      pass.push_back(ch);
      cout << '*';
      ch = _getch();
   }
   cout<<endl;
    int flag=0;
    if(conn){
        int qstate=mysql_query(conn,"SELECT User_id,Name,password FROM driver");
        if(!qstate){
            res=mysql_store_result(conn);
            while(row=mysql_fetch_row(res)){
                if(row[0]==s && pass==row[2]){
                    cout<<"Hii. "<<row[1]<<". You are welcomed to use the application."<<endl;
                    flag=1;
                    break;
                }
            }
        }
    }
    return flag;
}
insertion(MYSQL*conn)
{
    int qstate=0;
    stringstream ss;
    string User_id,Age;
    string confirmed_Password;
    string Password,Name;
    string pass ="";
    string pass1="";
    char ch;
    create:
    cout<<"Enter the User_id"<<endl;
    cin>>User_id;
    cout<<"Enter the Password"<<endl;
    ch = _getch();
    while(ch != 13){//You can enter max 13 characters
      pass.push_back(ch);
      cout << '*';
      ch = _getch();
    }
    cout<<endl;
    char ch1;
    cout<<"Confirm your password"<<endl;
    ch1=_getch();
    while(ch1 != 13){//You can enter max 13 characters
      pass1.push_back(ch1);
      cout << '*';
      ch1 = _getch();
    }
    cout<<endl;
    if(pass1==pass){
    cout<<"Enter the Name of the user."<<endl;
    cin>>Name;
    cout<<"Enter the age"<<endl;
    cin>>Age;
    }
    else{
        goto create;
    }
    ss<<"INSERT INTO driver (User_id,Password,Name,Age) VALUES('"+User_id+"','"+pass+"','"+Name+"','"+Age+"')";
    string query =ss.str();
    const char*q=query.c_str();
    qstate=mysql_query(conn,q);
    int value=Age.compare("18");
    if(qstate==0 && value>=0){
        cout<<"Record Inserted..........\n";
        return 1;
    }
    else if(value<0){
        deletedb(conn,User_id);
        return 2;
    }
    else{
        cout<<"Failed to insert........the record exists in the database\n";
        return 1;
    }
}
insertion1(MYSQL*conn)
{
    int qstate=0;
    stringstream ss;
    string Car_id,year_of_man,User_id;
    string Model_no;
    cout<<"Enter the Car_id"<<endl;
    cin>>Car_id;
    cout<<"Enter the model no. of your car"<<endl;
    cin>>Model_no;
    cout<<"Enter the year of manufacturing"<<endl;
    cin>>year_of_man;
    ss<<"INSERT INTO driver (Car_id,Model_no,year_of_man,User_id) VALUES('"+Car_id+"','"+Model_no+"','"+year_of_man+"')";
    string query =ss.str();
    const char*q=query.c_str();
    qstate=mysql_query(conn,q);
    if(qstate==0){
        cout<<"Record Inserted..........\n";
    }
    else{
        cout<<"Failed to insert.........\n";
    }
}
int minimum(int a,int b)
{
    if(a<b){
        return a;
    }
    else{
        return b;
    }
}
int it(int pred[][N],int s,int d){
    int con=1;
    while(s!=d){
        d=pred[s][d];
        if(d==INF){
            break;
        }
        con++;
    }
    return con;
}
int iterpath(int pred[][N], int s, int d,int arr[]){
  int temp = d;
  int con = 1;
  while(s != d){
      d = pred[s][d];
      if(d == INF){
         break;
      }
    con++;
    }
    d = temp;
    for(int i=con-1; i>=1; i--){
      arr[i] = d;
      d = pred[s][d];
    }
  arr[0] = s;
}
int floydWarshall(int graph[N][N], int pred[N][N],int s,int e)
{
/* dist[][] will be the output matrix
that will finally have the shortest
distances between every pair of vertices */
    int dist[N][N], i, j, k;

/* Initialize the solution matrix same
as input graph matrix. Or we can say
the initial values of shortest distances
are based on shortest paths considering
no intermediate vertex. */
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            dist[i][j] = graph[i][j];
        }
    }
/* Add all vertices one by one to
the set of intermediate vertices.
---> Before start of an iteration,
we have shortest distances between all
pairs of vertices such that the
shortest distances consider only the
vertices in set {0, 1, 2, .. k-1} as
intermediate vertices.
----> After the end of an iteration,
vertex no. k is added to the set of
intermediate vertices and the set becomes {0, 1, 2, ..
k} */
    for (k = 0; k < N; k++) {
// Pick all vertices as source one by one
        for (i = 0; i < N; i++) {
// Pick all vertices as destination for the
// above picked source
            for (j = 0; j < N; j++) {
// If vertex k is on the shortest path from
// i to j, then update the value of
// dist[i][j]
                if (dist[i][j] > (dist[i][k] + dist[k][j])
                    && (dist[k][j] != INF
                    && dist[i][k] != INF))
                    {
                        pred[i][j] = pred[k][j];
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
            }
        }
    }
    if(s<e){
    cout<<"The shortest possible path length between the given points is: "<<dist[s][e]<<endl;
    }
    else{
        cout<<"The shortest possible path length between the given points is: "<<dist[e][s]<<endl;
    }
}
struct route_name
{
    string s;
};
int main()
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"192.168.0.8","Abhir","Amrh1902@","project",0,NULL,0);
    route_name r[100];
    int x;
    cout<<"\t\t\t\tWelcome to the VIT ALERT"<<endl;
    cout<<"========================================================================================"<<endl;
    start:
    cout<<"Do you have an account? If yes enter 1 or else enter 2"<<endl;
    cin>>x;
    int t;
    if(x==2){
        create_login:
        t=insertion(conn);
    }
    if(t==1 || x==1){
    login:
    int m=selection(conn);
    if(m){
    char y;
    cout<<endl;
    cout<<endl;
    cout<<"Is your car id among the following car ids : "<<endl;
    int cid[100];
    int sp[100];
    int z=0;
    if(conn){
        int qstate=mysql_query(conn,"SELECT Car_id FROM car");
        if(!qstate){
            res=mysql_store_result(conn);
            while(row=mysql_fetch_row(res)){
                cout<<row[0]<<endl;
            }
        }
    }
    if(conn){
        int qstate=mysql_query(conn,"SELECT Car_id,speed_limit FROM car");
        if(!qstate){
            res=mysql_store_result(conn);
            while(row=mysql_fetch_row(res)){
                cid[z]=atoi(row[0]);
                sp[z]=atoi(row[1]);
                z++;
            }
        }
    }
    cout<<"If yes write y else write n"<<endl;
    cin>>y;
    if(y=='n'){
        insertion1(conn);
    }
    int m;
    cout<<"Enter the car id: "<<endl;
    cin>>m;
    int speed_of_car;
    for(int i=0;i<z;i++)
    {
        if(m==cid[i]){
            speed_of_car=sp[i];
            break;
        }
    }
    int arr[100][2];
    int pathl[100];
    double prob[100];
    int M=sizeof(arr)/sizeof(arr[0]);//The edges
    if(conn){
        int qstate=mysql_query(conn,"SELECT sp_index,ep_index,path_length,route_name,probability FROM routes");
        if(!qstate){
            int i=0;
            res=mysql_store_result(conn);
            while(row=mysql_fetch_row(res)){
                arr[i][0]=atoi(row[0]);
                arr[i][1]=atoi(row[1]);
                pathl[i]=atoi(row[2]);
                r[i].s=row[3];
                prob[i]=atof(row[4]);
                i++;
            }
        }
    }
    int d[N][N]=     {{0,10,6,INF,INF,INF,INF},  // Adjacency matrix
                     {10,0,INF,15,INF,INF,INF},
                     {6,INF,0,5,INF,INF,INF},
                     {INF,15,5,0,15,INF,INF},
                     {INF,INF,INF,15,0,3,8},
                     {INF,INF,INF,INF,3,0,4},
                     {INF,INF,INF,INF,8,4,0}};

    int pred[N][N]=  {{INF,0,0,INF,INF,INF,INF}, // Predecessor matrix based on the
                     {1,INF,INF,1,INF,INF,INF},
                     {2,INF,INF,2,INF,INF,INF},
                     {INF,3,3,INF,3,INF,INF},
                     {INF,INF,INF,4,INF,4,4},
                     {INF,INF,INF,INF,5,INF,5},
                     {INF,INF,INF,INF,6,6,INF}};

    int d1[100][100];
    int s,e;
    cout<<"------------------------------------------------------------------------------------"<<endl;
    cout<<"Enter the starting point and ending point of the journey: "<<endl;
    cin>>s>>e;
    cout<<"===================================================================================="<<endl;
    floydWarshall(d,pred,s,e); // Applying Floyd-Warshall algorithm.
    int c=it(pred,s,e);
    int arr1[c];
    iterpath(pred,s,e,arr1);
    int con1=0;
    double arr2[c];
    int speed;
    if(s<e){
    cout<<"The suggested path is: "<<endl;
    for(int i=0;i<8;i++){
        if(arr1[con1]==arr[i][0] && arr1[con1+1]==arr[i][1]){
            arr2[con1]=prob[i];
            cout<<arr1[con1]<<"-->"<<arr1[con1+1]<<"....the probability of the accident taking place on the road will be: "<<arr2[con1]<<" the route is "<<r[con1].s<<endl;
            con1++;
        }
    }
    cout<<"====================================================================================="<<endl;
    double p=1;
    for(int i=0;i<c;i++){
        p=p*(1-arr2[i]);
    }
    speed = 80-40*(1-p);
    cout<<"The probability that the accident takes place while the whole journey is: "<<(1-p)<<endl;
    //cout<<"The safety speed limit for your car should be: "<<speed_of_car<<endl;
    cout<<"The suggested safety speed limits is: "<<speed<<endl;
    }
    else{
        int arr3[100];
        for(int i=0;i<c;i++){
            arr3[c-i-1]=arr1[i];
        }
        for(int i=0;i<8;i++){
        if(arr3[con1]==arr[i][0] && arr3[con1+1]==arr[i][1]){
            arr2[con1]=prob[i];
            cout<<arr3[c-1-con1]<<"-->"<<arr3[c-1-(con1+1)]<<"....the probability of the accident taking place on the road will be: "<<arr2[c-1-con1]<<" the route is "<<r[c-1-con1].s<<endl<<endl;
            con1++;
            }
        }
        cout<<endl;
        cout<<"====================================================================================="<<endl;
        double p=1;
        for(int i=0;i<c;i++){
            p=p*(1-arr2[i]);
        }
        speed = 80-40*(1-p);
        cout<<"The probability that the accident will takes place while the whole journey is: "<<(1-p)<<endl<<endl;
        //cout<<"The safety speed limit for your car should be: "<<speed_of_car<<endl;
        cout<<"The suggested safety speed limits are: "<<speed<<endl;
    }
    }
    else{
        string pr;
        cout<<"The user id or the password is incorrect do check it again...."<<endl;
        cout<<"Create your account if don't have one or else try to login again."<<endl;
        cout<<"Enter your choice login or create a new account"<<endl;
        cin>>pr;
        if(pr=="login")
        {
            goto login;
        }
        else
        {
            goto create_login;
        }
    }
    }
    else{

        cout<<"You are under aged"<<endl;
    }

}

