[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-dark-v6.png#gh-dark-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/signaloid/Signaloid-Demo-General-C#gh-dark-mode-only)
[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-light-v6.png#gh-light-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/signaloid/Signaloid-Demo-General-C#gh-light-mode-only)

# Lift force for an airfoil with uncertainties on the Signaloid platform
This program determines the lift force for an airfoil based on the Bernoulli equation and depends on the aircraft sensor measurements, the shape of the airfoil (wing) and on the wind conditions. It determines the lift force together with the uncertainties using the Signaloid Cloud Developer Platform.

## Physical principle
The lift force can be determied using the Bernoulli equtions as

$$L = C_L \times \frac{\rho v^2}{2} \times S$$

where $C_L$ is the lift coefficient, $\rho$ is the air density, $v$ is the speed of the aircraft and $S$ is the area of the airfoil.

I have chosen to calculate the lift force using measurable quantities. Thus, at the level of the airfoil, one measures the total pressure and the static pressure using Pitot tubes. The temperature is either obtained from meteorological services or measured by a probe in flight. The angle of attack is measured with a vane and the wind velocity using also a Pitot tube.

The lift coefficient can be determined in terms of the angle of attack $\alpha$ and the percentage of camber $$p_c$$ of the airfoil as:

$$C_L = 2 \pi (\alpha + 2p_c + 1 - \sqrt{4p_c^2+1})  .$$

Using the perfect gas equations, the density $\rho$ can be expressed in terms of the pressure $p$ and temperature $T$ as

$$ \rho = \rho_0 \frac{p}{p_0} \frac{T_0}{T}$$

where the quantities with a 0 index represent the values of physical quantities at sea level for the standard atmosphere, i.e. $T_0 = 288.15 K$, $p_0=101325 Pa$, $\rho_0=1.225 kg/m^3$.

The speed of the aircraft is usually determined in terms of two measurements (with Pitot tubes), of the static pressure $p_s$ and the total pressure $p$. Their difference is the dynamic pressure $\rho v^2/2$. The *True aircraft speed* (TAS) is determined differently in two regimes
1) The subsonic regime

$${\rm TAS}=\sqrt{\frac{2(p-p_s)}{p}T \frac{1}{\rho_0 T_0}} ,$$

2) The supersonic regime (accounting for air compressibility)

$${\rm TAS}=a_0\sqrt{5 \left[\frac{p-p_s}{p}+1\right]^{2/7}-1} \times\sqrt{\frac{T}{T_0}} ,$$

where a_0 is the speed of sound at standard sea level.

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

The constants and the parameters of the model, together with some plausible numerical values (given in SI units) and their uncertainties are given in the table below.

| Parameter | Description | Value | Uncertainty
| --- | --- | --- | ---
| $a_0$ | sound speed at sea level | 340.29 m/s | 0
| $T_0$ | air temperature at sea level | 288.15 K | 0
| $\rho_0$ | air density at sea level | 1.225 $\rm kg/m^3$ | 0
| $p_0$ | air pressure at sea level | $1.01325 \times 10^5$ Pa | 0
| $p$ | air pressure  | $8 \times 10^4$ Pa | $0.22$%
| $p_s$ | static air pressure  | $5 \times 10^4$ Pa | $0.22$%
| $T$ | air temperature | 260 K |  $0.15$%
| $\alpha$ | angle of attack | $4^{\circ}$ | 8%
| $p_c$ | ??? | 0.06 | 0
| $W$ | wind speed | 25 m/s | 2%
| $\beta$ | wind direction | $30^{\circ}$ | 8%


## References
