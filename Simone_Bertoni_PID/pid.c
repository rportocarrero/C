// This code was copied from Simone Bertoni's linkedin post.

#include <stdio.h>
#include <math.h>

float TIME_STEP = 0.1;

struct PID {
    float Kp;   // proportional gain constant
    float Ki;   // integral gain constant
    float Kd;   // derivative gain constant
    float Kaw;  // anti-windup gain constant
    float T_C;  // time constant
    float T;    //Timestep
    float max;  // Max command
    float min;  // min command 
    float max_rate; // mac rate of change of command
    float integral; //integral term
    float err_prev; //previous error
    float deriv_prev;   //previous derivative
    float command_sat_prev; //previous saturated command
    float command_prev; // previous comand 
};

struct Object
{
    float m;    // mass of the object
    float k;    // damping coefficient
    float F_max;    //max force applied to the object
    float F_min;    //minimum force applied to the object
    float T;    //Time step
    float v;    //velocity of the object
    float z;    //positionof the object
};

float PID_step(struct PID* pid, float measurement, float setpoint){
    //PID implementation
    float err;
    float command;
    float command_sat;
    float deriv_flit;

    //error calc
    err = setpoint - measurement;

    //integral w/ anti windup
    pid->integral += pid->Ki*err*pid->T + pid->Kaw*(pid->command_sat_prev - pid->command_prev)*pid->T;

    //derivative term
    deriv_flit = (err - pid->err_prev + pid->T_C*pid->deriv_prev)/(pid->T + pid->T_C);
    pid-> err_prev = err;
    pid -> deriv_prev = deriv_flit;

    // sum terms
    command = pid->Kp*err + pid->integral + pid->Kd*deriv_flit;

    pid->command_prev = command;

    //apply command saturation
    if(command > pid-> max){
        command_sat = pid->max;
    } else if (command < pid-> min){
        command_sat = pid->min;
    } else {
        command_sat = command;
    }

    // apply rate limits
    if(command_sat > pid-> command_sat_prev + pid-> max_rate*pid->T){
        command_sat = pid->command_sat_prev + pid-> max_rate*pid->T;
    } else if(command_sat < pid->command_sat_prev - pid->max_rate*pid->T){
        command_sat = pid->command_sat_prev - pid->max_rate*pid->T;
    } else {}

    pid->command_sat_prev = command_sat;

    return command_sat;
}

float  Object_Step(struct Object *obj, float F){
    //update position

    //derivative variable and saturated force command
    float dv_dt;
    float F_sat;

    //saturate input force
    if(F > obj->F_max){
        F_sat = obj->F_max;
    } else if (F < obj->F_min){
        F_sat = obj->F_min;
    } else{
        F_sat = F;
    }

    // calcuate derivative
    dv_dt = (F_sat - obj->k*obj->v)/obj->m;

    //update velocity and position
    obj->v += dv_dt*obj->T;
    obj->z += obj->v*obj->T;

    return obj->z;
}

int main(){
    //sim time
    float t = 0;

    //counter
    int i = 0;

    //setpoint of first loop
    float command1 = 0;
    float stp1 = 100;
    float z1 = 0;

    //setpoint of second loop
    float command2 = 0;
    float stp2 = 50;
    float z2 = 0;

    // PID params for first loop
    struct PID pid1 = {1,0.1,5,0.1,1, TIME_STEP, 100, -100, 40, 0,0,0,0,0};

    //object for first loop
    struct Object obj1 = {10, 0.5, 100, -100, TIME_STEP, 0,0};

    // PID params for second loop
    struct PID pid2 = {1.8,0.3,7,0.3,1, TIME_STEP, 100, -100, 40, 0,0,0,0,0};

    //object for second loop
    struct Object obj2 = {10, 0.5, 100, -100, TIME_STEP, 0,0};

    //open file for sim data
    FILE *file = fopen("PID_data.csv", "w");

    //main loop
    while(i < ceil(120/TIME_STEP)){
        stp1 = (t < 60) ? 100 : 200;
        stp2 = (t < 60) ? 50 : 150;

        //first loop
        command1 = PID_step(&pid1, z1, stp1);
        z1 = Object_Step(&obj1, command1);

        //second loop
        command2 = PID_step(&pid2, z2, stp2);
        z2 = Object_Step(&obj2, command2);

        //log sim data for timestep
        fprintf(file, "%f,%f,%f,%f,%f,%f,%f\n", t, command1, z1, stp1, command2, z2, stp2);

        //increment time and counter
        t += TIME_STEP;
        i += 1;
    }

    // close file and exit
    fclose(file);
    return 0;
}
