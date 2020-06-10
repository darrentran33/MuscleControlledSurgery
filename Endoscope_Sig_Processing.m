%% Initializing
clear;clc

%% Setting up hardware
a=arduino('COM3','uno','Baudrate',9600);%A Baud rate of 9600 to mimic Arduino serial plotter
%% Setting up data
open = load('EMGData.mat');
flexion_extension_data = open.b1;
time = flexion_extension_data(:,1);
EMG_anterior = flexion_extension_data(:,2);
EMG_posterior = flexion_extension_data(:,3);

%% Formatting Arduino 
LED_Anterior = 'D3';
LED_Posterior = 'D6';
configurePin(a,LED_Posterior,'DigitalOutput');
configurePin(a,LED_Anterior,'DigitalOutput');

%% Signal Processing
Abs_ant = abs(EMG_anterior); %Rectification of the Anterior Signal
Abs_post = abs(EMG_posterior); %Rectification of the Posterior Signal

smooth_ant = smooth(Abs_ant,150); %Smoothing running average to filter anterior signal
smooth_post = smooth(Abs_post,150);%Smoothing running average to filter posteiror signal

diff_EMG = (2.5.*smooth_ant)-(smooth_post);% Puts anterior readings in the positive domain and posterior readings in the negative domain

%% Establishing a baseline reading
baseline_EMG = 0; %Baseline as flexion in positive domain while extension in negative domain
tol = 0.002; %Tolerance because of residual noise at the baseline level
%% Flexion and Extension Analysis (With LEDs)

for n=1:size(time)
        if diff_EMG(n) > (baseline_EMG(:,1)+tol) %Gives flexion reading
            writeDigitalPin(a,LED_Posterior,0)
            writeDigitalPin(a,LED_Anterior,1)
        elseif diff_EMG(n) < (baseline_EMG(:,1)-tol)%Gives extension reading
            writeDigitalPin(a,LED_Anterior,0)
            writeDigitalPin(a,LED_Posterior,1)
        else 
            writeDigitalPin(a,LED_Anterior,0)%Gives no reading
            writeDigitalPin(a,LED_Posterior,0)
        end
  
end

