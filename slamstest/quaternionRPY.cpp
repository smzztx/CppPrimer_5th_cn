// #include "stdafx.h"
#include "math.h"
#include<iostream>
#include<string.h>
using namespace std;
 
void EulerAnglesToQuaternion(double roll, double pitch, double yaw) 
{ 
    double cosRoll,sinRoll,cosPitch,sinPitch,cosyaw,sinyaw,qx,qy,qz,qw;
    cosRoll = cosf(roll * 0.5f); //X
    sinRoll = sinf(roll * 0.5f);//X
 
    cosPitch = cosf(pitch * 0.5f);//Y
    sinPitch = sinf(pitch * 0.5f);//Y

    cosyaw = cosf(yaw * 0.5f);//Z
    sinyaw = sinf(yaw * 0.5f);//Z
 
    qx = sinRoll * cosPitch * cosyaw - cosRoll * sinPitch * sinyaw;
    qy = cosRoll * sinPitch * cosyaw + sinRoll * cosPitch * sinyaw;
    qz = cosRoll * cosPitch * sinyaw - sinRoll * sinPitch * cosyaw;
    qw = cosRoll * cosPitch * cosyaw + sinRoll * sinPitch * sinyaw;
    
    cout << "qx = " << qx << endl;
    cout << "qy = " << qy << endl;
    cout << "qz = " << qz << endl;
    cout << "qw = " << qw << endl;
}
void QuaternionToEulerAngles(double qx, double qy, double qz, double qw) 
{
    double roll, pitch, yaw;
    roll = atan2f(2.f * (qw*qx + qy*qz), 1-2*(qx*qx+qy*qy));//X
    pitch = asinf(2.f * (qw*qy - qx*qz)); //Y
    yaw = atan2f(2.f * (qw*qz + qx*qy), 1-2*(qy*qy+qz*qz)); //Z
 
    cout << "roll = " << roll << endl;
    cout << "pitch = " << pitch << endl;
    cout << "yaw = " << yaw << endl;
}
 
int main()
{
    QuaternionToEulerAngles(0, 0, -0.78104, 0.624481);
    EulerAnglesToQuaternion(0,0,-1.7926);
    return 0;
}