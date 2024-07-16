[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-dark-v6.png#gh-dark-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/signaloid/Signaloid-Demo-General-C#gh-dark-mode-only)
[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-light-v6.png#gh-light-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/signaloid/Signaloid-Demo-General-C#gh-light-mode-only)

# Lift force for an airfoil with uncertainties on the Signaloid platform
This program determines the lift force for an airfoil based on the Bernoulli equation and depends on the aircraft sensor measurements, the shape of the airfoil (wing) and on the wind conditions. It determines the lift force together with the uncertainties using the Signaloid Cloud Developer Platform.

## Physical principle
The lift force can be determied using the Bernoulli equtions as

$$L = C_L \times \frac{\rho v^2}{2} \times S$$

where $C_L$ is the lift coefficient, $\rho$ is the air density, $v$ is the speed of the aircraft and $S$ is the area of the airfoil (wing).

The lift coefficient can be determined in terms of the angle of attack $\alpha$ and the ... as:

$$C_L = 2 \pi (\alpha + 2p + 1 - \sqrt{4p^2+1})  .$$

The density $\rho$ can be expressed in terms of the pressure $p$ and temperature $T$ as

$$ \rho = \rho_0 \frac{p}{p_0} \frac{T_0}{T}$$

where the quantities with a 0 index represent measurements at sea level.

The speed of the aircraft is usually determined in terms of two measurements (with Pitot tubes), of the static pressure $p_s$ and the dynamic pressure $p$. The *True aircraft speed* (TAS) is determined differently in two regimes
1) The subsonic regime

$${\rm TAS}=\sqrt{\frac{2(p-p_s)}{p}T \frac{1}{\rho_0 T_0}} ,$$

2) The supersonic regime

$${\rm TAS}=a_0\sqrt{5 \left[\frac{p-p_s}{p}+1\right]^{2/7}-1} \times\sqrt{\frac{T}{T_0}} ,$$

where a_0 is the speed of sound at standard sea level.

The speed of the aircraft is then determined in terms of the angle of true air speed, the angle of attack $\alpha$ and the direction of the wind with respect to the ground $\beta$ as

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

The parameters of the model, together with some plausible numerical values (given in SI units) and their uncertainties are given in the table below.

## References
