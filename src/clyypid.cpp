#include "clyypid.h"

#include <math.h>

#include <QDebug>

struct _pid{
    float err;                //定义偏差值
    float err_last;            //定义上一个偏差值
    float Kp,Ki,Kd;            //定义比例、积分、微分系数
    float power;          //定义输出功率（此值为电压与电流的乘积，如果电压恒定，功率除以电压即为电流）
    float integral;            //定义积分值
    float maxpower;       //最大输出功率
    float minpower;       //最小输出功率
};

static _pid pid;

//初始化函数
void PID_init()
{
    qDebug() << "PID_init begin";
    pid.err=0.0;
    pid.err_last=0.0;
    pid.power=0.0;
    pid.integral=0.0;
    pid.Kp=0.01;    //比例系数，相对于步长，可调
    pid.Ki=0.004;  //积分系数，控制收敛效果，可调;和采样时间有关，目前该数值对应采样时间为1秒的情况；如果采样时间为0.1秒，此数值应该变为原来的十分之一。
    pid.Kd=0;      //微分系数，对于波动较为严重的系统不能使用微分，会造成系统非常不稳定！因此这里是0。
    pid.maxpower=5.0;       //最大输出功率5W，如果用小加热器则需要改变该值
    pid.minpower=0.0;       //最小输出功率0W
    qDebug() <<  "PID_init end";
}

//控制函数接口，参数speed是目标温度，Aspeed是被控制物体的温度，返回值为功率大小
float PID_realize(float speed, float Aspeed)
{
    float index = 0;
    pid.err = speed - Aspeed; //两者误差
    if (abs(pid.err) > 10) {
        if (pid.err > 10) {
            pid.power = 5;//如果两者差距大于10度，关闭积分控制器，全力加热或者不加热
            return pid.power;
        } else  {
            pid.power = 0;//如果两者差距小于1度，关闭积分控制器，关闭加热
            return pid.power;
        }
    } else if (abs(pid.err) < 3) {
        index = 1.0;
        pid.integral += pid.err;
    } else {
        index = (10 - abs(pid.err)) / 7;
        pid.integral += pid.err;
    }
    pid.power = pid.Kp * pid.err + index * pid.Ki * pid.integral + pid.Kd * (pid.err - pid.err_last);
    if (pid.power > pid.maxpower) {
        pid.power = 5;
    }//设置最大输出功率5W
    if (pid.power < pid.minpower) {
        pid.power = 0;
    }//设置最小输出功率0W
    pid.err_last = pid.err;
    return pid.power;
}
