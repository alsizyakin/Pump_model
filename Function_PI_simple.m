function [out, sum_return] = Function_PI_simple(m_sumI, m_kP, m_kI, Input, dt)
%PI Controller without saturation;


%Pi controller
% Coeff

kP = m_kP;
kI = m_kI;

% Proportional

m_sumP = m_kP*Input;

% Integral
m_sumI = m_sumI + m_kI*Input*dt;

out_sum = m_sumP + m_sumI;
	out = out_sum;
    sum_return = m_sumI; 
end
