[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-dark-v6.png#gh-dark-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/signaloid/Signaloid-Demo-General-C#gh-dark-mode-only)
[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-light-v6.png#gh-light-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/signaloid/Signaloid-Demo-General-C#gh-light-mode-only)

# Lift force for an airfoil with uncertainties on the Signaloid platform
This program determines the lift force for an airfoil based on the Bernoulli equation and depends on the aircraft sensor measurements associated to an airplane flying at the same altitude, with the same velocity and in the same atmosphere including the wind, and the geometry of the airfoil. It determines the lift force together with the uncertainties using the Signaloid Cloud Developer Platform.

## Physical principle
The lift force can be determined as

$$L = C_L \times \frac{\rho v^2}{2} \times S$$

where $C_L$ is the lift coefficient, $\rho$ is the air density, $v$ is the speed of the airfoil with respect to the atmosphere and $S$ is the platform area.

I have chosen to calculate the lift force using measurable quantities. Thus, at the position of the airfoil (aircraft), one measures the total pressure $p$ and the static pressure $p_s$ using Pitot tubes. Their difference is the dynamic pressure $\rho*v^2/2$. The temperature is either obtained from meteorological services or measured by a probe in flight. The angle of attack is measured with a vane and the wind velocity using also a Pitot tube.

The lift coefficient can be determined in terms of the angle of attack $\alpha$ and the percentage of camber $p_c$ of the airfoil as:

$$C_L = 2 \pi (\alpha + 2p_c + 1 - \sqrt{4p_c^2+1})  .$$

The lift coefficient depends on the Mach number for subsonic flight as

$$C_L(M)= C_L(M=0)/sqrt(1-M^2)$$

where the Mach number is the ratio between the speeds of airsoil and sound. In the present project I analyse only subsonic fly (M<0.8).

The Mach number is defined as

$$M=\sqrt{5 \left[\left(\frac{p-p_s}{p}+1\right)^{2/7} \right]} .$$

It is generally accepted that the lift coefficient has a very small dependence on air viscosity [^0], and it will be neglected. 

The Bernoulli equation for an isoentropic fluid ($p/rho^\gamma={\rm constant}$) is

$$\frac{v^2}{2}+\frac{\gamma}{\gamma-1} \frac{p}{\rho}={\rm constant},$$

while the corresponding form for the incompressible fluid is

$$\frac{\rho v^2}{2}+p_s=p.$$

Note that the use of Bernoulli equation for the incompressible fluid produces errors less than 3% up to Mach number less than 0.5. For air, $\gamma=1.4$.

Thus, for low speeds with respect to the speed of sound (M<0.5), the lift force can be estimated directly based on the measurements of $p$, $p_s$ , on the data related to airfoils geometry $(p_c, S)$ and on the angle of attack as

$$L=C_L(p-ps)S$$

In order to perform the correction for higher speeds, one must calculate the velocity. 
I shall use in the project the equations corresponding to compressible air.
One can calculate [^0a]:
- the calibrated air speed 

$$v_{cal}=\frac{2a_0^2}{\gamma-1} \left[\left(\frac{p-p_s}{p}+1\right)^{2/7} -1\right]$$

where the index “0” indicates the value at the sea level.

- the true air speed (TAS) is the speed of the aircraft relative to the air mass through which it is flying. For isentropic flow (with the ratio of specific heats 1.4), accounting for air compressibility, TAS is calculated as 
Using the perfect gas equations, the density $\rho$ can be expressed in terms of the pressure $p$ and temperature $T$ as [^1]

$${\rm TAS}=a_0\sqrt{5 \left[\left(\frac{p-p_s}{p}+1\right)^{2/7}-1\right]} \times\sqrt{\frac{T}{T_0}} ,$$

where $a_0$ is the speed of sound at standard sea level.

The air density $\rho$ at altitude $h$, where the pressure is $p$ and the temperature $T$ is determined in the standard atmosphere [alvaro, Fund aerops eng], from the dependence of density on altitude:

$$ \rho = 1.225 (1-22.558 \times 10^{-6} \times h)^4.2559$$. 


$$ \rho = \rho_0 \frac{p}{p_0} \frac{T_0}{T}$$

where the quantities with a 0 index represent the values of physical quantities at sea level for the standard atmosphere, i.e. $T_0 = 288.15 K$, $p_0=101325 Pa$, $\rho_0=1.225 kg/m^3$.



The speed of the airfoil is then determined in terms of the angle of true air speed, the angle of attack $\alpha$ and the direction of the wind with respect to the ground, $\beta$, as

$$v = {\rm TAS} + W \cos(\beta-\alpha)  .$$


## Directory structure
The files are located in the `src/` folder for the repository, containing one C source file (`main.c`) and a `config.mk` to modify the build parameters.
```
src/
├── config.mk
└── main.c
```


## Implementation
The program is implemented in C. The uncertainties in the measurements of the variables are taken into account using the `UxHw` library implemented in the `uxhw.h` header file.
## Numerical values and uncertainties

The range of variation of the parameters is
| Parameter | Description | Range
| --- | --- | --- 
| $p$ | air pressure  | $2 \times 10^4$ Pa $\div p_0$ (considering the troposphere and the tropopause)
| $p_s$ | static air pressure  | $0 \div 7.7 \times 10^4$ Pa (corresponding to the sound velocity of the airfoil at sea level)
| $T$ | air temperature | 216.5 K (limit of tropopause) $\div$ 288.15 K 
| $\alpha$ | angle of attack | $0 \div 8$ (max angle of attack for linear dependence of $C_L(\alpha)$ for most of airfoils)
| $p_c$ | precentage of camber | $0 \div 0.6$ (depending on the airfoil)

The constants, together with plausible numerical values for the parameters of the model (given in SI units), considered as an example and their uncertainties are given in the table below.

| Parameter | Description | Value | Uncertainty
| --- | --- | --- | ---
| $a_0$ | sound speed at sea level | 340.29 m/s | 0
| $T_0$ | air temperature at sea level | 288.15 K | 0
| $\rho_0$ | air density at sea level | 1.225 $\rm kg/m^3$ | 0
| $p_0$ | air pressure at sea level | $1.01325 \times 10^5$ Pa | 0
| $p$ | air pressure  | $8 \times 10^4$ Pa/ $5.5 \times 10^4$ Pa | $0.22$% [^2]
| $p_s$ | static air pressure  | $5 \times 10^4$ Pa/ $5.03 \times 10^4$ Pa | $0.22$% [^2]
| $T$ | air temperature | 275 K/ 258 K |  $0.15$% [^2]
| $\alpha$ | angle of attack | $4^{\circ}$/ $6^{\circ}$ | 8% [^3]
| $p_c$ | percentage of camber | 0.06 [^4] (NACA 6409)/ 0.04 (NACA 4412) | 0 
| $W$ | wind speed | 25 m/s | 2% [^5]
| $\beta$ | wind direction | $30^{\circ}$ | 8% [^5]


## References
[^0]: R. Hull, Fundamentals of Aeroplane Space Dynamics, Springer 2007
[^0a]: Barnes McCormick, Aerodynamics, Aeronautics and Flight Mechanics, John Wiley and Sons, 1994
[^1]: https://en.wikipedia.org/wiki/True_airspeed
[^2]: C. Bonham et al., Meas. Sci. Techn. 29, 015002 (2018)
[^3]: L. Sankaralingam, C. Ramprasad, Clin. J. Aeron. 33, 749 (2020)
[^4]: http://airfoils.com/index.htm
[^5]: E. Brown, NCAR ITN-386+STR (1993) 
