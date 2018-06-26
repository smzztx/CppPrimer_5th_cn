// #include "stdafx.h"
#include "math.h"
#include<iostream>
#include<string.h>
using namespace std;
 
void EulerAnglesToQuaternion(double roll, double pitch, double yaw) 
{ 
    double cosRoll,sinRoll,cosPitch,sinPitch,cosyaw,sinyaw,qw,qx,qy,qz;
    cosRoll = cosf(roll * 0.5f); //z
    sinRoll = sinf(roll * 0.5f);//z
 
    cosyaw= cosf(yaw * 0.5f);//y
    sinyaw = sinf(yaw * 0.5f);//y
 
    cosPitch = cosf(pitch * 0.5f);//x
    sinPitch = sinf(pitch * 0.5f);//x
 
    qx = sinRoll * cosyaw * cosPitch - cosRoll * sinyaw * sinPitch;
    qy = cosRoll * cosyaw * sinPitch + sinRoll * sinyaw * cosPitch;
    qz = cosRoll * sinyaw * cosPitch - sinRoll * cosyaw * sinPitch;
    qw = cosRoll * cosyaw* cosPitch + sinRoll * sinyaw * sinPitch;
    
    cout << "qx = " << qx << endl;
    cout << "qy = " << qy << endl;
    cout << "qz = " << qz << endl;
    cout << "qw = " << qw << endl;
}
void QuaternionToEulerAngles(double qx, double qy, double qz, double qw) 
{
    double roll, pitch, yaw;
    roll =atan2f(2.f * (qw*qy + qz*qx), 1-2*(qy*qy+qx*qx));//X
    pitch =  asinf(2.f * (qw*qx - qy*qz)); //Y
    yaw =  atan2f(2.f * (qw*qz + qx*qy), 1-2*(qz*qz+qx*qx)); //Z
 
    cout << "roll = " << roll << endl;
    cout << "pitch = " << pitch << endl;
    cout << "yaw = " << yaw << endl;
}
 
int main()
{
    QuaternionToEulerAngles(0, 0, -0.78104, 0.624481);
    EulerAnglesToQuaternion(0,0,-1.78);
    return 0;
}