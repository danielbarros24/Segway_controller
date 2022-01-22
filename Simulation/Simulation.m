close all;
clc;

%% Motor

J = 0.0632;     % moment of inertia of the rotor (kg.m^2)
b = 0.7897;     % motor viscous friction constant (N.m.s)
K = 0.678;      % electromotive force constant  and motor torque constant 
R = 1;          % electric resistance (Ohm)
L = 5e-3;       % electric inductance (H)
r = 0.3556;     % wheel radius

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

M = 0.4;        % Mass of the cart (kg)
m = 0.5;        % Mass of the pendulum (kg)
b = 0.1;        % coefficient of friction for cart (N/m/sec)
I = 0.1350;     % mass moment of inertia of the pendulum (kg.m^2)
g = 9.8;        % gravity
l = 0.6;        % length to pendulum center of mass (m)

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