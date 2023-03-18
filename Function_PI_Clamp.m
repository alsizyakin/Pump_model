function [out, sum_return] = Function_PI_Clamp(m_sumI, m_kP, m_kI, Input, m_outMax, ...
    m_outMin, dt)
%PI Controller with Clamping


%dt = 100e-6;

%Pi controller
% Coeff

kP = m_kP;
kI = m_kI;

% Proportional

m_sumP = kP*Input;

% Integral
m_sumI = m_sumI + kI*Input*dt;

out_sum = m_sumP + m_sumI;

if (out_sum > m_outMax)
    out = m_outMax;
    if (m_sumP < m_outMax)
        m_sumI = m_outMax - m_sumP;
    else
        m_sumI = 0;
    end

elseif (out_sum < m_outMin)
	out = m_outMin;
    if (m_sumP > m_outMin)
		m_sumI = m_outMin - m_sumP;  
    else 
        m_sumI = 0;
    end

else
	out = out_sum;
end
   
    sum_return = m_sumI; 
end
