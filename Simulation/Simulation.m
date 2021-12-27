close all;
clc;

%% Motor

J = 0.0632;
b = 0.7897;
K = 0.678;
R = 1;
r = 0.3556;
L = 5e-3;

A = [-b/J   K/J
    -K/L   -R/L];
B = [0
    1/L];
C = [0   K/r];
D = 0;

states = {'theta_dot', ''};
inputs = {'V'};
outputs = {'F'};

motor_ss = ss(A,B,C,D,'statename',states,'inputname',inputs,'outputname',outputs);

%% Inverted pendulum

M = 0.4;
m = 0.5;
b = 0.1;
I = 0.1350;
g = 9.8;
l = 0.6;

p = I*(M+m)+M*m*l^2; %denominator for the A and B matrices

A = [0      1              0           0;
     0 -(I+m*l^2)*b/p  (m^2*g*l^2)/p   0;
     0      0              0           1;
     0 -(m*l*b)/p       m*g*l*(M+m)/p  0];
B = [     0;
     (I+m*l^2)/p;
          0;
        m*l/p];
C = [1 0 0 0;
     0 0 1 0];
D = [0;
     0];

states = {'x' 'x_dot' 'phi' 'phi_dot'};
inputs = {'u'};
outputs = {'x'; 'phi'};

sys_ss = ss(A,B,C,D,'statename',states,'inputname',inputs,'outputname',outputs);
sys_ss = tf(sys_ss);

full_ss = motor_ss * sys_ss(2);
fb_ss = feedback(pid_ss * full_ss, 1);

[y, tOut] = step(fb_ss, stepDataOptions('StepAmplitude', deg2rad(20)));
plot(tOut, rad2deg(y));